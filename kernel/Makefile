I_DIR = include
O_DIR = build
L_DIR = lib
B_DIR = bin
S_DIR = src

CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -Wno-unused-parameter -I$(I_DIR) -I$(L_DIR) -L$(L_DIR)
AFLAGS=

AS=i686-elf-as
CC=i686-elf-gcc

default: run
all: init kernel
run: all
	qemu-system-i386 -kernel bin/kernel.bin
#$(L_DIR)/%.o: stdlib

$(O_DIR)/%.o: $(S_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(O_DIR)/%.o: $(S_DIR)/%.s
	$(AS) $< -o $@ $(AFLAGS)


kernel: $(addprefix $(O_DIR)/, $(addsuffix .o, $(basename $(shell cd $(S_DIR) && find $@ -name '*.c') $(shell cd $(S_DIR) && find $@ -name '*.s'))))
	$(CC) $^ -o $(B_DIR)/kernel.bin -T linker.ld -nostdlib -lgcc $(CFLAGS)


init:
	mkdir -p $(O_DIR)/isrs
	mkdir -p $(B_DIR)
	mkdir -p $(L_DIR)
clean:
	rm -rf ./$(O_DIR)
	rm -rf ./$(B_DIR)

