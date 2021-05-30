#include "Common_header.h"
#include "time.h"
#include "Output_Handler.h"
#include "sender_main.h"



void main()
{
	clock_t timestamp_start;
	timestamp_start = clock();
	sender_main();
	while(1)
	{
		if(Fc_counter_elapsed(timestamp_start) == TRUE)
		{
			timestamp_start = clock();
			if(sender_main() == PROCESS_TERMINATE)
			{
				break;
			};
		}
	}
}

int sender_main(void)
{
	/*Operation steps:
	1. Collect a set of parameters from CSV file.
	2. Store it in Local memory/Msg collect
	3. Send it to the configured user interface*/
	int Retval, doTerminate = FALSE;
	char *disp_msg; 
	Sender_st Sender = {CSV_Handler , batt_param_collector , Msg_Handler};
	/*-----------------------------------------*/
	Retval = Sender.CSVhandler();
	/*-----------------------------------------*/
	if(Retval == OK)
	{
		disp_msg = Sender.BattParamCol(0 , 0 , ACCUMULATE) ; 
	}		
	else if(Retval == NOT_OK)
	{
		disp_msg  = "CSV file read error" ; 
		doTerminate = TRUE;
	}
	else if(Retval == FILE_END_OK)
	{
		disp_msg  = "CSV file end" ; 
		doTerminate = TRUE;
	}
	/*-----------------------------------------*/
	Retval = Sender.MsgHndlr(send_to_console , disp_msg);
	/*-----------------------------------------*/
	if((Retval != OK) || (doTerminate == TRUE) )
	{
		return PROCESS_TERMINATE;
	}
	else
	{
		return Retval;
	}
}


int Fc_counter_elapsed(clock_t timestamp_previous)
{
	clock_t timestamp_current = clock();
	if( Fc_time_difference(timestamp_previous , timestamp_current) >= 1000 )
		return TRUE;
	else
		return FALSE;
}/*end of Fc_counter_elapsed*/

int Fc_time_difference(clock_t timestamp_previous , clock_t timestamp_current)
{
	if(timestamp_current > timestamp_previous)
	{
		return MILISECOND_VALUE(timestamp_current - timestamp_previous);
	}
	else
	{
		/*counter overflow condition*/
		return MILISECOND_VALUE((MAX_CLOCK_CYCLE_TIME - timestamp_previous) + timestamp_current);
	}
}/*end of Fc_time_difference*/
