#include "handlecar.h"
#include <string.h>
#include <stdlib.h>

uint8_t gData[100];
uint8_t gFrame[100+5];
uint8_t gUartRxData[200];
uint8_t gUartTxData[200];

T_Car_Status gsCarStatus;
T_CARDATA gRxData;

void handle_monitor(uint8_t *Data, uint8_t frame_len)
{
	T_Monitor_Data  MonitorData;
	MonitorData.Header = Data[e_Header];
	MonitorData.Type = Data[e_Type];
	MonitorData.Cmd = Data[e_Cmd];
	MonitorData.Length = Data[e_Length];
	
	MonitorData.Data = malloc(MonitorData.Length*sizeof(uint8_t));
	memcpy(MonitorData.Data,&Data[e_Data],MonitorData.Length);
	MonitorData.End = Data[MonitorData.Length+5];

	if(MonitorData.Header == MONITOR_HEADER){
		if(MonitorData.Type == MONITOR_TYPE){
			switch (MonitorData.Cmd){
				case MONITOR_CMD_CARMNTOR_MODE:{
											//handle_monitor_data(MonitorData.Data,offset_total_mileage);
								       break;
							       }
				case MONITOR_CMD_POSITION_MODE:{
								       break;
							       }
				case MONITOR_CMD_STAND_MODE:{
								       break;
							       }
				case MONITOR_CMD_END_CALIBRATION:{
								       break;
							       }
				case MONITOR_CMD_ACCOUNT_REQUEST:{
								       break;
							       }
				case MONITOR_CMD_WARN_INFORMATION:{
								       break;
							       }
				case MONITOR_CMD_HINT_INFORMATION:{
								       break;
							       }
				default: break;
			}
		}
	}
}


uint8_t DataMask[] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};
uint8_t BllGetValueCarOneByte(T_CARDATA *RxData,uint8_t offset,uint8_t Bitstart,uint8_t Bitlen)
{
	uint8_t Retval;
	Retval = (RxData->Data[offset]<<Bitstart)&DataMask[Bitlen];
	return Retval;
}

//0 [4]
void MslGettotalmileage(T_CARDATA *RxData)
{
	memcpy(gsCarStatus.total_mileage,&(RxData->Data[offset_0]),Byte_len4);
}
//4 [2]
void MslGetcontinuout_mileage(T_CARDATA *RxData)
{
	memcpy(gsCarStatus.continuout_mileage,&(RxData->Data[offset_4]),Byte_len2);
}
//6
void MslGetoil_mass(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.oil_mass,&(RxData->Data[offset_6]),Byte_len1);
}
//7
void MslGetlow_oil(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.low_oil,&(RxData->Data[offset_7]),Byte_len1);
}

//8
void MslGetvoltage(T_CARDATA *RxData)
{
	gsCarStatus.voltage = BllGetValueCarOneByte(RxData,offset_8,start_bit0,bit_len8);
}
//9:0
void MslGetcar_lamp(T_CARDATA *RxData)
{
	gsCarStatus.car_lamp = BllGetValueCarOneByte(RxData,offset_9,start_bit0,bit_len1);	
}
//9:1
void MslGetbrake_fluid(T_CARDATA *RxData)
{
	gsCarStatus.brake_fluid = BllGetValueCarOneByte(RxData,offset_9,start_bit1,bit_len1);	
}
//9:2
void MslGetdriving_lockdoor(T_CARDATA *RxData)
{
	gsCarStatus.driving_lockdoor = BllGetValueCarOneByte(RxData,offset_9,start_bit2,bit_len1);	
}
//9:3
void MslGetpassenger_lockdoor(T_CARDATA *RxData)
{
	gsCarStatus.passenger_lockdoor = BllGetValueCarOneByte(RxData,offset_9,start_bit3,bit_len1);	
}
//9:4
void MslGetdriving_door(T_CARDATA *RxData)
{
	gsCarStatus.driving_door = BllGetValueCarOneByte(RxData,offset_9,start_bit4,bit_len1);	
}
//9:5
void MslGetpassenger_door(T_CARDATA *RxData)
{
	gsCarStatus.passenger_door = BllGetValueCarOneByte(RxData,offset_9,start_bit5,bit_len1);	
}
//9:6
void MslGetrear_cover(T_CARDATA *RxData)
{
	gsCarStatus.rear_cover = BllGetValueCarOneByte(RxData,offset_9,start_bit6,bit_len1);	
}
//9:7
void MslGetleftback_door(T_CARDATA *RxData)
{
	gsCarStatus.leftback_door = BllGetValueCarOneByte(RxData,offset_9,start_bit7,bit_len1);	
}

//10:0
void MslGetrightback_door(T_CARDATA *RxData)
{
	gsCarStatus.rightback_door = BllGetValueCarOneByte(RxData,offset_10,start_bit0,bit_len1);	
}

//10:[1:4]
void MslGetscuttle(T_CARDATA *RxData)
{
	gsCarStatus.scuttle = BllGetValueCarOneByte(RxData,offset_10,start_bit1,bit_len4);	
}

//10:[5:6]
void MslGetpowerState(T_CARDATA *RxData)
{
	gsCarStatus.powerstate = BllGetValueCarOneByte(RxData,offset_10,start_bit5,bit_len2);	
}

//11
void MslGettirepressure_fl(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.tirepressure_fl,&(RxData->Data[offset_11]),Byte_len1);
}
//12
void MslGettirepressure_fr(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.tirepressure_fr,&(RxData->Data[offset_12]),Byte_len1);
}
//13
void MslGettirepressure_rl(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.tirepressure_rl,&(RxData->Data[offset_13]),Byte_len1);
}
//14
void MslGettirepressure_rr(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.tirepressure_rr,&(RxData->Data[offset_14]),Byte_len1);
}
//15
void MslGetfetaltemperature_fl(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.fetaltemperature_fl,&(RxData->Data[offset_15]),Byte_len1);
}
//16
void MslGetfetaltemperature_fr(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.fetaltemperature_fr,&(RxData->Data[offset_16]),Byte_len1);
}
//17
void MslGetfetaltemperature_rl(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.fetaltemperature_rl,&(RxData->Data[offset_17]),Byte_len1);
}
//18
void MslGetfetaltemperature_rr(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.fetaltemperature_rr,&(RxData->Data[offset_18]),Byte_len1);
}
//19 [2]
void MslGetPM(T_CARDATA *RxData)
{
	memcpy(gsCarStatus.PM,&(RxData->Data[offset_19]),Byte_len2);
}
//21:[0:2]
void MslGetcloth_state(T_CARDATA *RxData)
{
	gsCarStatus.cloth_state = BllGetValueCarOneByte(RxData,offset_21,start_bit0,bit_len3);	
}
//22
void MslGetaverage_oil_consumption(T_CARDATA *RxData)
{
	memcpy(&gsCarStatus.average_oil_consumption,&(RxData->Data[offset_22]),Byte_len1);
}



uint8_t MslUartRx(uint8_t *Data){
	uint8_t Datalen = 0;
	//Datalen = Uart3GetData(Data);
	return Datalen;
}
void MslUartTx(uint8_t *Data,uint8_t Len){
	//Uart3Sent(Data,Len);
}
void MslUartSendState(void){
	MslUartTx((uint8_t*)&gsCarStatus,sizeof(T_Car_Status));
}
void MslPeriodTask(void)
{
	T_Monitor_Data Monitor_Data;
	uint8_t FlagReception = 0;
	MslUartSendState();
	FlagReception = MslUartRx(gUartRxData);
	
	Monitor_Data.Header = gUartRxData[e_Header];
	Monitor_Data.Type = gUartRxData[e_Type];

	Monitor_Data.Cmd = gUartRxData[e_Cmd];
	Monitor_Data.Length = gUartRxData[e_Length];
	Monitor_Data.Data = &gUartRxData[e_Data];
	Monitor_Data.End = gUartRxData[e_Data+Monitor_Data.Length];
	
	if(FlagReception != 0){
		if(Monitor_Data.Type == 0x00){
			memcpy(&gsCarStatus,&gUartRxData[e_Data],gUartRxData[e_Length]);
		}
	}
}

void MslCarcmd(uint8_t cmd,uint8_t param)
{
	T_CarCMD CarCMD;
	CarCMD.Header = CARCMD_HEADER;
	CarCMD.Type = CARCMD_TYPE;
	CarCMD.Cmd = cmd;
	CarCMD.Index = 0x00;
	CarCMD.Length = 0x01;
	CarCMD.Param = param;
	CarCMD.End = CARCMD_END;
	MslUartTx((uint8_t*)&CarCMD,sizeof(T_CarCMD));
}

uint8_t CardcmdResponse(T_CarCMD_Response * CarCMDResponse)
{
	uint8_t Retval;
	if(CarCMDResponse->Header == CARCMD_RESPONSE_HEADER){
		if(CarCMDResponse->Type == CARCMD_RESPONSE_TYPE){
				switch (CarCMDResponse->Cmd){
					case CARCMD_CMD_CARBINDING:{
						Retval = CarCMDResponse->Result;
					break;
					}
					case CARCMD_CMD_CENTRAL_CONTROLLOCK:{
						Retval = CarCMDResponse->Result;
					break;
					}
					case CARCMD_CMD_WINDSPEED:{
						Retval = CarCMDResponse->Result;
					break;
					}
				}
		}
	}
	Retval = CarCMDResponse->Result;
	return Retval;
}

//void handle_monitor_data(uint8_t * data,uint8_t offset)
//{

//	switch (offset){
//		case offset_total_mileage:{
//							uint8_t tmpdata[4];
//							memcpy(tmpdata,&data[offset],4);
//						  break;
//					  }
//		case offset_continuout_mileage:{
//							uint8_t tmpdata[2];
//							memcpy(tmpdata,&data[offset],2);
//						  break;
//					  }
//		case offset_oil_mass:{
//							uint8_t tmpdata;
//							tmpdata = data[offset];
//						  break;
//					  }
//		case offset_low_oil:{
//							uint8_t tmpdata;
//							tmpdata = data[offset];
//						  break;
//					  }
//		case offset_voltage:{
//							uint8_t tmpdata;
//							tmpdata = data[offset];
//						  break;
//					  }
//		case offset_9:{
//							uint8_t tmpdata;
//							tmpdata = data[offset];
//							
//						  break;
//					  }
//		case offset_10:{
//						  break;
//					  }
//		case offset_tirepresssureFL:{
//						  break;
//					  }
//		case offset_tirepressureFR:{
//						  break;
//					  }
//		case offset_tirepressureRL:{
//						  break;
//					  }
//		case offset_tirepressureRR:{
//						  break;
//					  }
//		case offset_fetaltemperatureFL:{
//						  break;
//					  }
//		case offset_fetaltemperatureFR:{
//						  break;
//					  }
//		case offset_fetaltemperatureRL:{
//						  break;
//					  }
//		case offset_fetaltemperatureRR:{
//						  break;
//					  }
//		case offset_PM:{
//						  break;
//					  }
//		case offset_clothstate:{
//						  break;
//					  }
//		case offset_averageoil:{
//						  break;
//					  }
//		default: break;
//	}
//}
