#include "Common_header.h"
#include "Parameter_Collector.h"
#include "CSV_reader.h"

int CSV_Handler(void)
{
	int Retval = OK;
	char fread_buff[100]; // CSV file single line will never be longer than 50
	const char comma[2] = "," , semicolon[2] = ";" ; // "\0 at the end"
	char *data , *s_data;
	int col = 0;  
	static FILE *fp ;
	static int first_cycle = TRUE ;
	if(first_cycle == TRUE)
	{
		first_cycle = FALSE ; 
		fp	= fopen("Sender_C/database.txt","r");
		if(!fp)
		{
			Retval = NOT_OK;
		}
	}	
	if(Retval != NOT_OK)
	{
		if(fgets(fread_buff , sizeof(fread_buff) , fp))
		{
			s_data = strtok(fread_buff, semicolon); // remove the semicolon
			data = strtok(s_data, comma); // Capture the first part before the comma.
			while(data != NULL)
			{
				if(!strcmp(data, " "))
				{
					//Data capturing problem
					data = "ERROR" ; 
				}
				(void)data_collector(data , col);
				col++;
				data = strtok(NULL, comma);
			}
			col = 0; //initialize the coloumn
			Retval = OK;
		}
		else
		{
			//file END has been reached.
			Retval = FILE_END_OK;
			first_cycle = TRUE ;
			fclose(fp);
		}
	}	
	return Retval;
}

#if(TEST_CODE_ACTIVE == TRUE)

/************Test code******************/

int Test_CSV_HandlerNoFile(void)
{
	/*Whitebox testing*/
	/*Not present file*/
	if(CSV_Handler() == NOT_OK)
	{
		return OK;
	}
}

int Test_CSV_HandlerEndFile(void)
{
	/*Whitebox testing*/
	/*Empty file file*/
	if(CSV_Handler() == FILE_END_OK)
	{
		return OK;
	}
}

/****************************************/

#endif
