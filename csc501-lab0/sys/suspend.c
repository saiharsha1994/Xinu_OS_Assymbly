/* suspend.c - suspend */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  suspend  --  suspend a process, placing it in hibernation
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;
SYSCALL	suspend(int pid)
{
	if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[24]=proc->sys_arr[24]+1;
                 proc->sys_time_arr[24] += ctr1000;
        }
	STATWORD ps;    
	struct	pentry	*pptr;		/* pointer to proc. tab. entry	*/
	int	prio;			/* priority returned		*/

	disable(ps);
	if (isbadpid(pid) || pid==NULLPROC ||
	 ((pptr= &proctab[pid])->pstate!=PRCURR && pptr->pstate!=PRREADY)) {
		restore(ps);
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[24] += ctr1000;
	        }
		return(SYSERR);
	}
	if (pptr->pstate == PRREADY) {
		pptr->pstate = PRSUSP;
		dequeue(pid);
	}
	else {
		pptr->pstate = PRSUSP;
		resched();
	}
	prio = pptr->pprio;
	restore(ps);
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[24] += ctr1000;
        }
	return(prio);
}
