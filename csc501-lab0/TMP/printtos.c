/* printtos.c - printtos */

#include<stdio.h>
static unsigned long	*esp;
static unsigned long    *ebp;

/*------------------------------------------------------------------------
 *  printtos  -  Prints the stack pointer before and after function call
 *------------------------------------------------------------------------
 */

void printtos(){
	asm("movl %esp,esp");
	asm("movl %ebp,ebp");
	int x = 14;
	int y = 25;
	x = x + y;
	printf("\nvoid printtos()\n");
	printf("Before[0x%08x]:0x%08x \n",ebp+2,*(ebp+2));
	printf("After[0x%08x]:0x%08x \n",ebp, *ebp);
	int count = ebp - esp + 1;
	int i = 1;
	while(count > 0 && i < 5){
		 printf("\telement[0x%08x]:0x%08x \n",esp+i,*(esp+i));
		 count--;
		 i++;
	}
}

