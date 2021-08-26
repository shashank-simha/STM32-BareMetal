# Compilation stages

1. Preprocessing stage: C macros, conditional compilation macros are resolved and processed
    > .c files converted to .i files
2. Code generation stage: source files are translated into assembly language(processor architecture mnemonics)
    > .i files converted to .s files
3. Assembles stage: Assembly level mnemonics converted into opcodes(machine codes) and relocatable object file is generated
    > .s files converted to .o files
4. Linking stage: All relocatable object files and other libraries(.a) are linked together to create executable and debug file
    > .o and .a files linked(with the help of .ld) to generate .elf

# Compilation commands
1. Compile and assemble(do not link) the source files
    Ex.
    ```sh
    $ arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -c main.c -o main.o
    ```
2. Compile (do not assemble or link) the source files
    Ex.
    ```sh
    $ arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -S main.c -o main.s
    ```
3. Link the object files
    Ex.
    ```sh
    $ arm-none-eabi-gcc -nostdlib -T linker_stm32f446re.ld *.o -o main.elf
    ```
4. Use "arm-none-eabi-objdump" to analyse the object or executable files
    Ex.
    ```sh
    $ arm-none-eabi-objdump -h main.elf
    ```
5. Use "arm-none-eabi-nm" to list the symbols in an object or executable file
    Ex.
    ```sh
    $ arm-none-eabi-nm main.elf
    ```
# Sections of Relocatable object file
| Section | Description | Preferred Location |
| ------- | ----------- | ------------------ |
| __.data__ | contains initialized data | RAM |
| __.rodata__ | contains read only data | ROM |
| __.bss__ | contains uninitialized data | RAM |
| __.text__ | contains code(instructions) | ROM |
| __user defined sections__ | contains data/code programmer demands to put in these sections | RAM/ROM |
| __special sections__ | contains special data added by compiler | RAM |

*__Note:__* RAM => Flash

## Recommended order of sections
| Code Memory(Flash) | Data Memory (SRAM) |
| ----------- | ------------------ |
| Unused Code memory | Stack |
| .data (initialized global and static variables) | Unused RAM |
| .rodata | heap |
| .text | .bss (uninitialized global and static variables) |
| Vector Table | .data (initialized global and static variables) |
| 0x0800 0000 | 0x2000 0000 |

*__Note:__* C start-up: copy data section from ROM to RAM and reserve some space for .bss section with the help of startup file, and call main function

# Startup file
#### Function Attributes
Weak: Lets the programmer to override already defined weak functionality(dummy) with the same function name
Alias: Lets the programmer to give alias name for a function

# Linker Script
#### Linker and Locator
Linker: merge similar sections of different object files and resolve undefined symbols of different object files.
Locator(part of linker): how to merge different sections and assigns mentioned addresses to different sections
*__Note:__* .elf is loaded into Flash memory(ROM)

##### Linker script commands
1. ENTRY: 
    - Sets "Entry point address" info in header of final elf. In this case, Reset_Handler.
    - Not mandatory but required when debugging using a debugger(GDB)
    - Syntax: ENTRY(_symbol_name_) Ex. ENTRY(Reset_Handler)
2. MEMORY
    - Describes the different memories present in the target and their start address and size info
    - Typically one memory command is used in a linker script
    - Syntax: 
        MEMORY
        {
            name(attr): ORIGIN = origin, LENGTH = len
        }
3. SECTIONS
    - Create different output sections in the final elf
    - Instruct the placement of section in a memory region
4. KEEP
5. ALIGN:
    - align the section to word boundary
    - Syntax: ALIGN(2^n), Ex. ALIGN(4)
6. AT>
- *__Note:__* Location counter: special linker symbol denoted by '.'. Used to track and define boundaries of various sections
    - automatically updated with location information
    - appears only inside SECTIONS command
    - always tracks VMA(Virtual Memory Address) not LMA(Load Memory Address)

# Semi Hosting
- Useful to print messages on openocd terminal
- Depends on some host such as openocd
- Use rdimon specs instead of glib nano
- __Steps__
    - update linker flags to use rdimon specs instead of nano specs in Makefile
        ```
        --specs=nano.specs  to --specs=rdimon.specs in LD_FLAGS
        ```
    - Remove syscalls and sysmem dependencies from recipe in Makefile
    - Call 'initialise_monitor_handles()' in Reset_Handler before calling main
    - Launch openocd with suitable config file
        ```
        $ openocd -f stm32_nucleo_f446re.cfg
        ```
    - launch arm-none-eabi-gdb from a different terminal and flash the image
        ```
        $ arm-none-eabi-gdb
        
        (gdb) monitor flash write_image erase main_sh.elf
        (gdb) monitor reset init
        ```
    - Enable semihosting on openocd (execute the command in gdb)
        ```
        (gdb) monitor arm semihosting enable
        ```
    - resume the execution of the program and debug statement will be printed on openocd terminal
        ```
        (gdb) monitor resume
        ```
    *__Note:__* Even without semihosting, openocd and gdb can be used for flashing and debugging on the similar lines.

_Reference:_
1. [https://gcc.gnu.org/onlinedocs/gcc/](https://gcc.gnu.org/onlinedocs/gcc/)

_Credits:_ [Kiran Nayak](https://github.com/niekiran)
