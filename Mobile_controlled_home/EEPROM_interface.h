

#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_init(void);
void EEPROM_write_byte(U8 data,U8 address,U8 block);
void EEPROM_read_byte(U8*data,U8 address,U8 block);
void EEPROM_write_string(const char* data,U8 address,U8 block);
void EEPROM_read_string(char* str,U8 address,U8 block);
#endif








