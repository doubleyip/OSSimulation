//
/*
Simon Yip
CSCI 340 Home Project
YIPOS.cpp 
cpp File
Please compile using C++11
*/
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "OSFunctions.h"
#include <sstream>

using namespace std;

int main(){

long long RAMsize;
int numHDDs;
int numPrinter;				
string command;				//string that gets the user input
int currPID=1;				//PID of the next new process created


cout<<"How much RAM memory is there? (bytes)"<<endl;
while(getline(cin,command))								//while loop to read user input
{
int comp=command[0]-'0';
if(comp>0&&comp<=9)
{
stringstream ss(command);
string extra;
ss>>RAMsize>>extra;
int count=command.size()-1;
	if(extra.size()==0 && command[count]!=' '&&RAMsize>=1&&RAMsize<=4000000000)		//checks if entry is between 1 and 4000000000
	{																				//rejects extra characters after the entry
	//cout<<"Set RAM to "<<RAMsize<<endl;
	break;																			//breaks loop if valid input
	}
	else
	{
	cout<<"Please enter a number between 1 and 4000000000"<<endl;
	}
}
else
{
cout<<"Please enter a number between 1 and 4000000000"<<endl;	
}
}
initializeMem(RAMsize);											//initializes RAM size to user inputted number


cout<<"How many hard disks are there?"<<endl;

while(getline(cin,command))								//while loop to listen for number of Hard Disks
{
	stringstream ss(command);
	string extra;
	ss>>numHDDs>>extra;
	int count=command.size()-1;
	if(extra.size()==0 && command[count]!=' '&&numHDDs>=1&&numHDDs<=10)		//checks if input is between 1 and 10 
	{																		//rejects otherwise
	setHDDs(numHDDs);														//sets number of hdd
	setHQueue(numHDDs);														//sets number of hdd queues
	break;																	
	}
	else
	{
	cout<<"Please enter a number between 1 and 10"<<endl;
	}
}

cout<<"How many printers are there?"<<endl;

while(getline(cin,command))							//while loop to listen for number of printers
{
	stringstream ss(command);
	string extra;
	ss>>numPrinter>>extra;
	int count=command.size()-1;
	if(extra.size()==0 && command[count]!=' '&&numPrinter>=1&&numPrinter<=10)	//checks if input is between 1 and 10
	{																			//rejects otherwise
	setPrinters(numPrinter);													//sets number of printers
	setPQueue(numPrinter);														//sets number of printer queues
	break;
	}
	else
	{
	cout<<"Please enter a number between 1 and 10"<<endl;
	}
}

cout<<"Input user commands, press 0 to exit"<<endl;
while(getline(cin,command))								//while loop to listen for commands
{
int priority=command[2]-'0';							//converts string to int to check input
if (command=="0"){										//case to exit program
break;	
}
else if (command[0]=='A' && command[1]==' ' && priority>=0 &&priority<=4 && command[3]==' ')	
{														//check for valid new process input
stringstream ss(command);
string extra;
string extra1;
long long stemp;
ss>>extra>>extra>>stemp>>extra1;				//checks if there are extra characters after valid input
int count=command.size()-1;
	if(extra1.size()==0 && command[count]!=' ')		
	{
		if (manageMemory(currPID,stemp)==true)		//if input is value, execute function to create new process
			{
			newprocess(currPID,priority);
			incrementPID(currPID);					//if process is succesfully created, increment PID
			}
		
	}
	else
	{
	cout<<"Please enter a valid user command1"<<endl;	//reject incorrect input
	}
}
else if (command[0]=='d'&&command[1]==' ')		//checks for valid input for sending process to hdd or printer
{
processH(command);
}
else if (command[0]=='p'&&command[1]==' ')
{
processP(command);
}
else if (command[0]=='D'&&command[1]==' ')		//checks for valid input for removing process from hdd or printer
{
processH(command);
}
else if (command[0]=='P'&&command[1]==' ')
{
processP(command);
}
else if(command.length()>3)
{
cout<<"Please enter a valid user command"<<endl;	//reject input if length is greater than 3 and not new process command
}
else
{	
processInput(command);							//process other inputs
}
}


}
