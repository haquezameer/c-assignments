#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

struct process{
    int pid;
    int bt;
};

int main()
{   
    int no_of_process,i,new_process;
    printf("Enter the number of process\n");
    scanf("%d",&no_of_process);
    struct process p[no_of_process];
    for(i=0;i<no_of_process;i++){
        new_process=fork();
        if (new_process == 0) {
            // This is a child process. Just spin until killed.
            while(1);
        }
        p[i].pid = new_process;
        p[i].bt = rand()%100;
        kill(new_process,SIGKILL);
    }
    for(i=0;i<no_of_process;i++)
		printf("process %d and bt %d\n",p[i].pid,p[i].bt);
	
    return 0;
}