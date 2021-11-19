//Priority Scheduling
#include<iostream>

using namespace std;

int main()
{
    int i,j,index,count=0,time,n, highest;
	//number of processes
    cin>>n;

    int a[n],b[n],x[n];
    int waiting[n],turnaround[n],completion[n],p[n];
    float avg=0,tt=0,end;

    //arrival time of process
    for(i=0;i<n;i++)
      cin>>a[i];

    //burst time of process
    for(i=0;i<n;i++)
      cin>>b[i];

    //priority of process
    for(i=0;i<n;i++)
      cin>>p[i];

	//copy of burst times
    for(i=0; i<n; i++)
        x[i]=b[i];

	//for every second we check if any process has arrived
    for(time=0; count!=n; time++)
    {
		//to keep track of the highest process
        highest=-1;
        for(i=0; i<n; i++)
        {
            if(a[i]<=time && p[i]>highest && b[i]>0 )
			{
				//index of the highest priority process
                index=i;
				highest=p[i];
			}
        }
        b[index]--;

        if(b[index]==0)
        {
            count++;
            end=time+1;
            completion[index] = end;
			turnaround[index] = end - a[index];
            waiting[index] = turnaround[index] - x[index];
        }
    }
    cout<<"Process"<<"\t"<< "burst-time"<<"\t"<<"arrival-time" <<"\t"<<"waiting-time" <<"\t"<<"turnaround-time"<< "\t"<<"completion-time"<<"\t"<<"Priority"<<endl;
    for(i=0; i<n; i++)
    {
         cout<<"p"<<i+1<<"\t\t"<<x[i]<<"\t\t"<<a[i]<<"\t\t"<<waiting[i]<<"\t\t"<<turnaround[i]<<"\t\t"<<completion[i]<<"\t\t"<<p[i]<<endl;
        avg = avg + waiting[i];
        tt = tt + turnaround[i];
    }
   	cout<<"\n\nAverage waiting time ="<<avg/n;
    cout<<"  Average Turnaround time ="<<tt/n<<endl;
}
