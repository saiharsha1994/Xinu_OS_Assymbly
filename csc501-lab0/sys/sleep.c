/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */

extern int Start_Stop;
unsigned long   ctr1000; 

SYSCALL	sleep(int n)
{
	if(Start_Stop==1){
		 struct pentry *proc = &proctab[currpid];
       		 proc->sys_arr[18]=proc->sys_arr[18]+1;
		 proc->sys_time_arr[18] += ctr1000;
	}
	STATWORD ps;    
	if (n<0 || clkruns==0){
		if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_time_arrend[18] += ctr1000;
        	}
		return(SYSERR);
	}

	if (n == 0) {
	        disable(ps);
		resched();
		restore(ps);
		if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_time_arrend[18] += ctr1000;
        	}
		return(OK);
	}
	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0)
		sleep10(10*n);
	if(Start_Stop==1){
		 struct pentry *proc = &proctab[currpid];
		 proc->sys_time_arrend[18] += ctr1000;
	}	
	return(OK);
}
