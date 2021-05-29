#include"Common_header.h"
#include "Output_Handler.h"


int Msg_Handler(send_type_en passed_send_type ,const char *disp_msg)
{
	Send_method_st Send_method[1] = {{send_to_console , send2console}};
	return Send_method[passed_send_type].fn_send2UI(disp_msg);
}

int send2console(const char *msg)
{
	printf("%s" ,msg);
	return OK;
}