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
    int no_of_process,i,new_process,j;
    printf("Enter the number of process\n");
    scanf("%d",&no_of_process);
	struct process p[no_of_process],temp;
	int wt[no_of_process],tat[no_of_process];
	float wtavg,tatavg;
    for(i=0;i<no_of_process;i++){
        new_process=fork();
        if (new_process == 0) {
            while(1);
        }
        p[i].pid = new_process;
        p[i].bt = rand()%100;
        kill(new_process,SIGKILL);
    }
	for(i=0;i<no_of_process-1;i++){
		for(j=0;j<no_of_process-1-i;j++){
			if(p[j].bt>p[j+1].bt){
				temp=p[j+1];
				p[j+1]=p[j];
				p[j]=temp;
			}
		}
	}
	wt[0]=wtavg=0;
	tat[0]=tatavg=p[0].bt;
	for(i=1;i<no_of_process;i++){
		wt[i]=wt[i-1]+p[i-1].bt;
		tat[i]=tat[i-1]+p[i].bt;
		wtavg+=wt[i];
		tatavg+=tat[i];
	}
	printf("\n%-10s %-10s %-10s %-10s\n","ProcessId","Burst Time","Waiting Time","Turn Around Time");
	for(i=0;i<no_of_process;i++){
		printf("%-10d %-10d %-10d %-10d\n",p[i].pid,p[i].bt,wt[i],tat[i]);
	}
	printf("Average waiting time : %f\n",wtavg/no_of_process);
	printf("Average turn around time : %f\n",tatavg/no_of_process);
    return 0;
}