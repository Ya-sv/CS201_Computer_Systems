#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>

#define numProgramRun 10 
#define MAX_NUM 200

volatile sig_atomic_t flag;


//Set flag equals 1
void signal_handler()
{
	flag = 1;
}


// Do some busy works as tasks described
void busyWorksParent(pid_t child) 
{
	int j = 0;
     	int sum1 = 0;
	int hitVal2 = 0;
	srand((unsigned)time(NULL)*7);
     	kill(getpid(),SIGINT);// send a signal to child process
     	while(j < numProgramRun)	
     	{	
         	if(flag != 0)
	 	{	
	   		hitVal2 = (rand()%50)+1;
	   		sum1 = sum1 +hitVal2;
	   		printf("Parent %d got with %d",getppid(),hitVal2);
	   		printf(". damage is now %d\n",sum1);
           		flag = 0;
	   		kill(child,SIGINT);
           		if(sum1 >= MAX_NUM)
	   		{			
				printf("Parent has died!\n");
 				int status;
				waitpid(-1,&status,0);
				break;
           		}	
			if((sum1 < MAX_NUM) && (j == numProgramRun-1))
           		{	
				printf("Parent has surrived!\n");
				break;
	   		}
	 	}	
		int t = (rand()% 3)+1;
		sleep(t);
		//printf("Sleep %d seconds in the parent process\n",t);
		j++;			 
	}	
}


int main()
{
	flag = 0;
	pid_t pid1;
        srand(time(NULL));
	signal(SIGINT,signal_handler);// install signal for SIGINT
	pid1= fork();
	if (pid1== -1)// ERROR checking
	{	
		printf("Error in fork fucntion\n");
        }
	else if(pid1 == 0)// Child process
        {
      		int i = 0;
		int sum = 0;
		int hitVal = 0;
	 	srand((unsigned)time(NULL)*3);
	    	while(i < numProgramRun)      
      		{
	  		if (flag != 0)
	 		{	
	  			hitVal = (rand()%50)+1;
	  			sum = sum + hitVal;
          			printf("Child %d got with %d",getpid(),hitVal);
          			printf(". damage is now %d\n",sum);
	  			kill(getppid(),SIGINT);
				sigset_t mask,prevMask;
				sigemptyset(&mask);
				sigaddset(&mask,SIGINT);
				sigprocmask(SIG_BLOCK,&mask,&prevMask);
				sigprocmask(SIG_SETMASK,&prevMask,NULL);
          			flag = 0;
          			if(sum >= MAX_NUM)
         	 		{		
          				printf("Child has died!\n");
	   				exit(0);
          			}
				if((sum < MAX_NUM)&& (numProgramRun == i))
				{
					printf("child has survived!\n");
				}
			}	
			i++;
         		int n = (rand()%3)+1;
	 		sleep(n);
		}
	}  
	else // Parent process 
  	{      
   		busyWorksParent(pid1);
      		//use default waitpid function to wait for every child process to finish  
		int status;   
      		waitpid(-1,&status,0);
      		sigset_t mask, prev_mask;
                sigemptyset(&mask); // Create an empty mask
		sigaddset(&mask,SIGINT);
		sigprocmask(SIG_BLOCK, &mask,&prev_mask);
		sigprocmask(SIG_SETMASK,&prev_mask,NULL);
      
 	 }  
  
	return 0;
}
