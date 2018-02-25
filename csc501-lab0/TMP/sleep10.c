/* sleep10.c - sleep10 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep10  --  delay the caller for a time specified in tenths of seconds
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;
SYSCALL	sleep10(int n)
{
	 if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[19]=proc->sys_arr[19]+1;
                 proc->sys_time_arr[19] += ctr1000;
        }
	STATWORD ps;    
	if (n < 0  || clkruns==0){
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[19] += ctr1000;
        }
		return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep10(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n*100);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[19] += ctr1000;
        }
	return(OK);
}
