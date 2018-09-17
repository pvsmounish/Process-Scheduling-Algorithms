// Round Robin with Arrival Time
//Mounish Sai (https://github.com/pvsmounish)

#include<iostream>
#define SIZE 5
using namespace std;

int items[20];
int front = -1, rear =-1;

int isEmpty(){
    if(front == -1) return 1;
    return 0;
}

void enQueue(int element){
        if(front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        items[rear] = element;
}


int deQueue(){
    int element;
    element = items[front];
    if (front == rear){
        front = -1;
        rear = -1;
    } 
    else {
        front = (front + 1) % SIZE;
    }
    return(element);
    
}

    void display()
    {
        
        int i;
        if(isEmpty()) {
            cout << endl << "Empty Queue" << endl;
        }
        else
        {
            cout << "Front -> " << front;
            cout << endl << "Items -> ";
            for(i=front; i!=rear;i=(i+1)%SIZE)
                cout << items[i];
            cout << items[i];
            cout << endl << "Rear -> " << rear;
        }
    }

class Process{
    public:
        string processName;
        int burstTime;
        int arrivalTime;

        int waitingTime;
        int completionTime;
        int responseTime;
        int turnAroundTime;

        bool isProcessCompleted;
        bool isInQueue;
        int remainingTime;

        void initialize(){
        	waitingTime = 0;
        	responseTime = 0;
        	turnAroundTime = 0;
        	isProcessCompleted = false;
        	remainingTime = burstTime;
            isInQueue = false;
        }
};

int main(){
    int numOfProcesses;
    int timeQuantum;
    int currentTime = 0;

    cout << "\nEnter Time Quantum: ";
    cin >> timeQuantum;

    cout << "\nEnter no. of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];

    for(int n=0;n<numOfProcesses;n++){
        cout << "Enter Process Name for " << (n+1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n+1) << ": ";
        cin >> processes[n].burstTime;
        processes[n].initialize();
    }

    cout << "\n" << endl;

    for(int i=0;i<numOfProcesses-1;i++){
        for(int j=i+1;j<numOfProcesses;j++){
            if(processes[j].arrivalTime < processes[i].arrivalTime){
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }


    currentTime = processes[0].arrivalTime;
    enQueue(0);
    processes[0].isInQueue = true;
    printf("\n Initial %d", 1);

    
    while(isEmpty() == 0){
        
        int i = deQueue();
        processes[i].isInQueue = false;
       
        printf("/n Removed %d", (i+1));
        
        if(!processes[i].isProcessCompleted && processes[i].arrivalTime <= currentTime){
        	if(processes[i].remainingTime == processes[i].burstTime){
        		processes[i].responseTime = currentTime;
        	}

        	if(processes[i].remainingTime <= timeQuantum){
        		currentTime += processes[i].remainingTime;
        		processes[i].completionTime = currentTime;
        		processes[i].remainingTime = 0;
        		processes[i].isProcessCompleted = true;
        	}
        	else{
        		currentTime += timeQuantum;
        		processes[i].remainingTime -= timeQuantum;
        	}

            if(currentTime < processes[numOfProcesses-1].arrivalTime){
                for(int j=i;j<numOfProcesses;j++){
                    if(processes[j].arrivalTime <= currentTime && !processes[j].isProcessCompleted && !processes[j].isInQueue){
                        enQueue(j);
                        processes[j].isInQueue = true;
                        printf("\n Added %d", (j+1));
                    }
                }

               
            }

            if(!processes[i].isProcessCompleted){
                    printf("\n Added %d", (i+1));
                    enQueue(i);
                    processes[i].isInQueue = true;
            }
           
            
        }
    }



    // for(int i=0;i<numOfProcesses;i = (i+1)%numOfProcesses){

    //     if(!processes[i].isProcessCompleted && processes[i].arrivalTime <= currentTime){
    //     	if(processes[i].remainingTime == processes[i].burstTime){
    //     		processes[i].responseTime = currentTime;
    //     	}

    //     	if(processes[i].remainingTime <= timeQuantum){
    //     		currentTime += processes[i].remainingTime;
    //     		processes[i].completionTime = currentTime;
    //     		processes[i].remainingTime = 0;
    //     		processes[i].isProcessCompleted = true;
    //     	}
    //     	else{
    //     		currentTime += timeQuantum;
    //     		processes[i].remainingTime -= timeQuantum;
    //     	}

    //     }

    //     bool flag = true;
    // 	for(int i=0;i<numOfProcesses;i++){
    // 		if(!processes[i].isProcessCompleted){
    // 			flag = false;
    // 			break;
    // 		}
    //     }
    //     if(flag){
    //     	break;
    //     }



    // }


    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
  

    for(int n=0;n<numOfProcesses;n++){
        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;
        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n" << endl;

        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }


	cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
	cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;


    return 0;
}
