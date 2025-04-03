#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello my name is northmatrix, This is my OS\nIs it the best Operating system No is it the worst maybe\nIs it the most incomplete YES\n");
  char str[20];
  itoa(144,str,10);
  printf(str);
} 
