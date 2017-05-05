#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <string>

struct Process{
    int Process_ID;
    int Arrival_Time;
    int Burst_Duration;
    int Priority;
    int TurnAroundTime;
    int WaitTime;
};
//**********************************************************
struct Gantt
{
  int Process_ID;
  int Arrival_Time;
  int End_Time;
};

void File_Content(struct  Process Processes[], int number);
void FCFS(struct Process Processes[], int number);
void SJFP(struct Process Processes[], int number);
void PRIORITY(struct Process Processes[], int number);
void RR(struct Process Processes[], int number, int quantum);
void Display_Output(struct  Process Processes[],int number,std::vector<Gantt> Rows[],int count, std::string filename);

int main(int argc, char **argv)
{

    int number_of_pross = 0;

    	if (argc != 2)
    	{
       		printf("Incorrect number of arguments.\n");
       	 	return -1;
    	}

		FILE* file1 = fopen(argv[1], "r");

  while(!feof(file1))
  {
  char  ch = fgetc(file1);
    if(ch == '\n')
    {
      number_of_pross++;
    }
  }
        struct Process Processes[number_of_pross];

        fseek(file1, 0, SEEK_SET);


        number_of_pross=0;


		while(fscanf(file1, "%d,%d,%d,%d",&Processes[number_of_pross].Process_ID,&Processes[number_of_pross].Arrival_Time,&Processes[number_of_pross].Burst_Duration,&Processes[number_of_pross].Priority) != EOF	)
       {
			number_of_pross++;
        }
        fclose(file1);

            File_Content(Processes,number_of_pross);
            FCFS(Processes,number_of_pross);
            SJFP(Processes,number_of_pross);
            PRIORITY(Processes,number_of_pross);
	
        return 0;
}
//--------------------------------------------------------
void File_Content(struct Process Processes[], int number)
{
    int i;
    printf("PROCESS ID\tARRIVAL TIME\tBURST DURATION\tPRIORITY\n");
    for(i=0;i<number;i++)
    {

        printf("%d\t\t%d\t\t%d\t\t%d\n",Processes[i].Process_ID,Processes[i].Arrival_Time,Processes[i].Burst_Duration,Processes[i].Priority);

    }
}
//---------------------------------------------------------------
void Display_Output(struct  Process Processes[],int number, std::vector<Gantt> Rows, int count, std::string filename)
{
      FILE* file;
      int i;
      file=fopen(filename.c_str(),"w");
      fprintf(file,"PROCESS ID\tARRIVAL TIME\tEND TIME\n");

      for(i=0;i<count;i++)
      {
        fprintf(file,"%10d%10d%10d\n",Rows[i].Process_ID,Rows[i].Arrival_Time,Rows[i].End_Time);
      }

      float avgWait=0;
      float avgTurnAround=0;
      for(i=0;i<number;i++)
      {
          avgWait+=Processes[i].WaitTime;
          avgTurnAround+=Processes[i].TurnAroundTime;
      }
      fprintf(file,"Average Wait Time=%f\n",avgWait/number);
      fprintf(file,"TurnAround Time=%f\n",avgTurnAround/number);
      // Assumption: the value of count recieved is greater than exact number of rows in the Gantt chart by 1. Dont forget to adjust the value if yours is not so.
      fprintf(file,"Throughput=%f\n",((float)number/Rows[count-1].End_Time));
      fclose(file);

}
//------------------------------------------------------------

bool finished( struct Process Processes[], int number ){
	for( int i = 0; i < number; i++ )
		if( Processes[i].Burst_Duration > 0 )
			return false;
	return true;
}

/*
 Note: Use function Display_Output to display the result. The Processes is the
 updated Processes with their respective waittime, turnAround time.
 Use the array of Gantt Struct to mimic the behaviour of Gantt Chart. Rows is the base name of the same array.
 number is the number of processes which if not changed during processing, is taken care. count is the number of rows in the Gantt chart. 
 
 Number of Processes will not exceed 1000. Create and array of Gantt chart which can accomodate atleast 1000 process.
 */
// -------------FCFS----------------------------------------
void FCFS(struct Process Processes[], int number)
{
	Process localProcesses[number];
	memcpy( localProcesses, Processes, sizeof( Process ) * number );
	std::vector<Gantt> vgantt;
	Gantt tmpgantt;
    //---------Start Processing
	int i, time = 0;
    
	while( !finished( localProcesses, number) ){
		for( i = 0; i < number; i++ ){
			if( localProcesses[i].Arrival_Time == time ){
				// Contruct the new addition to the gantt chart
				tmpgantt.Process_ID = localProcesses[i].Process_ID;
				!vgantt.empty()?
					tmpgantt.Arrival_Time = vgantt.back().End_Time:
					tmpgantt.Arrival_Time = 0;
				tmpgantt.End_Time = tmpgantt.Arrival_Time + localProcesses[i].Burst_Duration;
				vgantt.push_back( tmpgantt );

				// Calculate the Turn-Around and Wait times
				localProcesses[i].TurnAroundTime = vgantt.back().End_Time - localProcesses[i].Arrival_Time;
				localProcesses[i].WaitTime = vgantt.back().Arrival_Time - localProcesses[i].Arrival_Time;
				
				// Reduce the Burst_Duration to the completed state ( ie. 0 )
				localProcesses[i].Burst_Duration = 0;
			}
		}

		time++;
	}
    //---------End of Processing
   //Hint: Call function with arguments shown Display_Output(localProcesses,number,Rows,count,"FCFS");
   Display_Output( localProcesses, number, vgantt, vgantt.size(), "FCFS" );
}
//---------------------SJFP---------------------------------------
void SJFP(struct Process Processes[],int number)
{
	Process localProcesses[number];
	memcpy( localProcesses, Processes, sizeof( Process ) * number );
	for( int n = 0; n < number; n++){
		localProcesses[n].WaitTime = 0;
		localProcesses[n].TurnAroundTime = 0;
	}
	std::vector<Gantt> vgantt;
	Gantt tmpgantt;
	Process *curproc = NULL;
    //---------Start Processing
    	int i, time = 0;
	bool contsw = false;	// ?context switch
    	while( !finished( localProcesses, number) ){
		curproc;

		for( i = 0; i < number; i++ ){
			// Find a process that can prempt ( When curproc is not assigned, supply a value that will be garenteed to succeed )
			if( (localProcesses[i].Arrival_Time <= time)  &&
				localProcesses[i].Burst_Duration > 0 &&
				localProcesses[i].Burst_Duration < (curproc != NULL ? curproc->Burst_Duration : 0x7FFF)){
					curproc = localProcesses+i;
					contsw = true;
				}
		}
		
		if(contsw){
			// Construct and add a new gantt entry
			tmpgantt.Process_ID = curproc->Process_ID;
			!vgantt.empty()?
				tmpgantt.Arrival_Time = vgantt.back().End_Time = time:
				tmpgantt.Arrival_Time = 0;
			tmpgantt.End_Time = tmpgantt.Arrival_Time + curproc->Burst_Duration;
			vgantt.push_back( tmpgantt );
	
		}
	
		curproc->Burst_Duration--;
		if( curproc != NULL && curproc->Burst_Duration <= 0){
			curproc->TurnAroundTime = time+1 - curproc->Arrival_Time;
			curproc->WaitTime = time+1 - Processes[curproc->Process_ID-1].Burst_Duration - curproc->Arrival_Time;
			curproc = NULL;
		}

		contsw = false;
		time++;
	}
    //---------End of Processing
	Display_Output( localProcesses, number, vgantt, vgantt.size(), "SJFP" );

}
//------------------PRIORITY-------------------------------------
void PRIORITY(struct Process Processes[], int number)
{
	Process localProcesses[number];
	memcpy( localProcesses, Processes, sizeof( Process ) * number );
	for( int n = 0; n < number; n++){
		localProcesses[n].WaitTime = 0;
		localProcesses[n].TurnAroundTime = 0;
	}
	std::vector<Gantt> vgantt;
	Gantt tmpgantt;
	Process *curproc = NULL;
     //---------Start Processing
    	int i, time = 0;
	bool contsw = false;	// ?context switch
	while( !finished( localProcesses, number ) ){
		if(curproc != NULL && curproc->Burst_Duration <= 0){
			curproc->TurnAroundTime = time - curproc->Arrival_Time;
			curproc->WaitTime = time - Processes[curproc->Process_ID-1].Burst_Duration - curproc->Arrival_Time;
			curproc = NULL;
		}
		for(i = 0; i < number; i++){
			if( localProcesses[i].Arrival_Time <= time 	&&
				localProcesses[i].Burst_Duration > 0	&&
				localProcesses[i].Priority < (curproc != NULL ? curproc->Priority : 0x7FFF)){
					curproc = localProcesses+i;
					contsw = true;
				}
		}
		
		if(contsw){
			// Construct and add a new gantt entry
			tmpgantt.Process_ID = curproc->Process_ID;
			!vgantt.empty()?
				tmpgantt.Arrival_Time = vgantt.back().End_Time = time:
				tmpgantt.Arrival_Time = 0;
			tmpgantt.End_Time = tmpgantt.Arrival_Time + curproc->Burst_Duration;
			vgantt.push_back( tmpgantt );
		}
	
		curproc->Burst_Duration--;
		contsw = false;
		time++;
	}
    //---------End of Processing

	Display_Output( localProcesses, number, vgantt, vgantt.size(), "PRIORITY" );
}



