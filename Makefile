C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o cpu/interrupt.o} 

all: os-image.bin

os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin


kernel_read: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o kernel_read.bin -Ttext 0x1000 $^
	objdump -s -d -M Intel kernel_read.bin > res
	

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o kernel.bin -no-pie -Ttext 0x1000 $^ --oformat binary
	
%.o: %.c ${HEADERS}
	gcc -m32 -fno-PIC -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@ 

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o
