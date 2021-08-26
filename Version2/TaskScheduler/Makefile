CC=arm-none-eabi-gcc
MACH=cortex-m4

CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall

all:main.o led.o startup_stm32f446re.o

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

led.o:led.c
	$(CC) $(CFLAGS) -o $@ $^
	
startup_stm32f446re.o:startup_stm32f446re.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf
