/* user.c - main */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <Lab0.h>

/*------------------------------------------------------------------------
 *  main  --  user main program
 *------------------------------------------------------------------------
 */
static unsigned long	*esp;
int prX, prY, prZ;
void halt();
prch(c)
char c;
{
	int i;
	sleep(1);	
}
int main()
{

	printf("\n\nHello World, Xinu lives\n\n");
	long x = zfunction(0xaabbccdd);
	printf("%x \n",x);
	printsegaddress();
	printtos();
	syscallsummary_start();
	resume(prX = create(prch,2000,20,"proc X",1,'A'));
	resume(prY = create(prch,2000,20,"proc Y",1,'B'));
	sleep(10);
	syscallsummary_stop();
	printsyscallsummary();
	printprocstks(5);
	return 0;
}
