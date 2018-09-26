#include "handlecar.h"
extern uint8_t gFrame[100+5];
extern void MslPeriodTask(void);
extern void MslCarcmd(uint8_t cmd,uint8_t param);


int main(void)
{
	while(1){
	MslCarcmd((uint8_t)CARCMD_CMD_CARBINDING,(uint8_t)CARCMD_PARAM_0);
	MslPeriodTask();
	}
}
