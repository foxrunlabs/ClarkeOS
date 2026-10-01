# ClarkeOS

**A 32-bit x86 kernel project developed in 2009–2010.**

ClarkeOS explores the foundations of an operating-system kernel: processor descriptor tables, interrupt and exception handling, direct hardware I/O, and text output without a hosted runtime. Written in C and x86 assembly, it exposes the low-level machinery beneath application software.

This repository preserves an early systems-programming project for historical and portfolio purposes. It is a kernel prototype: its startup sequence initializes the processor and console infrastructure, displays a readiness message, and loops indefinitely. It is not a complete operating system, and a successful boot of a newly rebuilt kernel has not been verified.

## What is implemented

- A Multiboot header and 32-bit assembly entry point.
- A flat Global Descriptor Table (GDT), kernel segment setup, and a 16 KiB stack.
- A 256-entry Interrupt Descriptor Table (IDT).
- Assembly stubs and C diagnostics for CPU exceptions.
- Initialization and IRQ masking controls for the two 8259A programmable interrupt controllers (PICs).
- Direct 80×25 VGA text output, text colors, control characters, and hardware cursor positioning.
- Minimal `printf`-style formatting and a byte-wise memory-fill routine.
- A helper for displaying the memory map supplied by a Multiboot bootloader; it is not called during normal startup.

The snapshot contains no interactive shell, keyboard input driver, scheduler, user processes, paging, heap allocator, networking, or kernel filesystem driver. Hardware IRQs are masked during initialization.

## How the kernel boots

The kernel expects an **external Multiboot-compatible bootloader**, such as GRUB. The repository does not include a bootloader, bootable disk image, or ISO-generation recipe.

```text
PC BIOS
  → external Multiboot-compatible bootloader
  → kernel assembly entry point: start
  → C entry point: k_main
  → processor and interrupt initialization
  → “System Ready.”
  → infinite loop
```

The bootloader recognizes the Multiboot header in `kernel/start.s`, loads the ELF kernel according to its layout, and transfers control to `start` in 32-bit protected mode. It supplies the Multiboot magic value in `EAX` and a boot-information address in `EBX`.

The assembly entry point disables interrupts, installs the kernel's GDT, loads the segment registers, establishes the stack, and passes the boot arguments to `k_main`. The linker script places the kernel at `0x00100000` (1 MiB), with read-only data and data sections aligned to 4 KiB boundaries.

`k_main` clears the screen, prints `Starting ClarkeOS...`, and validates the Multiboot magic. The hardware abstraction layer then installs the IDT and exception handlers, remaps IRQs to vectors `0x20`–`0x2f`, masks all hardware IRQs, and enables CPU interrupts. Finally, the kernel prints `System Ready.` and busy-loops.

An invalid magic value causes an error message and a return to the assembly entry code, which disables interrupts and halts in a loop.

## Implementation highlights

**C and assembly integration.** Assembly handles kernel entry and interrupt frames, while C implements initialization and diagnostic output. The kernel runs with flat ring-0 code and data segments.

**Exception diagnostics.** All IDT entries initially point to a dummy handler; vectors `0x00`–`0x1f` receive exception-specific stubs. The C handler displays an exception name, an applicable error code, saved EIP/EFLAGS, a stack address, and 16 stack words, then executes `hlt`. This is a raw stack dump rather than a symbolic backtrace.

**Direct hardware access.** Console output writes to VGA memory at `0xb8000`, and cursor positioning uses ports `0x3d4` and `0x3d5`. Screen clearing writes two character cells per 32-bit store.

**Freestanding utilities.** The formatter supports characters, strings, signed and unsigned decimal integers, hexadecimal, octal, literal percent signs, and the `#` alternate-form flag. Local variadic argument macros use GCC-compatible compiler built-ins. `k_memset` fills memory one byte at a time.

**Emulator debugging.** The `BOCHS` build define exposes an `xchg bx, bx` debugger-break macro, and the saved emulator configuration enables magic breaks.

Together, these components demonstrate processor initialization, boot protocols, linker layout, hardware I/O, and freestanding systems programming.

## Toolchain and historical dependencies

The supplied Makefiles name **Make, GCC, NASM, GNU `ld`, and `ar`**. They compile C with `-ffreestanding`, `-nostdinc`, `-fno-stack-protector`, local include paths, and a `BOCHS` define. NASM produces ELF objects. No hosted C runtime or standard library is linked by the supplied build.

The source assumes a **32-bit x86 environment**. Assembly declares `use32` and `cpu 386`; pointer conversions and descriptor layouts also depend on 32-bit addresses. The C code uses GNU-style inline assembly, packed structures, and compiler built-ins.

Exact historical compiler and binutils versions are not recorded. The Makefiles use native `gcc` and `ld` without explicitly selecting a 32-bit target or ELF linker emulation, so they depend on suitable host defaults.

The retained Bochs configuration specifies SDL output, local BIOS/VGA ROM paths, one emulated CPU, and 4 MiB RAM. `bochs.configure` is a list of options for building the emulator itself, not an executable project setup script. Emulator support for sound, network, or USB devices does not imply corresponding kernel drivers.

## Building

With a compatible 32-bit x86 ELF toolchain configured, the intended root build command is:

```sh
make
```

The root target builds the HAL first, then links the kernel. To remove the generated kernel/HAL build products:

```sh
make clean
```

**The unchanged Makefiles are not a portable modern build configuration.** A modern rebuild needs explicit compiler and linker targeting, and may also need adjustment for position-independent-code defaults and other compiler assumptions. The repository does not provide a pinned toolchain or cross-compiler setup.

### Verification status

During source review:

- All kernel and HAL C files compiled with Clang explicitly targeting `i386-unknown-none-elf`, with freestanding and non-PIC settings.
- All kernel and HAL assembly files assembled with NASM as ELF32 objects.
- The only warning from that C compilation check was the unused `mbi` parameter in `k_main`.

These checks validate individual compilation and assembly. They do **not** establish that the original Makefiles work unchanged, that the final kernel links successfully, or that the resulting binary boots. Linking and emulator execution were not verified.

## Running

A runnable setup must supply a Multiboot-compatible bootloader and boot media that load `kernel/kernel`. Building the kernel alone does not create that media.

The retained `bochsrc` and `make install` target are historical artifacts of the original disk-image workflow:

- `make install` expects that image, loop-mounts an ext2 partition at byte offset `32256`, and copies the kernel into `/system/` using Linux-oriented commands.
- The repository has no target to create the image or install its bootloader.

Consequently, neither the installation target nor the emulator configuration is ready to use with this source-only tree. A boot-media recipe and an emulator boot test are needed to establish a reproducible run procedure. Hardware compatibility beyond the intended legacy PC environment has not been established.

## Known limitations

This is preserved prototype code, with several concrete correctness limitations:

- `k_vsprintf` does not reset formatting flags between conversions; flags such as `#` can affect subsequent values.
- `k_printf` uses a fixed 1024-byte buffer without bounds checking.
- A backspace at the top-left screen position writes before the VGA text buffer.
- The console clamps the cursor to the final row instead of scrolling.
- Normal startup ends in a busy loop rather than an idle or scheduling mechanism.

The short startup path does not exercise all of these behaviors. Individual files compiling successfully should not be interpreted as complete runtime validation.

## Historical context and attribution

Much of the preserved kernel and HAL source is dated March–April 2010. Later archive and metadata dates do not establish continued development.

## License

ClarkeOS is available under the [MIT License](LICENSE).

Copyright © 2009-2010 Ryan Clarke

