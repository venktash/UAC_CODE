
#define RS PD0
#define RW PD1
#define EN PD2
#define lcd PORTD

void Lcd_Data(char Data);
void Lcd_Cmd(char cmd);
void Lcd_Init();
void Lcd_String(char *str);

void Lcd_Init()
{
	DDRD = 0XFF;
	Lcd_Cmd(0x02);
	Lcd_Cmd(0x28);
	Lcd_Cmd(0x06);
	Lcd_Cmd(0x0C);
	Lcd_Cmd(0x80);
	Lcd_Cmd(0x01);

}

void Lcd_Cmd(char cmd)
{
	lcd = cmd&0xF0;
	lcd = lcd&~(1<<RS);//RS = 0
	lcd = lcd&~(1<<RW);//RW = 0
	lcd = lcd|(1<<EN); //EN = 1
	_delay_ms(10);
	lcd = lcd&~(1<<EN);//EN = 0
	_delay_ms(10);
	
	lcd = (cmd<<4)&0XF0;
	lcd = lcd&~(1<<RS);//RS = 0
	lcd = lcd&~(1<<RW);//RW = 0
	lcd = lcd|(1<<EN); //EN = 1
	_delay_ms(10);
	lcd = lcd&~(1<<EN);//EN = 0
	_delay_ms(10);
}
void Lcd_Data(char Data)
{
	lcd = Data&0xF0;
	lcd = lcd|(1<<RS);//RS = 1
	lcd = lcd&~(1<<RW);//RW = 0
	lcd = lcd|(1<<EN); //EN = 1
	_delay_ms(10);
	lcd = lcd&~(1<<EN);//EN = 0
	_delay_ms(10);
	
	lcd = (Data<<4)&0xF0;
	lcd = lcd|(1<<RS);//RS = 1
	lcd = lcd&~(1<<RW);//RW = 0
	lcd = lcd|(1<<EN); //EN = 1
	_delay_ms(10);
	lcd = lcd&~(1<<EN);//EN = 0
	_delay_ms(10);
}
void Lcd_String(char *str)
{
	while(*str!='\0')
	{
		Lcd_Data(*str);
		str++;
	}
}






