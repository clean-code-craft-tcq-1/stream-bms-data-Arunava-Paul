#ifndef COMMON_HEADER_H
#define COMMON_HEADER_H

#include "stdio.h"
#include "string.h"

#define TRUE 1
#define FALSE 0

#define OK 1
#define NOT_OK 0
#define FILE_END_OK 2

#define UPDATE 0
#define ACCUMULATE 1

#define TEST_CODE_ACTIVE  FALSE

#if(TEST_CODE_ACTIVE == TRUE)
int Test_OpHdlr_positive_trigger(void);
int Test_OpHdlr_negetive_trigger(void);
int send2console(const char *msg);
int Test_BattParamColl(char *val , int col , int usage);
int Test_CSV_HandlerNoFile(void);
int Test_CSV_HandlerEndFile(void);
#endif

#endif
