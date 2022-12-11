#include"STD_Types.h"
#include <util/delay.h>
#include "EEPROM_interface.h"
#include "TWI_interface.h"

void EEPROM_init(void)
{
	TWI_Master_init();
}

void EEPROM_write_byte(U8 data,U8 address,U8 block){
	    block=((0b1010000)|block);
	    TWI_Send_Start_Condition();
	    TWI_Send_Slave_Address_with_Write(block);
	    TWI_Master_Write_Data_Byte(address);
	    TWI_Master_Write_Data_Byte(data);
	    TWI_Send_Stop_Condition();
		_delay_ms(10);
    return;
}


void EEPROM_read_byte(U8* data,U8 address,U8 block){
	    block=((0b1010000)|block);
	    TWI_Send_Start_Condition();
	    TWI_Send_Slave_Address_with_Write(block);
	    TWI_Master_Write_Data_Byte(address);
	    TWI_Send_Repeated_Start();
	    TWI_Send_Slave_Address_with_Read(block);
	    TWI_Master_Read_Data_Byte_NACK(data);
		TWI_Send_Stop_Condition();
}


void EEPROM_write_string(const char* data,U8 address,U8 block){
			U8 counter=0;
	        while(1){
	        EEPROM_write_byte(data[counter],(address+counter),block);
			counter++;
			if(data[counter]=='\0'){
			   EEPROM_write_byte('/',(address+counter),block);
			   EEPROM_write_byte('0',(address+counter+1),block);
				break;
			}
			}
}
void EEPROM_read_string(char* str,U8 address,U8 block){
     U8 counter=0;
	while(1){
		EEPROM_read_byte(&str[counter],address+counter,block);
        	counter++;
        	if((str[counter-2]=='/')&&(str[counter-1]=='0')){
        		str[counter-2]='\0';
        		break;
        	}
	}
}
