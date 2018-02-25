/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <proc.h>

extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;

SYSCALL	gettime(long *timvar)
{
   	 if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[4]=proc->sys_arr[4]+1;
                 proc->sys_time_arr[4] += ctr1000;
        }

	 /* long	now; */

	/* FIXME -- no getutim */
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[4] += ctr1000;
        }
    return OK;
}
