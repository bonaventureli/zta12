
/*********************************************************************
 * @brief   Process a pending Simple Profile characteristic value change
 *          event.
 * @param   
 * @version 0.1
 * @return  None.
 * @auther lifei
 * @update time 2018.9.21
 */


 /*Header        Type 	Cmd 	Length    Data     End
 * 1Byte        1Byte   1Byte   1Byte     1Byte    1Byte
 * */

#define MONITOR_HEADER 0x7E
#define MONITOR_TYPE   0x00

#define MONITOR_CMD_CARMNTOR_MODE 0xFF
#define MONITOR_CMD_POSITION_MODE 0x01
#define MONITOR_CMD_STAND_MODE    0x02
#define MONITOR_CMD_END_CALIBRATION 0x03
#define MONITOR_CMD_ACCOUNT_REQUEST 0x04
#define MONITOR_CMD_WARN_INFORMATION 0x10
//...
#define MONITOR_CMD_HINT_INFORMATION 0X30

typedef struct{
	uint8_t Header;
	uint8_t Type;
	uint8_t Cmd;
	uint8_t Length;
	uint8_t *Data;
	uint8_t End;
}T_Monitor_Data;

typedef signed   char      int8_t;
typedef signed   short     int16_t;
typedef signed   long      int32_t;
typedef signed   long long int64_t;

typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned long      uint32_t;
typedef unsigned long long uint64_t;

#define MAXDATA_LENGTH 100

uint8_t gData[MAXDATA_LENGTH];
uint8_t gFrame[MAXDATA_LENGTH+5];

