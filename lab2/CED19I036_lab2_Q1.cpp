//FCFS
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Process{
public:
    int process_id, arrival_time, burst_time;

    Process(int process_id, int arrival_time, int burst_time)
    {
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        this->process_id = process_id;
    }
};

void find_avg_time(vector<Process> &list_of_processes)
{
    int n = list_of_processes.size();
    int wt[n], ct[n];
    Process p = list_of_processes[0];

    //calculating completion time
    ct[0] = p.arrival_time + p.burst_time;
    for (int i = 1; i < n ; i++ )
    {
        p = list_of_processes[i];
        ct[i] = max(ct[i-1], p.arrival_time) + p.burst_time;
    }
    
    //calculating waiting time
    p = list_of_processes[0];
    wt[0] = 0;
    for(int i=1; i<n; i++)
    {
        p=list_of_processes[i];
        wt[i] = ct[i-1]<=p.arrival_time ? 0 : ct[i-1]-p.arrival_time;
    }
    
    cout << "Processes\t"<<"Arrival Time\t"<< "Burst time\t"
         << "Completion Time\t " << "Waiting time\t" << "Turn Around Time\n";

    for(int i=0; i<n; i++)
    {
        p = list_of_processes[i];
        printf("%d\t\t    %d\t\t    %d\t\t    %d\t\t    %d\t\t    %d\n", 
        p.process_id, p.arrival_time, p.burst_time, ct[i], wt[i], wt[i]+p.burst_time);
    }

    float average_wait=0, average_tat=0;
    for(int i=0; i<n; i++){
        average_tat += (wt[i]+list_of_processes[i].burst_time);
        average_wait += wt[i];
    }
    average_tat /= n;
    average_wait /= n;
    cout<<"Average Turn Around Time: "<<average_tat<<'\n';
    cout<<"Average Waiting Time: "<<average_wait<<'\n';
}

int main()
{
    int n;
    cout<<"Enter the number of processes\n";
    cin>>n;

    vector<Process> list_of_processes;
    for(int i=0; i<n; i++)
    {
        int arrival_time, burst_time;
        // cout<<"Enter arrival time: ";
        cin>>arrival_time;
        // cout<<"Enter burst time: ";
        cin>>burst_time;
        Process p(i+1, arrival_time, burst_time);
        list_of_processes.push_back(p);
    }

    sort(list_of_processes.begin(), list_of_processes.end(), 
    [](Process &a, Process &b){
        return a.arrival_time < b.arrival_time;
    });

    find_avg_time(list_of_processes);
    cout<<'\n';
    return 0;
}