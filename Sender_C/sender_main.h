#ifndef SENDER_MAIN_H
#define SENDER_MAIN_H


float string2float(char *str);
extern int CSV_Handler(void);
extern char * batt_param_collector(char *param_val , int col , int usage);
extern int Msg_Handler(send_type_en passed_send_type , const char *disp_msg);

#define NOT_OK 0
#define OK		1

typedef int (*pfnCSVhandler)(void);
typedef char* (*pfnBatt_paramcollector)(char *data, int column, int usage_type);
typedef int (*pfnMsg_Hndlr)(const char *data);


typedef struct
{
	pfnCSVhandler CSVhandler;
	pfnBatt_paramcollector BattParamCol;
	pfnMsg_Hndlr MsgHndlr;

}Sender_st;

void sender_main(void);

#endif