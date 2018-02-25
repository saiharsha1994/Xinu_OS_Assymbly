/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;

SYSCALL sleep1000(int n)
{
	if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[21]=proc->sys_arr[21]+1;
        	 proc->sys_time_arr[21] += ctr1000;         
	        }
	STATWORD ps;    

	if (n < 0  || clkruns==0){
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[21] += ctr1000;
        }
		return(SYSERR);
	}
	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[21] += ctr1000;
        }
	return(OK);
}
