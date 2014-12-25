

void cal_init_eeprom(ES1653_Ch *phch);
void eeprom_sel_mode(ES1653_Ch *phch, ViInt16 mode);
void eeprom_set_addr(ES1653_Ch *phch, ViInt32 page_addr);
void eeprom_enable(ES1653_Ch *phch);
ViUInt16 eeprom_read_data(ES1653_Ch *phch);
void eeprom_write_data(ES1653_Ch *phch, ViUInt16 data);
void eeprom_reset(ES1653_Ch *phch);
