/* printprocstks.c - printprocstks */

#include<stdio.h>
#include<kernel.h>
#include<proc.h>
static unsigned long *esp;

/*------------------------------------------------------------------------
 *  printprocstks  -  Prints the process greater than the priority specified
 *------------------------------------------------------------------------
 */

void printprocstks(int priority){
	int i;
	printf("\nvoid printprocstks(int priority)\n");
	for(i=1;i<NPROC;i++){
		struct pentry *proc = &proctab[i];
		if(proc->pprio > priority){
			printf("Process [%s]\n",proc->pname);
			printf("\tpid: %d\n",i);
			printf("\tpriority: %d\n",proc->pprio);
			printf("\tbase: 0x%08x\n",proc->pbase);
			printf("\tlimit: 0x%08x\n",proc->plimit);
			printf("\tlen: %d\n",proc->pstklen);
			if(i == currpid){
				asm("movl %esp,esp");
				printf("\tpointer: 0x%08x\n",esp);
			}	
			else{
				printf("\tpointer: 0x%08x\n",proc->pesp);
			}
		} 
	}
}
