#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello my name is northmatrix, This is my OS\nIs it the best Operating system No is it the worst maybe\nIs it the most incomplete YES\n");
  printf("Lets try and print an number to the screen below i will print my favorite number and below that a random number i also like\n");
  printf("%d\n",13);
  printf("%d\n",7188302);
} 
