//SJFS Non-pre emptive
#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
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

    //custom comparator
    //when burst times are same then the processes with earlier arrival time is given priority.
    auto cmp = [&](const Process &a, const Process &b){
        if(a.burst_time == b.burst_time)
            return a.arrival_time > b.arrival_time;
        return a.burst_time > b.burst_time;
    };

    //min heap
    priority_queue<Process, vector<Process>, decltype(cmp)> pq(cmp);

    //calculating completion time and waiting time

    Process p = list_of_processes[0];
    int k=1;
    ct[0] = p.arrival_time+p.burst_time;
    wt[0] = 0;
    for(int i=1; i<n; i++)
    {
        //push the elements into the priority queue until the arrival time
        //is greater than the recently finished process's completion time.
        while(k<n && ct[i-1] >= list_of_processes[k].arrival_time)
            pq.push(list_of_processes[k++]);
        
        //if the cpu is in idle state for a while until the next process gets into ready state.
        if(pq.empty())
            p = list_of_processes[k++];
        else
        {
            p = pq.top();
            pq.pop();
        }
        //rearranging the processes according to the priority queue.
        list_of_processes[i] = p;
        ct[i] = max(ct[i-1], p.arrival_time) + p.burst_time;
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

    //sort the process according to their arrival time (ascending order)
    sort(list_of_processes.begin(), list_of_processes.end(), 
    [](Process &a, Process &b){
        return a.arrival_time < b.arrival_time;
    });

    find_avg_time(list_of_processes);
    cout<<'\n';
    return 0;
}