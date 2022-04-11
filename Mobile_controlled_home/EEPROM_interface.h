

#ifndef EEPROM_H_
#define EEPROM_H_


void EEpromInit(void);
void EEpromWriteByte(char,U8,U8);
char EEpromReadByte(U8,U8);
void EEprom_write_string(char* data,U8 address,U8 block);
char* EEprom_read_string(U8 address,U8 block);
#endif








