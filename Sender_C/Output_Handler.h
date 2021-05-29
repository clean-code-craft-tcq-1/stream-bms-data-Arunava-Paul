#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

typedef int (*pfn_send2UI)(const char *msg);

typedef enum
{
	send_to_console = 0,
	MAX_send_type
}send_type_en;

typedef struct
{
	send_type_en send_type;
	pfn_send2UI fn_send2UI;		
}Send_method_st;


int send2console(const char *msg);
int Msg_Handler(send_type_en passed_send_type ,const char *disp_msg);

#endif