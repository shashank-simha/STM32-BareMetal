CC=arm-none-eabi-gcc
MACH=cortex-m4

LD_SRC= linker_stm32f446re.ld

CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall
LDFLAGS= -nostdlib -T $(LD_SRC)

all: main.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^
	
startup_stm32f446re.o:startup_stm32f446re.c
	$(CC) $(CFLAGS) -o $@ $^

main.elf: main.o led.o startup_stm32f446re.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf
