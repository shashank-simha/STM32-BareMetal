CC=arm-none-eabi-gcc
MACH=cortex-m4

LD_SRC= linker_stm32f446re.ld

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(LD_SRC) -Wl,-Map=main.map

all: main.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^

startup_stm32f446re.o:startup_stm32f446re.c
	$(CC) $(CFLAGS) -o $@ $^

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^

sysmem.o:sysmem.c
	$(CC) $(CFLAGS) -o $@ $^

main.elf: main.o led.o startup_stm32f446re.o syscalls.o sysmem.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf *.map
