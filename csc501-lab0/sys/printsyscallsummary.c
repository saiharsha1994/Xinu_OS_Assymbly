/* printsyscallsummary.c - printsyscallsummary syscallsummary_start syscallsummary_stop */

#include<stdio.h>
#include<kernel.h>
#include<proc.h>
extern int Start_Stop;
char names[27][30]={"freemem","chprio","getpid","getprio","gettime","kill","receive","recvclr","recvtim","resume","scount","sdelete","send","setdev","setnok","screate","signal","signaln","sleep","sleep10","sleep100","sleep1000","sreset","stacktrace","suspend","unsleep","wait"};

/*------------------------------------------------------------------------
 *  printsyscallsummary  -  Prints the process with system calls
 *------------------------------------------------------------------------
 */


void syscallsummary_start(){
	Start_Stop=1;
	int i=0, j=0;
	for(i=0; i<NPROC; i++){
	struct pentry *proc = &proctab[i];
		for(j=0; j<27; j++){
			proc->sys_arr[j]=0;
			proc->sys_time_arr[j]=0;
			proc->sys_time_arrend[j]=0;
		}
	}
}

void syscallsummary_stop(){
	Start_Stop=0;
}

void printsyscallsummary(){
	int i = 0, j = 0;
	printf("\nvoid printsyscallsummary()\n");
	for(j=1; j<NPROC; j++){
		struct pentry *proc = &proctab[j];
		if(strcmp(proc->pname,"") != 0)
			printf("Process [pid:%d]\n",j);
		for(i=0; i<27; i++){
			if(proc->sys_arr[i]>0){
				 long a = 0;
				 if(proc->sys_time_arr[i]<=proc->sys_time_arrend[i]){
					a = (proc->sys_time_arrend[i]-proc->sys_time_arr[i])/proc->sys_arr[i];}
				 printf("\tSyscall: %s , count: %d, average execution time: %d (ms)\n",names[i],proc->sys_arr[i],a);
			}
       		 }		
	
	}
}
