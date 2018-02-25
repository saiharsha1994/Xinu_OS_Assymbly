/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;

SYSCALL getprio(int pid)
{
	 if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[3]=proc->sys_arr[3]+1;
                 proc->sys_time_arr[3] += ctr1000;
        }
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[3] += ctr1000;
        	}
		return(SYSERR);
	}
	restore(ps);
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[3] += ctr1000;
        }
	return(pptr->pprio);
}
