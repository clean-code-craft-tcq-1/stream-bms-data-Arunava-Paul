#ifndef PARAMETER_COLLECTOR_H
#define PARAMETER_COLLECTOR_H


typedef enum
{
	temperature_param = 0,
	SOC_param,
	current_param,
	charge_rate_param,
	MAX_PARAM_TYPE
}batt_param_type_en;

typedef struct
{
	batt_param_type_en batt_param_type; 
	char batt_param_val[10];
	char param_name[30];
}batt_param_st;

char * batt_param_collector(char *param_val , int col , int usage);




#endif