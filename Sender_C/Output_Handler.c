#include"Common_header.h"
#include "Output_Handler.h"


int Msg_Handler(send_type_en passed_send_type ,const char *disp_msg)
{
	int ret = NOT_OK;
	Send_method_st Send_method[1] = {{send_to_console , send2console}};
	if((Send_method[passed_send_type].fn_send2UI != NULL) && (passed_send_type < MAX_send_type))
	{
		ret = Send_method[passed_send_type].fn_send2UI(disp_msg);
	}
	return ret;
}

#if(TEST_CODE_ACTIVE != TRUE)
int send2console(const char *msg)
{
	printf("%s\n" ,msg);
	return OK;
}

#else
/***********Test code*************/

int Test_OpHdlr_positive_trigger(void)
{
	const char msg[128] = "This is a test message";
	Msg_Handler(send_to_console , msg);
	//pipe way..
}

int Test_OpHdlr_negetive_trigger(void)
{
	const char msg[128] = "This is a test message";
	if(Msg_Handler(6 , msg) == NOT_OK) // passing garbage value
	{
		return OK;
	}
}

int send2console(const char *msg)
{
	const char exp_msg[128] = "This is a test message";
	if(strcmp(msg , exp_msg) == 0)
	{
		return OK;
	}
	else
	{
		return NOT_OK;
	}
}

/************************************/

#endif
