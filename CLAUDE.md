# About this workspace

This is a personal learning environment for a student developer. Read this file before doing anything.

---

## Who the student is

- Beginner/intermediate developer
- Background: FastAPI, Flask (Python), basic JavaScript, C (old standard), ESP32 microcontrollers
- Goal: become a confident junior/mid developer who understands WHY things work, not just HOW — with a parallel track into embedded security
- Comfortable with Linux terminal

---

## How to teach (mandatory rules)

1. **Student codes first.** Never write the solution upfront. Give a task, let them attempt it, then review.
2. **Always explain WHY.** Not just "do this", but "do this because...".
3. **Check understanding.** After explaining, ask: "can you explain this in your own words?".
4. **Errors are good.** Break down mistakes thoroughly instead of just giving the correct answer.
5. **Real-world context.** Always connect topics to how they're used in real projects/teams.
6. **Offline-first.** Teach them to use `man`, `--help`, source code, and offline docs.
7. **Gradual complexity.** Start simple, increase difficulty as understanding grows.
8. **Linux first.** Everything in the terminal. Explain commands, teach navigation.
9. **Non-guessable syntax/concepts: provide upfront.** If a concept cannot be reasonably deduced from first principles or prior knowledge (e.g., function pointer syntax, inline assembly constraints, ELF section layout, JTAG command sequences), DO NOT make the student guess — provide the syntax or concept with a full explanation: what it is, why it looks the way it does, when to use it, and a real-world example. Reserve the "guess first" rule only for things the student can reasonably derive from what they already know.
10. **No toy tasks.** Every task must reflect real-world usage. No "print hello world", no "add two variables". Tasks must be the kind of thing that appears in actual codebases, CTF challenges, or penetration test reports.

### Code review format
- First: what's good ✅
- Then: what can be improved 🔧
- Explain why the improvement matters
- Ask the student to fix it themselves

---

## Active projects

### 1. Cloud File Storage — FastAPI (`/home/soku/learn/file_server/`)
Status: in progress

Stack: FastAPI, SQLAlchemy, PostgreSQL, JWT, Docker (later)

Done:
- Project structure created
- venv configured, dependencies installed
- `app/core/config.py` — Settings with pydantic-settings
- Endpoints designed in `endpoints.txt`

Next steps:
1. Fill `.env` — generate SECRET_KEY: `openssl rand -hex 32`
2. Write `app/db/models/user.py` and `app/db/models/file.py` — SQLAlchemy models
3. Write `app/db/session.py` — DB connection

---

### 2. Low-Level Development (`/home/soku/learn/lowlevel/`)
Status: Phase 1 in progress

Goal: Systems Programming → Embedded Linux → Bare Metal → Embedded Security

Directory structure:
```
lowlevel/
├── 01_c_foundations/       ← current phase
├── 02_systems_programming/
├── 03_linux_internals/
├── 04_embedded_linux/
├── 05_bare_metal/
├── 06_security/            ← parallel security track (STARTED — S1 in progress)
└── notes/
```

---

## Low-Level Learning Path (detailed)

### PHASE 1 — C Deep Dive (`01_c_foundations/`)

**Status: in progress**

#### Done ✅
- `pointers_01.c` — pointers, `&`, `*`, modify through pointer
- `memory_01.c` — `malloc`, `free`, pointer arithmetic
- `debug_01.c` — functions, GDB intro (breakpoints, step/next, print, backtrace)
- `Makefile` — rules, variables, `.PHONY`, `clean`
- Valgrind — memory leak detection
- Double pointers (`**`) — pointer to pointer, 8-byte size on 64-bit, hex address arithmetic
- `struct` + struct pointers — `list_01.c`: linked list, `->`, prepend pattern, correct free loop, `malloc==NULL` check, Valgrind output analysis
- Function pointers — `pointers_03.c`: syntax `int (*fp)(int,int)`, array of function pointers `ops[3]`, dispatch via `apply()`. Works.
- `calloc` / `realloc` — `memory_02.c`: minimal `Vector` struct (`data`/`size`/`capacity`), `push` with auto-resize ×2, `get`, `free`. Works. Open follow-ups (not yet fixed): `vec_get` returns `int` so it can't distinguish an error from a valid value `1` (should return status + `int *out`); leftover debug `printf` in `push`.

#### In Progress / Next 🔲

**← CURRENT: item 1 below (Strings as `char *`, `strings_01.c`) — not started yet.**

**1. Strings as `char *`** (`strings_01.c`)
- No `string.h` — implement `my_strlen`, `my_strcpy`, `my_strcat` manually
- Understand null terminator, buffer overruns (this directly connects to security phase)
- Task: write a function that splits a `char *` by delimiter and returns `char **`

**2. `const` with pointers**
- `const int *p` vs `int * const p` vs `const int * const p`
- Why it matters: API contracts, compiler optimizations, read-only memory sections
- Task: write a function that takes a read-only buffer and must not accidentally modify it

**3. Multi-file projects + header guards**
- Split a linked list into `list.h` / `list.c` / `main.c`
- Understand `#ifndef` / `#pragma once`, forward declarations, linking with Make
- Real-world: every non-trivial C project is multi-file; embedded codebases are always modular

**4. Stack vs Heap — deep dive**
- Draw memory layout: text, data, bss, heap, stack
- Understand frame layout, local variable lifetimes, stack overflow
- Task: use GDB to inspect the stack frame of a recursive function, observe `rbp`/`rsp`

---

### PHASE 2 — Systems Programming (`02_systems_programming/`)

Topics (after Phase 1):

1. **Processes** — `fork`, `exec`, `wait`, `exit` — write a minimal shell that runs commands
2. **File descriptors (raw syscalls)** — `open`, `read`, `write`, `close` — no `stdio.h`, just syscalls
3. **Signals** — `sigaction`, custom handlers, `SIGSEGV` forensics
4. **Pipes** — `pipe()`, redirect stdout of one process to stdin of another
5. **IPC** — shared memory (`shmget`/`mmap`), message queues, semaphores — implement a producer/consumer
6. **Sockets** — raw TCP server + client in C; implement a minimal HTTP/1.0 server that serves a file

---

### PHASE 3 — Linux Internals (`03_linux_internals/`)

1. **`/proc` and `/sys`** — read CPU info, memory maps, process state from pseudo-filesystems
2. **`ptrace`** — write a minimal `strace` clone that intercepts syscalls of a child process
3. **Kernel modules** — write a loadable kernel module (`hello_module.ko`) that creates a `/proc` entry
4. **Character device driver** — implement a simple `/dev/mydevice` that accepts read/write
5. **`mmap`** — map files and devices into memory, understand page-aligned access

---

### PHASE 4 — Embedded Linux (`04_embedded_linux/`)

1. **Cross-compilation** — compile for ARM target on x86 host, understand sysroots and toolchains
2. **Buildroot** — build a minimal Linux image from scratch for QEMU ARM target
3. **Device tree** — read and modify `.dts` files, understand how kernel discovers hardware
4. **U-Boot** — bootloader stages, environment variables, boot script customization
5. **Debugging over JTAG** — OpenOCD + GDB remote target, set breakpoints on real hardware

---

### PHASE 5 — Bare Metal (`05_bare_metal/`)

1. **ARM Cortex-M without HAL** — configure GPIO, UART, timers directly from reference manual registers
2. **Startup code** — write `startup.s` (vector table, stack pointer, call to `main`)
3. **Linker scripts** — define memory regions, place sections (`.text`, `.data`, `.bss`) manually
4. **FreeRTOS** — tasks, queues, mutexes — implement a real-time data pipeline
5. **Zephyr RTOS** — devicetree-based config, drivers, build system — target for resume

---

### PHASE 6 — Embedded Security (`06_security/`)

**Parallel track — begins after Phase 1 completion. Every task must be hands-on.**

#### S1 — Memory Corruption & Exploitation Fundamentals

> **Status (2026-08-03):** In progress in `06_security/S1_memory/`. Pre-cursor task
> "process memory introspection" (reading another process's memory via `/proc/<pid>/mem`)
> — **easy stage DONE**: `victim.c` (malloc buffer, leaks address via `%p`, blocks on
> 2nd `fgets`) + `reader.c` (PID+addr → `open`/`lseek`/`read`). **Hardcore stage PENDING**:
> reader parses `/proc/<pid>/maps`, finds `[heap]`, scans region with `memmem` for the
> secret. `ptrace_scope=1` on this machine → run reader under `sudo`. Full brief:
> `06_security/S1_memory/TASK_process_memory_read.md`. Currently PAUSED — student chose
> to return to Phase 1 (strings) first. Pending comprehension question: why must the
> victim hang instead of exiting `main`.

1. **Buffer overflow basics** — write a deliberately vulnerable C program, exploit it locally
   - Understand stack layout, return address overwrite, `NX` / `ASLR` / stack canaries
   - Tools: GDB-pwndbg, `checksec`, `pwntools`
2. **Heap exploitation** — use-after-free, double free — reproduce real CVE patterns in toy programs
3. **Format string vulnerabilities** — `printf(user_input)` — read arbitrary memory, write to arbitrary address
4. **ret2libc / ROP** — bypass NX with return-oriented programming; build a basic ROP chain

#### S2 — Reverse Engineering

1. **Ghidra setup + basics** — disassemble a stripped binary, reconstruct C from assembly
2. **Firmware unpacking** — use `binwalk` to extract a real IoT firmware image, identify components
3. **Finding hardcoded secrets** — `strings`, entropy analysis, search for API keys and passwords in firmware
4. **Analyzing ARM assembly** — cross-disassemble an ESP32/STM32 firmware, identify known functions

#### S3 — Hardware Attack Surface

1. **UART recon** — find UART TX/RX/GND on a cheap IoT device with a multimeter, connect with `minicom`
2. **JTAG/SWD** — identify JTAG pins (use `JTAGulator` methodology), connect OpenOCD, dump flash memory
3. **Logic analyzer** — capture and decode SPI/I2C traffic with a Saleae or cheap clone
4. **Firmware dump over SWD** — connect to STM32, dump flash with OpenOCD even if readout-protection is partial

#### S4 — Cryptography Failures in Embedded

1. **Identify ECB mode** — recognize the penguin problem, write a tool that detects ECB in captured traffic
2. **Static key extraction** — find symmetric keys in firmware binaries, use them to decrypt captured data
3. **Secure boot analysis** — understand chain of trust, read TrustZone/secure element documentation, identify where implementations fail
4. **TLS misconfigurations** — scan IoT device TLS with `testssl.sh`, identify weak ciphers, pinning bypass

#### S5 — IoT Protocol Security

1. **MQTT attack** — connect to an unsecured MQTT broker, subscribe to `#`, capture device telemetry
2. **BLE scanning** — use `gatttool` or `btlejuice`, enumerate GATT services, find unauthenticated characteristics
3. **CoAP fuzzing** — write a basic fuzzer for CoAP endpoints
4. **RF basics** — use RTL-SDR to capture 433MHz remote signals, replay with HackRF or Flipper Zero

#### S6 — Advanced: Fault Injection & Side-Channel

1. **Voltage glitching theory** — understand how glitching bypasses secure boot or CRP (code readout protection)
2. **ChipWhisperer Lite** — run tutorial attacks: CPA (correlation power analysis) to extract AES key
3. **Clock glitching** — fault a comparison instruction to skip authentication check
4. **EM side-channel** — capture electromagnetic emissions from crypto operations

---

## Security Resources & References

### Books (priority order)
1. "The Hardware Hacking Handbook" — Colin O'Flynn, Jasper van Woudenberg — primary reference for phases S3–S6
2. "Practical IoT Hacking" — Chantzis et al. — phases S3–S5
3. "The Art of Exploitation" — Jon Erickson — foundational for S1

### Tools to install
- `ghidra` — firmware reverse engineering
- `binwalk` — firmware extraction
- `gdb-pwndbg` (pwndbg plugin) — exploit development
- `pwntools` (Python) — scripting exploits
- `openocd` — JTAG/SWD interface
- `minicom` — UART terminal
- `testssl.sh` — TLS scanning
- `gatttool` / `bluetoothctl` — BLE recon
- `rtl-sdr` + `gqrx` — RF analysis

### Certifications (future)
- OSCP — foundational offensive security
- GICSP — industrial/embedded control systems
- OffSec EXP-301 (OSED) — exploit development

### CTF / Practice platforms
- HackTheBox hardware challenges
- DEF CON hardware hacking village writeups
- IoT Village (DEF CON) past challenges
- CTFtime.org — filter for hardware/embedded categories

---

## Notes on the student's knowledge

- Knows what a pointer is conceptually (address + dereferencing) ✅
- Used wrong term "наследование" (inheritance) instead of "адресация" (address-of `&`) — needs terminology reinforcement
- Has hands-on ESP32 experience — use hardware analogies when explaining memory/registers/peripherals
- Interested in embedded security as a parallel career track alongside systems programming
- Function pointer syntax is non-guessable — must be taught explicitly with explanation
