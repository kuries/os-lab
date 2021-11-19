#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

// class Process{
// public:
//     int process_id, arrival_time, burst_time;

//     Process(int process_id, int arrival_time, int burst_time)
//     {
//         this->arrival_time = arrival_time;
//         this->burst_time = burst_time;
//         // this->process_id = process_id;
//     }
// };

int main()
{
    auto cmp = [&](const pair<int, int> &a, const pair<int, int> &b)
    {
        bool ae = (a.first%2==1), be = (a.first%2==1);
        //if both odd
        if(ae && be)
            return true;
        //if anything is odd then go in
        if(ae || be)
            return be;

        bool a5 = (a.first%5==0), b5 = (b.first%5 == 0);
        if(a5 && b5)
            return b.first<a.first;

        if(a5 || b5)
            return a5;
        
        return b.second<a.second;
    };
    
    return 0;
}
