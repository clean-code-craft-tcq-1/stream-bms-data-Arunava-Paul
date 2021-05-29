#include "Common_header.h"
#include "Output_Handler.h"
#include "sender_main.h"



int main()
{
	sender_main();
	getchar();
	return 0;
}




float string2float(char *str)
{
	float number;
	sprintf(str, "%f", number);
	return number;
}

void sender_main(void)
{
	/*Operation steps:
	1. Collect a set of parameters from CSV file.
	2. Store it in Local memory/Msg collect
	3. Send it to the configured user interface*/
	int Retval;
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
	}
	else if(Retval == FILE_END_OK)
	{
		disp_msg  = "CSV file end" ; 
	}
	/*-----------------------------------------*/
	Retval = Sender.MsgHndlr(send_to_console , disp_msg);
	/*-----------------------------------------*/
}

