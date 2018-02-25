/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;
SYSCALL	send(int pid, WORD msg)
{
	if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[12]=proc->sys_arr[12]+1;
                 proc->sys_time_arr[12] += ctr1000;
        }
	STATWORD ps;    
	struct	pentry	*pptr;
	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[12] += ctr1000;
                }
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	 printf("start stop %d",Start_Stop);
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[12] += ctr1000;
                }
	return(OK);
}
