//
/*
Simon Yip
CSCI 340 Home Project
OSFunctions.h 
Header File
*/
//

#ifndef OSF_H
#define OSF_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class PCB{						//create class to store process data members
	int PID;
	int priority;
	public:
	void setPID(int a);			//class functions to set and retrieve data members
	void setpriority(int a);
	void showData(PCB a);
	int getPID(PCB a);
	int getPriority(PCB a);
};

struct processMem{				//struct to store process in memory
	int PID;
	long long memStart;
	long long memEnd;
};

vector <PCB> priority4;		//create vectors to represent priority queues
vector <PCB> priority3;
vector <PCB> priority2;
vector <PCB> priority1;
vector <PCB> priority0;
vector <PCB> cpu;			//create CPU
vector<PCB> printers;		//create vector of printers
vector<PCB> hdds;			//create vector of hdds
vector<vector<PCB>> pQueue;		//vector of queues for HDD
vector<vector<PCB>> hQueue;		//vector of queues for Printers
vector<processMem> memory;		//vector of struct to represent RAM

void initializeMem(long long a)		//initializes memory vector
{								//as 1 "hole"
processMem proc;
proc.PID=0;
proc.memStart=0;
proc.memEnd=a-1;
memory.push_back(proc);
}


bool manageMemory(int a, long long b)	//bool function that returns true if process 
{										//fits in memory
for (int i=0;i<memory.size();i++)		//for loop to check for hole big enough to fit memory
{
	if(memory[i].PID==0)			//checks if hole
	{
		long long space=memory[i].memEnd-memory[i].memStart;
		if(b<=space+1)			//checks if memory taken is less than the hole space
		{
		processMem proc;
		proc.PID=a;								
		proc.memStart=memory[i].memStart;	//sets struct to parameters of hole
		proc.memEnd=proc.memStart+b-1;
		memory[i].memStart=proc.memEnd+1;	//reassigns hole values
		
			if(memory.size()==1)				//if process is the first process, put it at the beginning
			{
			memory.insert(memory.begin(),proc);	
			return true;
			}
			else
			{								//if process is not the first, put it where the hole was
			memory.insert(memory.begin()+i,proc);
			return true;			
			}
			
		}
	}
}
cout<<"There is not enough space for this process"<<endl;	//reject process if there is no valid space for it
return false;
}

void deletefromMem(int a)		//function to delete a process of PID a from RAM memory
{
for(int i=0;i<memory.size();i++) //for loop that searches for process of PID a
{
	if(memory[i].PID==a)
	{
		memory[i].PID=0;		//if it finds it, it sets PID to 0
	}
}
for(int i=0;i<memory.size();i++)	//for loop to merge holes
{
	if(memory[i].PID==0 && memory[i-1].PID==0)	//find consecutive holes
	{
		if((memory[i-1].memEnd+1)==(memory[i].memStart))	
		{
		memory[i].memStart=memory[i-1].memStart;	//set 1st hole to 2nd hole start
		memory.erase(memory.begin()+i-1);		//delete the 1st hole
		i--;				//decrement 1 to check for additional consecutive holes
		}
	}
}

}


void PCB::setPID(int a)		//class function to set PID
{
PID=a;	
}


void PCB::setpriority(int a)	//class function to set priority
{
priority=a;
}


void PCB::showData(PCB a)		//class function to show PID and Priority
{
cout<<"PID: "<<a.PID<<endl;	
cout<<"Priority: "<<a.priority<<endl;
}


int PCB::getPID(PCB a)			//class function to get PID
{
int PID=a.PID;
return PID;
}


int PCB::getPriority(PCB a)		//class function to get Priority
{
int temp=a.priority;
return temp;	
}


int incrementPID(int &i)		//increments PID
{
	i++;
}


void setPrinters(int b)		//set # of printers
{
printers.resize(b);
}


void setPQueue(int b)		//set # of printer queues
{
pQueue.resize(b);
}


void setHDDs(int b)			//set # of Hard Disks
{
hdds.resize(b);
}


void setHQueue(int b)		//set # of Hard Disk Queues
{
hQueue.resize(b);
}


void newprocess(int a, int b){		//function to create a new process
PCB process;
process.setPID(a);
process.setpriority(b);				//create new process and set data members
//process.showData(process);
if (cpu.size()==0)					//if cpu is empty, push the process into CPU
{
cpu.push_back(process);
}
else if(cpu.size()==1)
{
int currPriority=cpu[0].getPriority(cpu[0]);	//if cpu is full, check if current 
		if(b>currPriority)		//process has a higher priority than process in cpu
		{
			if (currPriority==3)	//replace current process in cpu,
			{						//push it back to end of its priority queue
			PCB temp;
			temp=cpu[0];
			cpu.pop_back();
			cpu.push_back(process);
			process=temp;
			priority3.push_back(process);

			}
			if (currPriority==2)
			{
			PCB temp;
			temp=cpu[0];
			cpu.pop_back();
			cpu.push_back(process);
			process=temp;
			priority2.push_back(process);

			}
			if (currPriority==1)
			{
			PCB temp;
			temp=cpu[0];
			cpu.pop_back();
			cpu.push_back(process);
			process=temp;
			priority1.push_back(process);

			}
			if (currPriority==0)
			{
			PCB temp;
			temp=cpu[0];
			cpu.pop_back();
			cpu.push_back(process);
			process=temp;
			priority0.push_back(process);

			}
		}
		else if (b==4)		//else new process has lower priority, push it to end of it
		{					//its priority queue
		priority4.push_back(process);	
		}
		else if (b==3)
		{
		priority3.push_back(process);	
		}
		else if (b==2)
		{
		priority2.push_back(process);	
		}
		else if (b==1)
		{
		priority1.push_back(process);	
		}
		else if (b==0)
		{
		priority0.push_back(process);
		}
}

}

void nextProcess()
{
PCB process;
if (priority4.size()!=0)	//if the highest priority queue is not empty,
{							//take the first process, and push it to the cpu
process=priority4[0];
priority4.erase(priority4.begin());
cpu.push_back(process);
}
else if (priority3.size()!=0)	//if priority queue 4 is empty process to priority
								//queue 3, then 2, then 1, the 0 until empty
{
process=priority3[0];
priority3.erase(priority3.begin());
cpu.push_back(process);
}
else if (priority2.size()!=0)
{
process=priority2[0];
priority2.erase(priority2.begin());
cpu.push_back(process);
}
else if (priority1.size()!=0)
{
process=priority1[0];
priority1.erase(priority1.begin());
cpu.push_back(process);
}
else if (priority0.size()!=0)
{
process=priority0[0];
priority0.erase(priority0.begin());
cpu.push_back(process);
}
else
if (cpu.size()==1)
{
cout<<"There are no more remaining processes in Priority Queues"<<endl;
}

}


void terminateProcess()		//function to terminate process
{
if (cpu.size()==0)		//if cpu is empty, reject terminate command
{
cout<<"There are no more processes to terminate"<<endl;
}
else			//otherwise, delete the process from CPU and memory
{
int temp;
int deletePID=cpu[0].getPID(cpu[0]);	//save the PID of deleted process
cpu.pop_back();				//pop it from CPU
deletefromMem(deletePID);	//delete process from memory
nextProcess();				//send next high priority process to from 
}							//priority queues to CPU
}


void pToHDD(int a)		//function to send process from CPU to Hard Disk
{
int i=a;
PCB process;
if (cpu.size()==0)		//if there is nothing in CPU reject command
{
cout<<"There is no process in CPU to send"<<endl;
}
else if (hdds[i].getPID(hdds[i])==0)	//if HDD is empty move process in cpu to HDD
{
process=cpu[0];
cpu.pop_back();
nextProcess();
hdds[i]=process;
cout<<"Process in CPU sent to HDD"<<endl;
}
else				//if HDD has a process, move the current process to 
if (hdds[i].getPID(hdds[i])!=0)		//the proper HDD queue
{
process=cpu[0];
cpu.pop_back();
nextProcess();
hQueue[i].push_back(process);
cout<<"Process moved to HDD Queue "<<i<<endl;
}
}


void pToPrinter(int a)		//function to send process from CPU to printer
{
int i=a;
PCB process;
if (cpu.size()==0)   		//if there is nothing in CPU reject command
{
cout<<"There is no process in CPU to send"<<endl;
}
else 			
if (printers[i].getPID(printers[i])==0)	//if printer is empty, move process to printer
{
process=cpu[0];
cpu.pop_back();
nextProcess();
printers[i]=process;
cout<<"Process in CPU sent to printer"<<endl;
}
else
	if (printers[i].getPID(printers[i])!=0)	//if printer has a process, move process to
{								//printer queue
process=cpu[0];
cpu.pop_back();
nextProcess();
pQueue[i].push_back(process);
cout<<"Process moved to Printer Queue "<<i<<endl;
}
}


void endHProcess(int a)			//function to finish HDD use of process
{
int i=a;
int tempPID;
int tempPrio;
PCB process;
if(hdds[i].getPID(hdds[i])!=0&&hQueue[i].size()!=0)		
{		//if hdd has a process, and a queue exists move process from queue to HDD
process=hQueue[i][0];		//save process in HDD queue
int PID=hQueue[i][0].getPID(hQueue[i][0]);
hQueue[i].erase(hQueue[i].begin());	//erase from queue
tempPID=hdds[i].getPID(hdds[i]);
tempPrio=hdds[i].getPriority(hdds[i]);
newprocess(tempPID,tempPrio);	//move process back to cpu or its priority queue
hdds[i]=process;					//promote process in HDD queue
}
else
{					//else if queue is not empty, move the process from HDD to cpu
tempPID=hdds[i].getPID(hdds[i]);	
tempPrio=hdds[i].getPriority(hdds[i]);	
newprocess(tempPID,tempPrio);		//return process to cpu or its priority queue
hdds[i].setPID(0);				
}
}


void endPProcess(int a)		//function to remove process from printer
{
int i=a;
int tempPID;
int tempPrio;
PCB process;
if(printers[i].getPID(printers[i])!=0&&pQueue[i].size()!=0)	
{				//if there is a queue for the printer
process=pQueue[i][0];
int PID=pQueue[i][0].getPID(pQueue[i][0]);
pQueue[i].erase(pQueue[i].begin());		//move process from queue to printer
tempPID=printers[i].getPID(printers[i]);
tempPrio=printers[i].getPriority(printers[i]);
newprocess(tempPID,tempPrio);	//send process in printer back to cpu or priority queue
printers[i]=process;			
}
else
{	//else is queue is empty, just put the process in printer back to cpu or priority queue
tempPID=printers[i].getPID(printers[i]);
tempPrio=printers[i].getPriority(printers[i]);	
newprocess(tempPID,tempPrio);
printers[i].setPID(0);
}
}



void processH(string s)		//function to process d/D functions
{
stringstream ss(s);
string extra;
string extra1;
int stemp;
ss>>extra>>stemp>>extra1;
int count=s.size()-1;
	if (stemp>9 or stemp<1)
	{
	cout<<"Please enter a valid command"<<endl;
	}
	else if (stemp>=hQueue.size())	//if number entered is greater than the queue, reject
	{
	cout<<"This HDD does not exist"<<endl;	
	}
	else if(extra1.size()==0 && s[count]!=' ')
	{
		if(extra=="d")			//if d #, send process to HDD  or queue
		{
			if (cpu.size()==0)  //if no process in cpu, reject
			{
			cout<<"There is no process in CPU to sent to HDD"<<endl;
			}
		else
		{		
		pToHDD(stemp);	//else execute function to send process in cpu to HDD
		}
	}
	else 
		if(extra=="D")	//if D #, remove process from hard disk, send back
		{				//to CPU or queue
			int i=stemp;
			if (hdds[i].getPID(hdds[i])==0)
			{
			cout<<"HDD "<<stemp<<" does not have a process"<<endl;	
			}	
			else
			endHProcess(stemp);
		}
	}
	else
	{
	cout<<"Please enter a valid user command"<<endl;
	}
}


void processP(string s) //function to process p/D commands
{
stringstream ss(s);
string extra;
string extra1;
int stemp;
ss>>extra>>stemp>>extra1;
int count=s.size()-1;
	if (stemp>9 or stemp<1)
	{
	cout<<"Please enter a valid command"<<endl;
	}
	else if(stemp>=pQueue.size()) //if entered number is greater than queue size, reject
	{
	cout<<"This Printer does not exist"<<endl;	
	}
	else if(extra1.size()==0 && s[count]!=' ')
	{
		if(extra=="p")	//if no process in CPU, reject
		{
			if (cpu.size()==0)
			{
			cout<<"There is no process in CPU to sent to Printer"<<endl;
			}
		else
		{			
		pToPrinter(stemp);	//else send process to printer
		}
	}
	else 
		if(extra=="P")		//if P #, send process to from printer to CPU or queues
		{
			int i=stemp;
			if (printers[i].getPID(printers[i])==0)
			{
			cout<<"Printer "<<stemp<<" does not have a process"<<endl;	
			}	
			else
			endPProcess(stemp);
		}
	}
	else
	{
	cout<<"Please enter a valid user command"<<endl;
	}
}

void showMemory() 		//function to show current state of memory
{
if(memory.size()==1 && memory[0].PID==0)	//if there are no processes,
{											//output no processes
	cout<<"There are currently no processes in memory"<<endl;
	return;
}
for(int i=0;i<memory.size();i++)	//loop to print out start and end of memory
	{								//only if not a hole
	if(memory[i].PID!=0)
	{
	cout<<"PID: "<<memory[i].PID<<endl;
	cout<<"Start of Memory: "<<memory[i].memStart<<endl;
	cout<<"End of Memory: "<<memory[i].memEnd<<endl;
	}
	}
}

void showProcesses()		//function show processes in queue and using CPU
{

int tempPID;
cout<<"PID of Process currently using the CPU: ";
if (cpu.size()!=0)			//if no process is using CPU, print nothing
{		
tempPID=cpu[0].getPID(cpu[0]);
cout<<tempPID<<endl;
}
else
{
cout<<endl;
}

cout<<"PID of processes in Priority 4 Ready Queue :";
for(int i=0;i<priority4.size();i++)		//loops to print PID of process in each queue
{
tempPID=priority4[i].getPID(priority4[i]);
cout<<" "<<tempPID;
}
cout<<endl;
cout<<"PID of processes in Priority 3 Ready Queue :";
for(int i=0;i<priority3.size();i++)
{
tempPID=priority3[i].getPID(priority3[i]);
cout<<" "<<tempPID;
}
cout<<endl;
cout<<"PID of processes in Priority 2 Ready Queue :";
for(int i=0;i<priority2.size();i++)
{
tempPID=priority2[i].getPID(priority2[i]);
cout<<" "<<tempPID;
}
cout<<endl;
cout<<"PID of processes in Priority 1 Ready Queue :";
for(int i=0;i<priority1.size();i++)
{
tempPID=priority1[i].getPID(priority1[i]);
cout<<" "<<tempPID;
}
cout<<endl;
cout<<"PID of processes in Priority 0 Ready Queue :";
for(int i=0;i<priority0.size();i++)
{
tempPID=priority0[i].getPID(priority0[i]);
cout<<" "<<tempPID;
}
cout<<endl;
}



void showHDDs()				//function to print list of elements using HDD
{							//or in an HDD queue
int tempPID;
for(int i=0;i<hdds.size();i++)		//print PID of process in HDD
{
int a=i;
cout<<"HDD "<<a<<" is used by Process with PID: ";
	if(hdds[i].getPID(hdds[i])!=0)
	{
	tempPID=hdds[i].getPID(hdds[i]);
	cout<<tempPID;;
	}
	cout<<endl;
}
for(int i=0;i<hQueue.size();i++)	//print PID of processes in queues
{
cout<<"I/O Queue for HDD "<<i<<": ";
	for(int j=0;j<hQueue[i].size();j++)
	{
	tempPID=hQueue[i][j].getPID(hQueue[i][j]);
	cout<<tempPID<<" ";
	}
	cout<<endl;
}
}

void showPrinters()			//function to print list of elements using printer
{							//or in printer queue
int tempPID;
for(int i=0;i<printers.size();i++)		//print PID of process in printer
{
int a=i;
cout<<"Printer "<<a<<" is used by Process with PID: ";
	if(printers[i].getPID(printers[i])!=0)
	{
	tempPID=printers[i].getPID(printers[i]);
	cout<<tempPID;;
	}
	cout<<endl;
}
for(int i=0;i<pQueue.size();i++)		//print PID of printer in printer Queues
{
cout<<"I/O Queue for Printer "<<i<<": ";
	for(int j=0;j<pQueue[i].size();j++)
	{
	tempPID=pQueue[i][j].getPID(pQueue[i][j]);
	cout<<tempPID<<" ";
	}
	cout<<endl;
}
}

void processInput(string s)		//function to process other inputs
{
char temp;
char temp1;
char temp2;
temp=s[0];
temp1=s[1];
temp2=s[2];
int ctemp=temp2-'0';
if (s.length()<1)				//if command is less than size 0, reject it
{
cout<<"Please enter a valid user command"<<endl;
}
else if (temp=='t'&&s.length()==1)		//if command is t, run terminate function
{
terminateProcess();
}
else if (temp=='S'&&temp1==' '&&(s[2]=='r'||s[2]=='i'||s[2]=='m')) 
{							//process commands to print memory, input, queues
	if(s[2]=='r')
	{
		showProcesses();	//if S r, print list of processes in CPU and Queues
	}
	else if(s[2]=='i')		//if S i, print i/o queues and HDD/Printer
	{
		showHDDs();
		showPrinters();
	}
	else if(s[2]=='m')		//if S m, show state of memory
	{
		showMemory();
	}
}
else 
{						//reject all of other commands
cout<<"Please enter a valid user command"<<std::endl;
}
}

#endif