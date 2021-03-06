#include "Common_header.h"
#include "Parameter_Collector.h"

/*Making Global since the address is shared acreoos multiple files*/
char out_buffer[1024] ;

char * batt_param_collector(char *param_val , int col , int usage)
{	
	int i = 0 ,idx = 0;
	char Accu_buffer[50];
	const char colon[2] = ":" , space[3]= "  ";
	static batt_param_st batt_param[MAX_PARAM_TYPE] = {{temperature_param , "0.00" , "Battery_Temperature"} , 	\
													{SOC_param , "0.00" , "Battery_SOC"} , 					\
													{current_param , "0.00" , "Battery_Current"} , 			\
													{charge_rate_param , "0.00" , "Battery_Charge_Rate"}};
	
		if((usage == UPDATE) && (col < MAX_PARAM_TYPE) && (param_val != NULL))
	{
		strcpy(batt_param[col].batt_param_val , param_val);
	}
	else if(usage == ACCUMULATE)
	{
		for(i = 0; i<(MAX_PARAM_TYPE) ; i++)
		{
			sprintf(Accu_buffer , "%s%s%s%s" , batt_param[i].param_name , colon ,  batt_param[i].batt_param_val , space);			
			sprintf(&out_buffer[idx] , "%s" , Accu_buffer);
			idx += strlen(Accu_buffer);
		}
	}
	else
	{
		//error case. No op. 		
	}	
	return out_buffer;
}

#if(TEST_CODE_ACTIVE == TRUE)
/*************test code********************/

int Test_BattParamColl(char *val , int col , int usage)
{
	(void)batt_param_collector(val , col , usage);
	return OK; // any error condition code will go to exception
}

/****************************************/
#endif
