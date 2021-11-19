//Round Robin
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

class Process{
public:
    int pid;
    int arrival;
    int burst;
};

int main()
{
    int index, n, tq;

    //number of processes
    cin>>n;

    //time quanta
    cin>>tq;

    Process p[n], p_copy[n];
    int waiting[n],turnaround[n],completion[n];
    float avg=0,tt=0,end;

    //arrival time of process
    for(int i=0;i<n;i++)
    {
      cin>>p[i].arrival;
      p[i].pid = i;
    }

    //bursturst time of process
    for(int i=0;i<n;i++)
      cin>>p[i].burst;
    
    for(int i=0; i<n; i++)
        p_copy[i] = p[i];
    
    //sort according to arrival time
    sort(p, p+n, [](Process &a, Process &b){return a.arrival < b.arrival;});

    queue<Process> q;
    int i=1;
    Process prev, curr;
    int time=p[i].arrival, max_process_time;

    prev.arrival = -1;
    q.push(p[0]);

    while(!q.empty() || i<n || (prev.burst>0 && prev.arrival!=-1) )
    {
        //find how many processes have already arrived.
        while(i<n && time >= p[i].arrival)
        {
            q.push(p[i]);
            i++;
        }

        //if the previous process has not ended
        if(prev.arrival != -1)
            q.push(prev);

        curr = q.front();
        // cout<<curr.pid+1<<" "<<curr.burst<<'\n';
        q.pop();
        max_process_time = min(tq, curr.burst);
        time += max_process_time;
        curr.burst -= max_process_time;
        
        prev.arrival = -1;

        //if the current process is completed
        if(curr.burst <= 0)
        {
            completion[curr.pid] = time;
            turnaround[curr.pid] = time - curr.arrival;
            waiting[curr.pid] = turnaround[curr.pid] - p_copy[curr.pid].burst;
        }
        else
            prev = curr;
    }

    cout<<"\nProcess"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<"\t"<<'\n';
    for(i=0; i<n; i++)
    {
        Process p = p_copy[i];
        cout<<"p"<<i+1<<"\t\t"<<p.burst<<"\t\t"<<p.arrival<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<"\t\t"<<'\n';
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
   	cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
    
    return 0;

}