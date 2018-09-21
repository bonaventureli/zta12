#include "handlecar.h"
#include <string.h>
#include <stdlib.h>

typedef enum {
    e_Header,
    e_Type,
    e_Cmd,
    e_Length,//3
	  e_Data,
}e_Frame;

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
	
	//free(MonitorData.Data);
	
	if(MonitorData.Header == MONITOR_HEADER){
		if(MonitorData.Type == MONITOR_TYPE){
			switch (MonitorData.Cmd){
				case MONITOR_CMD_CARMNTOR_MODE:{
											handle_monitor_data();
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

void handle_monitor_data(uint8_t offset)
{
	switch (offset){
		case offset_total_mileage:{
						  break;
					  }
		case offset_continuout_mileage:{
						  break;
					  }
		case offset_oil_mass:{
						  break;
					  }
		case offset_low_oil:{
						  break;
					  }
		case offset_voltage:{
						  break;
					  }
		case offset_9:{
						  break;
					  }
		case offset_10:{
						  break;
					  }
		case offset_tirepresssureFL:{
						  break;
					  }
		case offset_tirepressureFR:{
						  break;
					  }
		case offset_tirepressureRL:{
						  break;
					  }
		case offset_tirepressureRR:{
						  break;
					  }
		case offset_fetaltemperatureFL:{
						  break;
					  }
		case offset_fetaltemperatureFR:{
						  break;
					  }
		case offset_fetaltemperatureRL:{
						  break;
					  }
		case offset_fetaltemperatureRR:{
						  break;
					  }
		case offset_PM:{
						  break;
					  }
		case offset_clothstate:{
						  break;
					  }
		case offset_averageoil:{
						  break;
					  }
		default: break;
	}
}
