/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <proc.h>

/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
extern int Start_Stop;
unsigned long   ctr1000;

SYSCALL	freemem(struct mblock *block, unsigned size)
{
	if(Start_Stop==1){
                 struct pentry *proc = &proctab[currpid];
                 proc->sys_arr[0]=proc->sys_arr[0]+1;
                 proc->sys_time_arr[0] += ctr1000;
        }
	STATWORD ps;    
	struct	mblock	*p, *q;
	unsigned top;

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end)){
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[0] += ctr1000;
       		 }	
		return(SYSERR);
	}
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);
		if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[0] += ctr1000;
        	}
		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);
	if(Start_Stop==1){
                struct pentry *proc = &proctab[currpid];
                proc->sys_time_arrend[0] += ctr1000;
        }
	return(OK);
}
