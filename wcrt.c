#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "PeriodicTask.h"



int *task_wcrt(system_T s, elem_task_T task)
{
	int w0 = task.cost;
	int num_highPriority = task.priority;
	int *wcrt;
	wcrt = (int *)malloc(sizeof(int)*2);
	wcrt[0] = w0;
	wcrt[1] = w0;
	if (num_highPriority>0){

		int *table_exeT=(int *)malloc(sizeof(int)*num_highPriority);
		int *table_intT=(int *)malloc(sizeof(int)*num_highPriority);
		int i=0;
		if(!system_empty(s)){
			transaction_T *current = s.transactions;
			while (current != NULL) {
				if(!trans_empty(current->trans)){
					periodicTask_T *current_task = current->trans.tasks;

					while (current_task != NULL) {
						if (current_task->task.priority < task.priority){
							table_exeT[i] = current_task->task.cost;
							table_intT[i] = current_task->task.period;
							i++;
						}
						current_task = current_task->next;
				    	}
				}
				current = current->next;
		    	}

		}
		table_exeT[i] = task.cost; 
		table_intT[i] = task.period;
		printf("number: %d\n", i);
		int max_wcrt=0;
		int response_time=0;
		int q=0;
		int q1=1;
		w0=task.cost;
		int w1=w0;
		int n=0;
		int R1=0, R2=0;
		// maxime busy window
		while(1){
			int sum=0;
			for(int j=0;j<num_highPriority;j++){
			
				sum=sum+(w0+table_intT[j]-1)/table_intT[j]*table_exeT[j];
			}
			
			w1=sum;
			// convergence
			if(w1==w0){
				n = (w0+task.period-1)/task.period;
				break;
			}else{
				w0=w1;
			}
			printf("sum: %d\n", sum);
		}

		// check all possibilities
		if(n>0){
			printf("n: %d\n", n);
			for(int k=0;k<n;k++){
				int t01=1, t02=1;
				int t1=t01, t2=t02;
				int trouve1=0,trouve2=0;
				while(1){

					int sum1=0, sum2=0;
					for(int j=0;j<num_highPriority-1;j++){

						// method classic
						if(!trouve1)
						sum1=sum1+(t01/table_intT[j]+1)*table_exeT[j] ;

						// new method
						if(!trouve2)
						sum2=sum2+((t02+table_intT[j]-1)/table_intT[j]+(t02%table_intT[j]==0))*table_exeT[j];

					}

					if(!trouve1){
						t1 = sum1 + k*task.cost;
						if(t1==t01){
							R1 = t1 - k*(table_intT[num_highPriority-1]) + task.cost;
							if(R1>wcrt[0]) wcrt[0]=R1;
							trouve1=1;
							//printf("sum1: %d\n", sum1);
						}else t01 = t1;
					}

					if(!trouve2){
						t2=sum2 + k*task.cost;
						// printf("t02: %d\n", t02);
						// printf("t2: %d\n", t2);
						if(t2==t02){
							R2 = t2 - k*(table_intT[num_highPriority-1]) + task.cost;
							if(R2>wcrt[1]) wcrt[1]=R2;
							trouve2=1;
							//printf("sum2: %d\n", sum2);
						}else t02 = t2;
					}

					if(trouve1&&trouve2) {
						
						
						break;
					}
				}
			}

		}
	}

	return wcrt;
	

}
