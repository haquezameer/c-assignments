#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

struct process{
    int pid;
    int bt;
};

struct process p[1000000];

int partition(int low,int high){
	int i,j;
	struct process pivot,temp;
	pivot=p[high];
	i=low-1;
	for(j=low;j<=high-1;j++){
		if(p[j].bt<pivot.bt){
			i=i+1;
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}
	}

	temp=p[i+1];
	p[i+1]=p[high];
	p[high]=temp;
	return i+1;
}

void quicksort(int low,int high){
	if(low<high){
		int q;
		q=partition(low,high);
		quicksort(low,q-1);
		quicksort(q+1,high);
	}
}

int main()
{   
    int no_of_process,i,new_process,j;
    printf("Enter the number of process\n");
    scanf("%d",&no_of_process);
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
	quicksort(0,no_of_process-1);
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