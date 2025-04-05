#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>
#include <kernel/multiboot.h>

void kernel_main(multiboot_info_t *mbd, unsigned int magic) {
	terminal_initialize();
  /* Make sure the magic number matches for memory mapping*/
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("invalid magic number!");
    }

    /* Check bit 6 to see if we have a valid memory map */
    if(!(mbd->flags >> 6 & 0x1)) {
        printf("invalid memory map given by GRUB bootloader");
    }

    printf("OS Memory Map\n\n");
    /* Loop through the memory map and display the values */
    unsigned int i;
    for(i = 0; i < mbd->mmap_length; 
        i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* mmmt = 
            (multiboot_memory_map_t*) (mbd->mmap_addr + i);

        printf("SA: %lx | L: %lx | S: %lx | T: %d\n",
            mmmt->addr, mmmt->len, mmmt->size, mmmt->type);

        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            /* 
             * Do something with this memory block!
             * BE WARNED that some of memory shown as availiable is actually 
             * actively being used by the kernel! You'll need to take that
             * into account before writing to memory!
             */
        }
    }
    printf("\nWelcome to KrustOS\n");
} 
