// Priority Preemptive with Arrival Time
// Mounish Sai (https://github.com/pvsmounish)

#include<iostream>
#include<limits>
using namespace std;

class Process{
    public:
        string processName;
        int arrivalTime;
        int burstTime;
        int priority;

        int remainingTime;

		int responseTime;
        int completionTime;
    
        int waitingTime;
        int turnAroundTime;

        void initialize(){
        	remainingTime = burstTime;
        }
};

int main(){
    int numOfProcesses;
    cout << "Enter no. of processes: ";
    cin >> numOfProcesses;

    Process processes[numOfProcesses];

    for(int n=0;n<numOfProcesses;n++){
        cout << "\nEnter Process Name for " << (n+1) << ": ";
        cin >> processes[n].processName;
        cout << "Enter Arrival Time for Process " << (n+1) << ": ";
        cin >> processes[n].arrivalTime;
        cout << "Enter Burst Time for Process " << (n+1) << ": ";
        cin >> processes[n].burstTime;
        cout << "Enter Priority for Process " << (n+1) << ": ";
        cin >> processes[n].priority;

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

    int currentTime = 0;

    while(true){

    	int currentHighestPriorityIndex = -1;
    	int currentHighestPriority = numeric_limits<int>::max();

    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++){
    		if(processes[i].remainingTime > 0){
    			isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime){
                    if(processes[i].priority < currentHighestPriority){
                        currentHighestPriority = processes[i].priority;
                        currentHighestPriorityIndex = i;
                    }
                }
    			
    		}
    	}

    	if(isAllCompleted){
    		break;
    	}

		if(processes[currentHighestPriorityIndex].remainingTime == processes[currentHighestPriorityIndex].burstTime){
			processes[currentHighestPriorityIndex].responseTime = currentTime;
		}

    	processes[currentHighestPriorityIndex].remainingTime--;
        currentTime++;

		if(processes[currentHighestPriorityIndex].remainingTime == 0){
			processes[currentHighestPriorityIndex].completionTime = currentTime;
		}
    }


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
