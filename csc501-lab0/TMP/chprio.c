/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;

SYSCALL chprio(int pid, int newprio)
{
	if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[1]=proc->sys_arr[1]+1;
                 proc->sys_time_arr[1] += ctr1000;
        }
	STATWORD ps;    
	struct	pentry	*pptr;

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[1] += ctr1000;
       		 }
		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);
	 if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[1] += ctr1000;
        }
	return(newprio);
}
