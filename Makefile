TARGET = LainaOSx86.bin
ISO    = LainaOSx86.iso

CC     = x86_64-elf-gcc
LD     = x86_64-elf-ld
AS     = x86_64-elf-as

CFLAGS = -std=gnu99 -ffreestanding -m64 -O2 -Wall -Wextra
LDFLAGS = -T linker.ld -nostdlib

SRC = src/kernal.c \
      src/vga.c \
      src/serial.c \
      src/gdt.c \
      src/idt.c \
      src/isr.c \
      src/irq.c \
      src/shell.c \
      src/shell_commands.c

OBJ = $(SRC:.c=.o) src/boot.o

all: $(ISO)

src/boot.o: src/boot.s
    $(AS) --64 $< -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
    $(LD) $(LDFLAGS) -o $(TARGET) $(OBJ)

$(ISO): $(TARGET)
    mkdir -p iso/boot/grub
    cp $(TARGET) iso/boot/LainaOSx86.bin
    cp grub.cfg iso/boot/grub/grub.cfg
    grub-mkrescue -o $(ISO) iso

clean:
    rm -f $(OBJ) $(TARGET)
    rm -rf iso

run: $(ISO)
    qemu-system-x86_64 -cdrom $(ISO)

.PHONY: all clean run
