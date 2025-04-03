#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>
#include <kernel/multiboot.h>

void kernel_main(multiboot_info_t *mb_info) {
	terminal_initialize();
  while ((uint32_t) mmap < mb_info->mmap_addr + mb_info->mmap_length) {
        printf("Base: %d%d, Length: %d%d, Type: %d\n", 
               mmap->base_addr_high, mmap->base_addr_low, 
               mmap->length_high, mmap->length_low, 
               mmap->type);
        mmap = (multiboot_mmap_t *) ((uint32_t) mmap + mmap->size + 4);
  }
  printf("Welcome to KrustOS\n");
  printf("This is a operating system developed in C\n");
  printf("It was developed by Northmatrix\n");
  printf("This is my favourite number %d\n",48172);
} 
