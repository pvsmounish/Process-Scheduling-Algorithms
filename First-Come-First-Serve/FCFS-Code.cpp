// First Code First Serve (FCFS) with Arrival Time
// Mounish Sai (https://github.com/pvsmounish)

#include<iostream>
#include<limits>
using namespace std;

class Process{
    public:
        string processName;
        int arrivalTime;
        int burstTime;

        int remainingTime;

        int responseTime;
        int completionTime;
        
        int waitingTime;
        int turnAroundTime;
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

    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
  
    
    int cumulativeSum = 0;


    for(int n=0;n<numOfProcesses;n++){
        processes[n].waitingTime = cumulativeSum;
        processes[n].completionTime =  processes[n].waitingTime + processes[n].burstTime;
        if(n == 0){
            processes[n].responseTime = 0;
        }
        else{
            processes[n].responseTime = processes[n-1].completionTime;
        }
        
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;

        cout << "\nProcess " << processes[n].processName << ":\n";
        cout << "Response Time: " << processes[n].responseTime << endl;
        cout << "Completion Time: " << processes[n].completionTime << endl;
        cout << "Waiting Time: " << processes[n].waitingTime << endl;
        cout << "Turn Around Time: " << processes[n].turnAroundTime << endl;

        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;

        cumulativeSum += processes[n].burstTime;
    }


    cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float) sumResponseTime/numOfProcesses;
    cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float) sumCompletionTime/numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float) sumWaitingTime/numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float) sumTurnAroundTime/numOfProcesses;

    return 0;
}

