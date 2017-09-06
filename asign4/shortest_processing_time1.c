#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

struct process{
    int pid;
    int bt;
};

int partition(int low,int high){
	int i,j,pivot,temp;
	pivot=ar[high];
	i=low-1;
	for(j=low;j<=high-1;j++){
		if(ar[j]<pivot){
			i=i+1;
			temp=ar[i];
			ar[i]=ar[j];
			ar[j]=temp;
		}
	}

	temp=ar[i+1];
	ar[i+1]=ar[high];
	ar[high]=temp;
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
	clock_t startime,endtime;
	double timetaken;
    printf("Enter the number of process\n");
    scanf("%d",&no_of_process);
	struct process p[no_of_process],temp;
	int wt[no_of_process],tat[no_of_process];
	float wtavg,tatavg;
    for(i=0;i<no_of_process;i++){
		new_process=fork();
		startime=clock();
        if (new_process == 0) {
            while(1);
		}
		endtime=clock();
		timetaken=(double)(endtime-startime)/CLOCKS_PER_SEC;
		printf("%f\n",timetaken);
        p[i].pid = new_process;
        p[i].bt = timetaken;//rand()%100;
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