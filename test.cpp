#include<bits/stdc++.h>
using namespace std;


struct process{

	int pid;
	int priority; //new
	int arrival_time;
	int burst_time;
	int start_time; //new
	int completion_time;
	int turn_around_time;
	int waiting_time;


};

void sortbyAT(process p[], int n){ 
    for(int i=0;i<n-1;i++){ 
        for(int j=0;j<n-i-1;j++){ 
            if(p[j].arrival_time>p[j+1].arrival_time){ 
                int temp; 
                //sorting burst times 
                temp = p[j].burst_time; 
                p[j].burst_time = p[j+1].burst_time; 
                p[j+1].burst_time = temp; 
                //sorting arrival times 
                temp = p[j].arrival_time; 
                p[j].arrival_time = p[j+1].arrival_time; 
                p[j+1].arrival_time = temp; 
                //sorting their respective IDs 
                temp = p[j].pid; 
                p[j].pid = p[j+1].pid; 
                p[j+1].pid = temp; 
            } 
        } 
    } 
} 
void findCompletionTime(process p[], int n){ 
    int sum = 0; 
    sum = sum + p[0].arrival_time; 
    for(int i = 0;i<n;i++){ 
        sum = sum + p[i].burst_time; 
        p[i].completion_time = sum; 
        p[i].turn_around_time= p[i].completion_time - p[i].arrival_time; 
        p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;   
        if(sum<p[i+1].arrival_time){ 
            int t = p[i+1].arrival_time-sum; 
            sum = sum+t; 
        }  
    } 
} 

void findTurnAroundTime(process p[],int n){
	for(int i=0; i<n; i++){
		p[i].turn_around_time=p[i].completion_time - p[i].arrival_time;
	}
	
}

void findWaitingTime(process p[],int n){
	p[0].waiting_time=0;
	for(int i=1; i<n; i++){
		p[i].waiting_time=p[i].turn_around_time - p[i].burst_time;

}
}

void sortbyPID(process p[], int n) { 
    for (int i = 0; i < n - 1; i++) { 
        for (int j = 0; j < n - i - 1; j++) { 
            if (p[j].pid > p[j + 1].pid) { 
                int temp;
                temp = p[j].burst_time; 
                p[j].burst_time = p[j + 1].burst_time; 
                p[j + 1].burst_time = temp;

                temp = p[j].arrival_time; 
                p[j].arrival_time = p[j + 1].arrival_time; 
                p[j + 1].arrival_time = temp;

                temp = p[j].completion_time; 
                p[j].completion_time = p[j + 1].completion_time; 
                p[j + 1].completion_time = temp;

                temp = p[j].turn_around_time; 
                p[j].turn_around_time = p[j + 1].turn_around_time; 
                p[j + 1].turn_around_time = temp;

                temp = p[j].waiting_time; 
                p[j].waiting_time = p[j + 1].waiting_time; 
                p[j + 1].waiting_time = temp;

                temp = p[j].pid; 
                p[j].pid = p[j + 1].pid; 
                p[j + 1].pid = temp;
            } 
        } 
    } 
}

void findfcfs(process p[],int n){

    cout<<"Enter process details(Arrival Time,Burst Time):"<<endl;
    for(int i=0;i<n;i++)
    {

        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;

    }
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    float avgTT=0;
    float avgWT=0;
    sortbyAT(p,n);
	findCompletionTime(p,n);
	findTurnAroundTime(p,n);
	findWaitingTime(p,n);
    sortbyPID(p,n);
    cout<<"PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time"<<endl;
	for(int i=0; i<n; i++)
    {
		cout<<p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<
		"\t\t"<<p[i].completion_time<<"\t\t"<<p[i].turn_around_time<<"\t\t"<<p[i].waiting_time<<endl;

	}
    for(int i=0;i<n;i++){
    total_turnaround_time += p[i].turn_around_time;
    total_waiting_time += p[i].waiting_time;
    }
    avgTT=(float) total_turnaround_time / n;
    avgWT=(float) total_waiting_time/ n;
    cout<<"\n";
    cout<<"Average Waiting time: "<<avgWT<<endl;
    cout<<"Average TAT time: "<<avgTT<<endl;          
}



//SJF

void findSRTF(process p[],int n){

    cout<<"Enter process details(Arrival Time,Burst Time):"<<endl;
    for(int i=0;i<n;i++)
    {

        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;

    }
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    float avgTT=0;
    float avgWT=0;

    int remainingTime[n];
    for(int i=0; i<n ;i++)
    {
        remainingTime[i]= p[i].burst_time;

    }
    int currentTime=0;
    int complete=0;
    int minBurst=9999;
    int shortest=0;
    while(complete<n){

        minBurst=9999;

        for(int i=0;i<n;i++)
        {

             if(p[i].arrival_time<=currentTime && remainingTime[i]<minBurst && remainingTime[i]>0)
             {
                minBurst=remainingTime[i];
                shortest=i;
               

             }
             

        }
        remainingTime[shortest]--;
        if(remainingTime[shortest]==0){
             complete++;
             p[shortest].completion_time=currentTime+1;
             p[shortest].turn_around_time=p[shortest].completion_time-p[shortest].arrival_time;
             p[shortest].waiting_time=p[shortest].turn_around_time-p[shortest].burst_time;
        }
        currentTime++;

       
    }
    cout<<"PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time"<<endl;
	for(int i=0; i<n; i++)
    {
		cout<<p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<
		"\t\t"<<p[i].completion_time<<"\t\t"<<p[i].turn_around_time<<"\t\t"<<p[i].waiting_time<<endl;

	}
    for(int i=0;i<n;i++)
    {
        total_turnaround_time += p[i].turn_around_time;
        total_waiting_time += p[i].waiting_time;
    }
    for(int i=0;i<n;i++){
    total_turnaround_time += p[i].turn_around_time;
    total_waiting_time += p[i].waiting_time;
    }
    avgTT=(float) total_turnaround_time / n;
    avgWT=(float) total_waiting_time/ n;
    cout<<"\n";
    cout<<"Average Waiting time: "<<avgWT<<endl;
    cout<<"Average TAT time: "<<avgTT<<endl;   

}

void printPS(process p[], int n); 

void findPS(process p[],int n){

    for(int i = 0; i < n; i++)
    {
        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        cout<<"Enter priority of the process "<<i+1<<": ";
        cin>>p[i].priority;
        p[i].pid = i+1;
        cout<<endl;
    }

    int completed=0;
    int currentTime=0;
    int prev=0;
    int burst_remaining[n];
    int total_idle_time=0;

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    float avgTT=0;
    float avgWT=0;

    sortbyAT(p,n);
    for(int i=0;i<n;i++){
        burst_remaining[i] = p[i].burst_time;
    }

    while(completed<n){
        int mx=-1;
        int idx=-1;

        for(int i=0;i<n;i++){

            if(p[i].arrival_time<=currentTime && burst_remaining[i]!=0){
                if(p[i].priority>mx){
                    mx=p[i].priority;
                    idx=i;
                }
                if(p[i].priority==mx){
                    if(p[i].arrival_time<p[idx].arrival_time){
                        mx=p[i].priority;
                        idx=i;
                    }
                }
            }
        }

        if(idx!=-1){


            if(burst_remaining[idx]==p[idx].burst_time)
            {
               p[idx].start_time=currentTime;
               total_idle_time+=p[idx].start_time-prev;
            }

            burst_remaining[idx]--;
            currentTime++;
            prev=currentTime;

            if(burst_remaining[idx]==0)
            {
                p[idx].completion_time=currentTime;
                p[idx].turn_around_time=p[idx].completion_time-p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turn_around_time - p[idx].burst_time;
                

                total_turnaround_time += p[idx].turn_around_time;
                total_waiting_time += p[idx].waiting_time;


                completed++;
            }
        }

        else
          currentTime++;

    }
    sortbyPID(p,n);
    printPS(p,n);
    avgTT=(float) total_turnaround_time / n;
    avgWT=(float) total_waiting_time/ n;
    cout<<"\n";
    cout<<"Average Waiting time: "<<avgWT<<endl;
    cout<<"Average TAT time: "<<avgTT<<endl;   

}

void printPS(process p[],int n){

	cout<<"PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time"<<endl;
	for(int i=0; i<n; i++){
		cout<<p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<
		"\t\t"<<p[i].completion_time<<"\t\t"<<p[i].turn_around_time<<"\t\t"<<p[i].waiting_time<<endl;

	}

}

void findHRRN(process p[], int n){

    int i, j;
    int currentTime=0, avgWT = 0, avgTT = 0;
    cout<<"Enter process details(Arrival Time,Burst Time):"<<endl;
    for(int i=0;i<n;i++)
    {

        cout<<"Enter arrival time of process "<<i+1<<": ";
        cin>>p[i].arrival_time;
        cout<<"Enter burst time of process "<<i+1<<": ";
        cin>>p[i].burst_time;
        p[i].pid = i+1;
        cout<<endl;

    }

    // Sorting the structure by arrival times
    sortbyAT(p,n);

    int completed = 0;  
    currentTime = p[0].arrival_time;        
    int is_completed[n];
    for(i=0;i<n;i++)
    {
        is_completed[i] = 0;
    }

    while (completed < n) {
        float hrr = -9999;  // Lower limit for response ratio
        float temp;
        int loc = -1;

        // Check all processes to select the next one
        for (i = 0; i < n; i++) {
            if (p[i].arrival_time <= currentTime && is_completed[i] != 1) {
                temp = (p[i].burst_time + (currentTime - p[i].arrival_time)) / (float)p[i].burst_time;
                if (hrr < temp) {
                    hrr = temp;
                    loc = i;
                }
            }
        }

        if (loc == -1) { 
            currentTime++;
        } 
        
        else {
            // Execute the selected process
            currentTime += p[loc].burst_time;
            p[loc].completion_time=currentTime;
            p[loc].waiting_time = currentTime - p[loc].arrival_time - p[loc].burst_time;
            p[loc].turn_around_time = currentTime - p[loc].arrival_time;
            avgTT += p[loc].turn_around_time;;
            is_completed[loc] = 1;
            completed++; 
            avgWT += p[loc].waiting_time;
        }
    }
    sortbyPID(p,n);
    cout<<"PID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time"<<endl;
	for(int i=0; i<n; i++)
    {
		cout<<p[i].pid<<"\t\t"<<p[i].arrival_time<<"\t\t"<<p[i].burst_time<<
		"\t\t"<<p[i].completion_time<<"\t\t"<<p[i].turn_around_time<<"\t\t"<<p[i].waiting_time<<endl;

	}

    cout << "\nAverage waiting time: " << avgWT / n << endl;
    cout << "Average Turn Around time:" << avgTT / n;
}

int main(){
    cout<<"\n";
    cout<<"------- Algorithm Calculator -------"<<endl;
	int n;
    cout<<"Enter number of processes :"<<endl;
	cin>>n;
	process p[n];
   
    int x;
    do
    {   
        cout<<"\n";
        cout<<"1.FirstComeFirstServed"<<endl;
        cout<<"2.ShortestJobFirst"<<endl;
        cout<<"3.Priority"<<endl;
        cout<<"4.HRRN"<<endl;
        cout<<"5.EXIT"<<endl;
        cout<<"Enter your choice: ";
	    cin>>x;
   

	  switch(x){
		case 1:
		  cout<<"FCFS Scheduling: "<<endl;
		  findfcfs(p,n);
		  break;
		case 2:
		   cout<<"SJF Scheduling: "<<endl;
		   findSRTF(p,n);
		   break;
        case 3:
            cout<<"Priority Scheduling : "<<endl;
            findPS(p,n);
            break;
		case 4:
           cout<<"HRRN : "<<endl;
           findHRRN(p,n);
		   break;
        case 5:
           break;
	}
	
   }while(x<5);
   return 0;
}