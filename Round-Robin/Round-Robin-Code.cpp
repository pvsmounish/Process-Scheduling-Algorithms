// Round Robin with Arrival Time
// Mounish Sai (https://github.com/pvsmounish)

#include<iostream>
using namespace std;

class Process{
    public:
        string processName;
        int burstTime;
        int arrivalTime;

        int waitingTime;
        int completionTime;
        int responseTime;
        int turnAroundTime;

        int remainingTime;

        void initialize(){
        	waitingTime = 0;
        	responseTime = 0;
        	turnAroundTime = 0;
        	remainingTime = burstTime;
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

    currentTime = processes[0].arrivalTime;
    int remainingProcesses = numOfProcesses;

    for(int i=0;i<numOfProcesses;i=(i+1)%numOfProcesses){
        if(processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime){
        	if(processes[i].remainingTime == processes[i].burstTime){
        		processes[i].responseTime = currentTime;
        	}

        	if(processes[i].remainingTime <= timeQuantum){
        		currentTime += processes[i].remainingTime;
        		processes[i].completionTime = currentTime;
        		processes[i].remainingTime = 0;
                remainingProcesses--;
        	}
        	else{
        		currentTime += timeQuantum;
        		processes[i].remainingTime -= timeQuantum;
        	}

        }

        if(remainingProcesses == 0){
            break;
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
