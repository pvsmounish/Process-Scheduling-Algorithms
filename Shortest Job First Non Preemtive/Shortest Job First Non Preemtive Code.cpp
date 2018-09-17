// Shortest Job First (SJF) Non Preemtive with Arrival Time
// Mounish Sai (https://github.com/pvsmounish)

#include<iostream>
#include<limits>
using namespace std;

class Process{
    public:
        string processName;
        int arrivalTime;
        int burstTime;

        bool isCompleted;

		int responseTime;
        int completionTime;
        
        int waitingTime;
        int turnAroundTime;

        void initialize(){
        	isCompleted = false;
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

    	int currentShortestJobIndex = -1;
    	int currentShortestJobRemainingTime = numeric_limits<int>::max();

    	bool isAllCompleted = true;

    	for(int i=0;i<numOfProcesses;i++){
    		if(!processes[i].isCompleted){
    			isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime){
                    if(processes[i].burstTime < currentShortestJobRemainingTime){
                        currentShortestJobRemainingTime = processes[i].burstTime;
                        currentShortestJobIndex = i;
    			    }
                }
    			

    		}
    	}

    	if(isAllCompleted){
    		break;
    	}

		processes[currentShortestJobIndex].responseTime = currentTime;

        currentTime += processes[currentShortestJobIndex].burstTime;
    	processes[currentShortestJobIndex].isCompleted = true;

        processes[currentShortestJobIndex].completionTime = currentTime;
    	
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
