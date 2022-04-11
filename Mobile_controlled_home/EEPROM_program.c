
#include"string.h"
#include"STD.Types.h"
#define F_CPU 8000000
#include <util/delay.h>
#include "eeprom.h"
#include "I2C_interface.h"
char I2C_string[2][22];
void EEpromInit(void)
{
	I2C_Master_init();
}

void EEpromWriteByte(char data,U8 address,U8 block){
	    block=((0b10100000)|(block<<1));
		I2C_start();
		I2C_Master_transmit(block);
		I2C_Master_transmit(address);
		I2C_Master_transmit(data);
		I2C_stop();
		_delay_ms(10);
    return;
}


char EEpromReadByte(U8 address,U8 block){
	block=((0b10100000)|(block<<1));
	    char data;
		I2C_start();
		I2C_Master_transmit(block);
	    I2C_Master_transmit(address);
		I2C_start();
		I2C_Master_transmit((block+1));
		data = I2C_Master_Recieve_data_NACK();
		I2C_stop();
    return (char)data;
}
void EEprom_write_string(char* data,U8 address,U8 block){
			U8 i=0;
	        while(1){
	        EEpromWriteByte(data[i],address,block);
			i++;
			address++;
			if(data[i]=='\0'){
			   EEpromWriteByte('/',address,block);
			   EEpromWriteByte('0',(address+1),block);
				break;
			}
			}
}
char* EEprom_read_string(U8 address,U8 block){
     U8 j=0;
    static U8 i=0;
    if(i==2){
	    memset(I2C_string,0,sizeof(I2C_string));
	    i=0;
    }
	while(1){
        	I2C_string[i][j]=EEpromReadByte(address+j,block);
        	j++;
        	if((I2C_string[i][j-2]=='/')&&(I2C_string[i][j-1]=='0')){
        		I2C_string[i][j-2]='\0';
        		break;
        	}
        }
	    i++;
        return I2C_string[i-1];
}
