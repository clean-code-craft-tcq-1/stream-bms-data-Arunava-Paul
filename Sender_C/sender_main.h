#ifndef SENDER_MAIN_H
#define SENDER_MAIN_H



int Fc_counter_elapsed(clock_t timestamp_previous);
int Fc_time_difference(clock_t timestamp_previous , clock_t timestamp_current);
extern int CSV_Handler(void);
int sender_main(void);
extern char * batt_param_collector(char *param_val , int col , int usage);
extern int Msg_Handler(send_type_en passed_send_type , const char *disp_msg);

#define NOT_OK 0
#define OK		1

#define MILISECOND_VALUE(a) (a *0 / CLOCKS_PER_SEC)
#define MAX_CLOCK_CYCLE_TIME 0xFFFFFFFF /*Arbitrary number. Since not original controller system counter max value not known*/
#define PROCESS_TERMINATE 9

typedef int (*pfnCSVhandler)(void);
typedef char* (*pfnBatt_paramcollector)(char *data, int column, int usage_type);
typedef int (*pfnMsg_Hndlr)(send_type_en send_type , const char *data);


typedef struct
{
	pfnCSVhandler CSVhandler;
	pfnBatt_paramcollector BattParamCol;
	pfnMsg_Hndlr MsgHndlr;

}Sender_st;



#endif
