#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

#include "adc.h"
#include "lcd.h"

// some changes have done in this code for repository
//this change have beed done for sub branch in master 
int page_display( );
void settings_update();
void Password_Enter(int );
int Menu_setup(int );

unsigned int EEPROM_read(unsigned int uiAddress)  ;
void EEPROM_write(unsigned int uiAddress, unsigned int ucData);

void CUTOFF_Battery_Update();
void CUTIN_Battery_Update();

void  CUTOFF_LVBD_Update();
void  CUTIN_LVBD_Update();


void  CUTOFF_LVLD_Update();
void  CUTIN_LVLD_Update();


/////////////////////////BATTERY VARIABLES///////////////////////////

int CUTOFF_battery_value=0;
int CUTIN_battery_value=0;

int CUTOFF_LVLD_value=0;
int CUTIN_LVLD_value=0;

int CUTOFF_LVBD_value=0;
int CUTIN_LVBD_value=0;
///////////////////////////testing variables///////////////////
float compare=467;
int number1;
int Var1;


int i;
int j;
int flag1=0;
int flag2=0;


char arr[10];
char buf[10];

////////////////////////// ADC Variables ////////////////////////////////////////////////
unsigned int DC_volt;
long Shunt_value;
char adcresult[4];
long ShuntAmps=300;
int current1=0;int current2=0;
char buffer1[5];
char buffer[5];

////////////////////////////////////////BUTTON VARIABLES//////////////////////////////

int UP=0;
int DOWN=0;
int ENTER=0;
int EXIT=0;
int count=0;

int Bcount=4;
//////////////////////////voltage string //////////////////////


char ID_str1[]="475";
int DC_voltage=0;
int offset =60;

int main(void)
{
	DDRD=0xff;   //lcd
	DDRB=0x00; //button iunput
	DDRA=0x00;  //adc
	DDRC=0xff;  // led for oalarms  2 3 4 
	
	
	initADC();
	Lcd_Init();
	
	Lcd_String("   Welcome to UAC   ");
	Lcd_Cmd(0xc0);
	Lcd_String("     Controller     ");
    Lcd_Cmd(0x01);
	_delay_ms(1000);
	Lcd_String("  Hold Enter Button ");
	Lcd_Cmd(0xc0);
	Lcd_String("    FOR SETTINGS    ");
	_delay_ms(2000);
	Lcd_Cmd(0x01);
	Lcd_Cmd(0x80);
	Lcd_String("DC VOLTAGE=");
	Lcd_Cmd(0xc0);
	Lcd_String("Current=");
	Lcd_Cmd(0x94);
	Lcd_String("load=");
	
	
	
	CUTIN_battery_value=  47;//EEPROM_read(3);
	CUTOFF_battery_value= 50;//EEPROM_read(5);
	
	CUTIN_LVLD_value=43;//EEPROM_read(7);
	CUTOFF_LVLD_value=45;////EEPROM_read(9);
	
	CUTIN_LVBD_value=   40;//EEPROM_read(11);
	CUTOFF_LVBD_value= 43;//EEPROM_read(13);
	
	
	
	//Lcd_String("Enter Password");
	//Lcd_Cmd(0xc0);	
	//Lcd_String(".....");
	
	
	                          
	while(1)
	{    
		
 /////////////////////   TESTING PRINTED VALUES /////////////		
		  //Lcd_Cmd(0x80);
		  //Lcd_Data(CUTIN_battery_value/10+48);
		  //Lcd_Data(CUTIN_battery_value%10+48);
		  //
		  //Lcd_Cmd(0x83);
		  //Lcd_Data(CUTOFF_battery_value/10+48);
		  //Lcd_Data(CUTOFF_battery_value%10+48);
		  //
		  //Lcd_Cmd(0x86);
		  //Lcd_Data(CUTIN_LVLD_value/10+48);
		  //Lcd_Data(CUTIN_LVLD_value%10+48);
		  //
		  //Lcd_Cmd(0x89);
		  //Lcd_Data(CUTOFF_LVLD_value/10+48);
		  //Lcd_Data(CUTOFF_LVLD_value%10+48);
		  //
		  //Lcd_Cmd(0x8C);
		  //Lcd_Data(CUTIN_LVBD_value/10+48);
		  //Lcd_Data(CUTIN_LVBD_value%10+48);
		  //
		  //
		  //Lcd_Cmd(0x8F);
		  //Lcd_Data(CUTOFF_LVBD_value/10+48);
		  //Lcd_Data(CUTOFF_LVBD_value%10+48);
		  
		  
//////////////  DC / SHUNT CURRENT READING VALUE ///////////////
          Lcd_Cmd(0x80);
          Lcd_String("DC VOLTAGE=");
          Lcd_Cmd(0xc0);
          Lcd_String("Current=");
          Lcd_Cmd(0x94);
          Lcd_String("load=");
          		  
		  DC_volt=ReadADC(0);
		  DC_volt = (DC_volt*5*12)/1024;
		  Lcd_Cmd(0x8B);
		  Lcd_Data(DC_volt/10+48);
		  Lcd_Data(DC_volt%10+48);
		    
		 Shunt_value=ReadADC(1);
		 Shunt_value= Shunt_value-512;
		 int current = (Shunt_value*(long) 300)/512;
		 
		 
		 current1= current*(-1);
		 itoa(current1,buffer,10);
		 Lcd_Cmd(0xcA);
		 Lcd_String(buffer);
		 
		 current2= current*(1);
		 Lcd_Cmd(0xc0);
		 itoa(current2,buffer1,10);
		 Lcd_Cmd(0x9E);
		 Lcd_String(buffer1);
		 _delay_ms(2000);
 
 ////////////////////////////////////////////////////////////////////////////////////////////////		 
		 //Lcd_Cmd(0x01);
		 //Lcd_Cmd(0xc80);
		 //Lcd_String("     Alarms   ");
		 //
		 //_delay_ms(2000);
		  		//if (current <0)
		  		//{
//
			  		//current1= current*(-1);
			  		//itoa(current1,buffer,10);
			  		//Lcd_Cmd(0xcB);
			  		//Lcd_String(buffer);
			  		//
		  		//}
		  		//
		  		//if (current >0)
		  		//{
			  		//current2= current*(1);
			  		//Lcd_Cmd(0xc0);
			  		//Lcd_String("current=");
			  		//itoa(current2,buffer1,10);
			  		//Lcd_Cmd(0x99);
			  		//Lcd_String(buffer1);
			  		//
		  		//}
		  
	//////////////////low bttry conditon//////////////////////////	 
		
		 //if (DC_volt<CUTIN_battery_value)    // below cuttin alarm generate 
		 //{
			  //PORTC= (1<<2);   /// alar on
		      //Lcd_Cmd(0xd4);
			  //Lcd_String("voltage low");flag1=1;
			 //
		 //}
		//
		//if (flag1==1 )
		//{
			//if (DC_volt>= CUTIN_battery_value  &&  DC_volt< CUTOFF_battery_value )
			//{
				//PORTC= (1<<2);
				//Lcd_Cmd(0xd4);
				//Lcd_String("voltage healthy");
			//}
			//
			//if (DC_volt >= CUTOFF_battery_value)
			//{
				//flag1=0;
				//
			//}
		//}
		//
		 //if (((DC_volt>= CUTIN_battery_value  &&  DC_volt<= CUTOFF_battery_value) || (DC_volt>CUTOFF_battery_value)) && (flag1==0))
		 //{
			 //PORTC&=~(1<<2);
			 //Lcd_Cmd(0xd4);
			 //Lcd_String("bttry ok");
			 //
		 //}
		//
  ///////////////////////Alarms   CONDITION///////////////
  
   if ( DC_volt<CUTIN_battery_value  )    // below cuttin alarm generate
     {
         PORTC|= (1<<5);
		 
        
		flag1=1;
          
     }
	 
	 if(flag1==1){
	 
	 if ( DC_volt>CUTIN_LVBD_value  && DC_volt<CUTIN_LVLD_value  &&  DC_volt<CUTIN_battery_value)
	  {
		  PORTC|= (1<<5)|(1<<4);
		  
	  }
	 else if (DC_volt<CUTIN_LVBD_value  && DC_volt<CUTIN_LVLD_value  &&  DC_volt<CUTIN_battery_value)
	   {
		   PORTC|= (1<<5)|(1<<4)|(1<<3); flag1=0;
		  
	   }
	 }
	 
	
		 if ((DC_volt>CUTOFF_LVBD_value)  && (flag1==1)  )
		{
			PORTC&=~(1<<3);flag2=1;
		}
		if(flag2==1)
		{
			if (DC_volt>CUTOFF_LVBD_value &&  DC_volt >CUTOFF_LVLD_value && DC_volt<CUTIN_battery_value)
			{
				PORTC&=~(1<<3);
				PORTC&=~(1<<4);
				
			}
			else if (DC_volt>CUTOFF_battery_value )
			{
				PORTC&=~(1<<3);
				PORTC&=~(1<<4);
				PORTC&=~(1<<5);
			
				flag2=0;
				
			}
			
		}


////////////////////setupt condition /////////////////////////////
      
			 if ((bit_is_set(PINB,PB2))&&(bit_is_clear(PINB,PB0))&&(bit_is_clear(PINB,PB1))&&(bit_is_clear(PINB,PB3)))
		         {
			       _delay_ms(100);
			        if ((bit_is_set(PINB,PB2))&&(bit_is_clear(PINB,PB0))&&(bit_is_clear(PINB,PB1))&&(bit_is_clear(PINB,PB3)))
			              {
			                    page_display();    // main page for enter pasword
			                    _delay_ms(1000);
			              }
		           }
		 }
}

void Password_Enter(int n)
{
	
	int click_count = 0;	
	int pass_value = 3;
	if(n==1)
	{
		while(click_count != 5)
		{
			if(  ( bit_is_set(PINB,PB0)) && (bit_is_clear(PINB, PB1)) )
			{
				_delay_ms(200);
				Lcd_Cmd(0xc0|click_count);
				Lcd_String("*");
				pass_value = pass_value+1;
				click_count++;
			    while(  ( bit_is_set(PINB,PB0)) && (bit_is_clear(PINB, PB1)) );
				
			}
			if(  ( bit_is_clear(PINB,PB0)) && (bit_is_set(PINB, PB1)) )// down
			{
				
				_delay_ms(200);
				Lcd_Cmd(0xc0|click_count);
				Lcd_String("*");
				pass_value = pass_value-1;
				click_count++;
				while(  ( bit_is_clear(PINB,PB0)) && (bit_is_set(PINB, PB1)) );
				
			}
			if(click_count == 5)
			{
				if(pass_value == 2)
				{
					_delay_ms(500);Lcd_Cmd(0x01);Lcd_String("   welcome to   ");_delay_ms(200);
					Lcd_Cmd(0xc0);Lcd_String("  Control Page  "); _delay_ms(1000); Lcd_Cmd(0x01);
					pass_value=0;click_count=0;

					settings_update();
					
					break;
				
				}
				else{ _delay_ms(500);Lcd_Cmd(0x01);Lcd_String(" Wrong pasword  ");_delay_ms(200);Lcd_Cmd(0x01); pass_value=0;click_count=0;break;}
				
			}
		}
	}
}

int page_display()
{

  //int pass_value=3;
  int n=0;
  int k=0;
  Lcd_Cmd(0x01);
  Lcd_Cmd(0x80);
  Lcd_String("Enter Password");
  Lcd_Cmd(0xc0);
  Lcd_String(".....");
  
  while(k!=2){
		 while(PINB&0b00001000) // exit
			  {
				  Lcd_Cmd(0x01);
				  Lcd_String("Exiting..");
				  n=0;k=2;
				  _delay_ms(400);
				  Lcd_Cmd(0x01);
				  break;
				  while(PINB&0b00001000);
	  
			  }
		 while( bit_is_set(PINB,PB2)) // enter
			  {
	               n=1;
				  Lcd_String("Enter pressed");k=2;
				   Password_Enter(n); 
				   Lcd_String("press exit..");  // working 
					k=0;n=0;
				  while(PINB&0b00000100);
			  }
           }
}





void settings_update()
{
	Lcd_Cmd(0x01);int n=0;
	int m=0;
	Lcd_String("Press ENTER ");
	
	while (n!=2)
	{    Lcd_Cmd(0xc0);Lcd_String("rchd here");n=0;
	   if(bit_is_set(PINB,PB2))
	     {
		     m=0;
		     Lcd_Cmd(0x01);
		     Lcd_Cmd(0x80);Lcd_String("Press Enter to Update");
			 Lcd_Cmd(0xc0);Lcd_String("*UPDATE BATTERY");
			 Lcd_Cmd(0x94);Lcd_String("*UPDATE LVBD ");
			 Lcd_Cmd(0xD4);Lcd_String("*UPDATE LVLD ");
		//while ((bit_is_clear (PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		   // while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting.stng.");_delay_ms(400);Lcd_Cmd(0x01);n=2;break;}
			
	         Lcd_Cmd(0x01);
		     Lcd_Cmd(0x80);Lcd_String(" UPDATE BTTRY VALUE");
		     Lcd_Cmd(0xC0);Lcd_String(" UPDATE LVBD VALUE");
		     Lcd_Cmd(0x94);Lcd_String(" UPDATE LVLD VALUE");
		    while(m!=2)
		        {
		           if(bit_is_set(PINB,PB2)){m=1;}
		           if(m==1)
		                  {
			
			               if((bit_is_set(PINB,PB0)) && (bit_is_clear(PINB, PB1)) )
			                  {
				
				                  Bcount++;
				                  while((bit_is_set(PINB,PB0)) && (bit_is_clear(PINB, PB1)));
			                   }
			               if((bit_is_clear(PINB,PB0)) && (bit_is_set(PINB, PB1)))
			                  {
				                  Bcount--;
				                  while((bit_is_clear(PINB,PB0)) && (bit_is_set(PINB, PB1)));
				
			                  }
						   
						Menu_setup(Bcount);
						//Lcd_Cmd(0xc0);Lcd_Cmd(0x01);
						//Lcd_String("reachd menu");//
						//break;
						
												//_delay_ms(1000);
						  }
			        //########################################################
			while( (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB, PB1))&& (bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB3)))
			       {
				Lcd_Cmd(0x01);Lcd_String("Exiting.setng.");_delay_ms(1000);Lcd_Cmd(0x01);m=2;n=2;break;  // working
				
			       }
				   
			}
	      }
      }
}


  
  
  
  
  int  Menu_setup(int x)
  {
	  int n=0; int m=0;int n0=0;int n1=0;int n2=0;
	  while(n!=2){
	  if(x<4)
	  {
		  
		  switch(x)
		  {
			  case 3:         Lcd_Cmd(0x80);
							  Lcd_String(">");
							  Lcd_Cmd(0xc0);
							  Lcd_String(" ");
							  Lcd_Cmd(0x94);
							  Lcd_String(" ");
							 
			          
			               while(bit_is_set(PINB,PB3)) {Lcd_Cmd(0x01);Lcd_String("Exiting..case");_delay_ms(400);Lcd_Cmd(0x01);n=2; x=4;m=2;break;}
			               
						     if(bit_is_set(PINB,PB2))
						     {
				              while(bit_is_set(PINB,PB2));
							  Lcd_Cmd(0x01);
							  Lcd_Cmd(0x80);
							  Lcd_String("PRESS UP CUTIN");
							  Lcd_Cmd(0xc0);
							  Lcd_String("PRESS DOWN CUTOFF");
				             while(n0!=2){
				 
							  if(bit_is_set(PINB,PB0))
							  {
								  while(bit_is_set(PINB,PB0));
								  Lcd_Cmd(0x01);Lcd_String("UPDATING CUTIN BTTRY");_delay_ms(1000);Lcd_Cmd(0x01);n0=2;n=2;
								  CUTIN_Battery_Update();
								  Lcd_String("rchd hig btr");
								  break;
							  }
							  if(bit_is_set(PINB,PB1))
							  {
								 while(bit_is_set(PINB,PB1));
								 Lcd_Cmd(0x01);Lcd_String("UPDATING CUTOFF BTTRY");_delay_ms(1000);Lcd_Cmd(0x01);n0=2;n=2;
								 CUTOFF_Battery_Update();
								 break;
							  }
						  
				     
				  
						  }
						 }
						// n=2;
				            break;
			
			  case 2:         Lcd_Cmd(0x80);
							  Lcd_String(" ");
							  Lcd_Cmd(0xc0);
							  Lcd_String(">");
							  Lcd_Cmd(0x94);
							  Lcd_String(" ");
			                  //int n1=0;
			             while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);n=2;x=4;m=2;break;}
			  
			             if(bit_is_set(PINB,PB2))
			                  {
				  
								 Lcd_Cmd(0x01);
								 Lcd_Cmd(0x80);
								 Lcd_String("PRESS UP CUTIN");
								 Lcd_Cmd(0xc0);
								 Lcd_String("PRESS DOWN CUTOFF");
								 while(n1!=2){
				
				                    if(bit_is_set(PINB,PB0))
				                              {
					                             Lcd_Cmd(0x01);Lcd_String("UPDATING CUTIN LVBD");_delay_ms(1000);Lcd_Cmd(0x01);n1=2;n=2;//n1=2;
				                                 CUTIN_LVBD_Update();
												 break;
				                               }
				                    if(bit_is_set(PINB,PB1))
				                               {
					                             Lcd_Cmd(0x01);Lcd_String("UPDATING CUTOFF LVBD");_delay_ms(1000);Lcd_Cmd(0x01);n1=2;n=2;//n1=2;
				                                 CUTOFF_LVBD_Update();
												 break;
				                               }
			                }
					}
			              // n=2;
						              break;
			  
			  
			  case 1:             Lcd_Cmd(0x80);
								  Lcd_String(" ");
								  Lcd_Cmd(0xc0);
								  Lcd_String(" ");
								  Lcd_Cmd(0x94);
								  Lcd_String(">");
								 
								  while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);n=2;x=4;m=2;break;}
			  
								  if(bit_is_set(PINB,PB2))
								  {
				  
									  Lcd_Cmd(0x01);
									  Lcd_Cmd(0x80);
									  Lcd_String("PRESS UP CUTIN");
									  Lcd_Cmd(0xc0);
									  Lcd_String("PRESS DOWN CUTOFF");
									  while(n2!=2){
					  
										  if(bit_is_set(PINB,PB0))
										  {
											  Lcd_Cmd(0x01);Lcd_String("UPDATING CUTIN LVBD");_delay_ms(1000);Lcd_Cmd(0x01);n2=2;n=2;//n1=2;
											  CUTIN_LVLD_Update();
											  break;
										  }
										  if(bit_is_set(PINB,PB1))
										  {
											  Lcd_Cmd(0x01);Lcd_String("UPDATING CUTOFF LVBD");_delay_ms(1000);Lcd_Cmd(0x01);n2=2;n=2;//n1=2;
											  CUTOFF_LVLD_Update();
											  break;
										  }
									  }
								  }
			                 break;
		 
	                         }
	                     }
	                     n=2;  
                         }
                    }




void  CUTIN_Battery_Update()
{
	unsigned long bttry_value1=0;
	int pos = 0;
	int update_pos = 0;
	int update_value = 0,k=1,j=0;
	char list_data[]="0123456789";
	Lcd_Cmd(0x01);
	
	for(int i=0;i<3;i++)
	{
		Lcd_Data(ID_str1[i]);
		_delay_ms(100);
	}
	Lcd_Cmd(0xc0|pos);Lcd_String("-");
	while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) );
	while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);break;}
	if(bit_is_set(PINB,PB2)){j=0;}
	while(j!=2)
	{
		if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String("  ");pos= pos+1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos>2){Lcd_Cmd(0xc0|(pos-1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String(" ");pos= pos-1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos < 0){Lcd_Cmd(0xc0|(pos+1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_set(PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) )
		{
			Lcd_Cmd(0x94);Lcd_String("updating"); k=0;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
			while(k!=2)
			{
				if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];  update_value += 1;// bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				// bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					update_value -= 1; Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];//bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				//bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)))
				{
					Lcd_Cmd(0x94);Lcd_String("updated ");_delay_ms(500);Lcd_Cmd(0x94);Lcd_String("        ");update_value=0;update_pos=0;k=2;
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));
				}
			}
			// return bttry_value;
		}

		while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)) )
		{
			Lcd_Cmd(0x01);bttry_value1=atoi(ID_str1);Lcd_String(ID_str1);Lcd_Cmd(0xc0);Lcd_Data((bttry_value1/10)/10+48);Lcd_Data((bttry_value1/10)%10+48);CUTIN_battery_value=bttry_value1/10;_delay_ms(500);EEPROM_write(3,CUTIN_battery_value);//int mem= read_from_memory(0);Lcd_Cmd(0xd4);
			//Lcd_Data(mem/10+48);
			//Lcd_Data(mem%10+48);/*eeprom_save_battery(bttry_value1);*/
			Lcd_Cmd(0xc0);Lcd_String("Exiting.."); _delay_ms(400);Lcd_Cmd(0x01);j=2;k=2;
			break;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));//j=2;k=2; 
		}
     }
}

  



void  CUTOFF_Battery_Update()
{
	unsigned long bttry_value1=0;
	int pos = 0;
	int update_pos = 0;
	int update_value = 0,k=1,j=0;
	char list_data[]="0123456789";
	Lcd_Cmd(0x01);
	
	for(int i=0;i<3;i++)
	{
		Lcd_Data(ID_str1[i]);
		_delay_ms(100);
	}
	Lcd_Cmd(0xc0|pos);Lcd_String("-");
	while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) );
	while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);break;}
	if(bit_is_set(PINB,PB2)){j=0;}
	while(j!=2)
	{
		if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String("  ");pos= pos+1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos>2){Lcd_Cmd(0xc0|(pos-1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String(" ");pos= pos-1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos < 0){Lcd_Cmd(0xc0|(pos+1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_set(PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) )
		{
			Lcd_Cmd(0x94);Lcd_String("updating"); k=0;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
			while(k!=2)
			{
				if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];  update_value += 1;// bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				// bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					update_value -= 1; Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];//bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				//bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)))
				{
					Lcd_Cmd(0x94);Lcd_String("updated ");_delay_ms(500);Lcd_Cmd(0x94);Lcd_String("        ");update_value=0;update_pos=0;k=2;
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));
				}
			}
			// return bttry_value;
		}

		while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)) )
		{
			Lcd_Cmd(0x01);bttry_value1=atoi(ID_str1);Lcd_String(ID_str1);Lcd_Cmd(0xc0);Lcd_Data((bttry_value1/10)/10+48);Lcd_Data((bttry_value1/10)%10+48);CUTOFF_battery_value=bttry_value1/10;_delay_ms(500);EEPROM_write(5,CUTOFF_battery_value);//int mem= read_from_memory(0);Lcd_Cmd(0xd4);
			//Lcd_Data(mem/10+48);
			//Lcd_Data(mem%10+48);/*eeprom_save_battery(bttry_value1);*/
			Lcd_Cmd(0xc0);Lcd_String("Exiting.."); _delay_ms(400);Lcd_Cmd(0x01);j=2;k=2;break;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));//j=2;k=2;
			
		}
	}
}



void  CUTIN_LVBD_Update()
{
	unsigned long bttry_value1=0;
	int pos = 0;
	int update_pos = 0;
	int update_value = 0,k=1,j=0;
	char list_data[]="0123456789";
	Lcd_Cmd(0x01);
	
	for(int i=0;i<3;i++)
	{
		Lcd_Data(ID_str1[i]);
		_delay_ms(100);
	}
	Lcd_Cmd(0xc0|pos);Lcd_String("-");
	while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) );
	while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);break;}
	if(bit_is_set(PINB,PB2)){j=0;}
	while(j!=2)
	{
		if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String("  ");pos= pos+1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos>2){Lcd_Cmd(0xc0|(pos-1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String(" ");pos= pos-1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos < 0){Lcd_Cmd(0xc0|(pos+1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_set(PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) )
		{
			Lcd_Cmd(0x94);Lcd_String("updating"); k=0;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
			while(k!=2)
			{
				if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];  update_value += 1;// bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				// bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					update_value -= 1; Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];//bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				//bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)))
				{
					Lcd_Cmd(0x94);Lcd_String("updated ");_delay_ms(500);Lcd_Cmd(0x94);Lcd_String("        ");update_value=0;update_pos=0;k=2;
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));
				}
			}
			// return bttry_value;
		}

		while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)) )
		{
			Lcd_Cmd(0x01);bttry_value1=atoi(ID_str1);Lcd_String(ID_str1);Lcd_Cmd(0xc0);Lcd_Data((bttry_value1/10)/10+48);Lcd_Data((bttry_value1/10)%10+48);CUTIN_LVBD_value=bttry_value1/10;_delay_ms(500);EEPROM_write(11,CUTIN_LVBD_value);//int mem= read_from_memory(0);Lcd_Cmd(0xd4);
			//Lcd_Data(mem/10+48);
			//Lcd_Data(mem%10+48);/*eeprom_save_battery(bttry_value1);*/
			Lcd_Cmd(0xc0);Lcd_String("Exiting.."); _delay_ms(400);Lcd_Cmd(0x01);j=2;k=2;break;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));//j=2;k=2;
			
		}
	}
}



void  CUTOFF_LVBD_Update()
{
	unsigned long bttry_value1=0;
	int pos = 0;
	int update_pos = 0;
	int update_value = 0,k=1,j=0;
	char list_data[]="0123456789";
	Lcd_Cmd(0x01);
	
	for(int i=0;i<3;i++)
	{
		Lcd_Data(ID_str1[i]);
		_delay_ms(100);
	}
	Lcd_Cmd(0xc0|pos);Lcd_String("-");
	while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) );
	while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);break;}
	if(bit_is_set(PINB,PB2)){j=0;}
	while(j!=2)
	{
		if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String("  ");pos= pos+1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos>2){Lcd_Cmd(0xc0|(pos-1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String(" ");pos= pos-1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos < 0){Lcd_Cmd(0xc0|(pos+1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_set(PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) )
		{
			Lcd_Cmd(0x94);Lcd_String("updating"); k=0;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
			while(k!=2)
			{
				if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];  update_value += 1;// bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				// bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					update_value -= 1; Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];//bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				//bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)))
				{
					Lcd_Cmd(0x94);Lcd_String("updated ");_delay_ms(500);Lcd_Cmd(0x94);Lcd_String("        ");update_value=0;update_pos=0;k=2;
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));
				}
			}
			// return bttry_value;
		}

		while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)) )
		{
			Lcd_Cmd(0x01);bttry_value1=atoi(ID_str1);Lcd_String(ID_str1);Lcd_Cmd(0xc0);Lcd_Data((bttry_value1/10)/10+48);Lcd_Data((bttry_value1/10)%10+48);CUTOFF_LVBD_value=bttry_value1/10;_delay_ms(500);EEPROM_write(13,CUTOFF_LVBD_value);//int mem= read_from_memory(0);Lcd_Cmd(0xd4);
			//Lcd_Data(mem/10+48);
			//Lcd_Data(mem%10+48);/*eeprom_save_battery(bttry_value1);*/
			Lcd_Cmd(0xc0);Lcd_String("Exiting.."); _delay_ms(400);Lcd_Cmd(0x01);j=2;k=2;break;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));//j=2;k=2;
			
		}
	}
}



void  CUTIN_LVLD_Update()
{
	unsigned long bttry_value1=0;
	int pos = 0;
	int update_pos = 0;
	int update_value = 0,k=1,j=0;
	char list_data[]="0123456789";
	Lcd_Cmd(0x01);
	
	for(int i=0;i<3;i++)
	{
		Lcd_Data(ID_str1[i]);
		_delay_ms(100);
	}
	Lcd_Cmd(0xc0|pos);Lcd_String("-");
	while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) );
	while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);break;}
	if(bit_is_set(PINB,PB2)){j=0;}
	while(j!=2)
	{
		if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String("  ");pos= pos+1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos>2){Lcd_Cmd(0xc0|(pos-1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String(" ");pos= pos-1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos < 0){Lcd_Cmd(0xc0|(pos+1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_set(PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) )
		{
			Lcd_Cmd(0x94);Lcd_String("updating"); k=0;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
			while(k!=2)
			{
				if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];  update_value += 1;// bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				// bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					update_value -= 1; Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];//bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				//bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)))
				{
					Lcd_Cmd(0x94);Lcd_String("updated ");_delay_ms(500);Lcd_Cmd(0x94);Lcd_String("        ");update_value=0;update_pos=0;k=2;
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));
				}
			}
			// return bttry_value;
		}

		while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)) )
		{
			Lcd_Cmd(0x01);bttry_value1=atoi(ID_str1);Lcd_String(ID_str1);Lcd_Cmd(0xc0);Lcd_Data((bttry_value1/10)/10+48);Lcd_Data((bttry_value1/10)%10+48);CUTIN_LVLD_value=bttry_value1/10;_delay_ms(500);EEPROM_write(7,CUTIN_LVLD_value);//int mem= read_from_memory(0);Lcd_Cmd(0xd4);
			//Lcd_Data(mem/10+48);
			//Lcd_Data(mem%10+48);/*eeprom_save_battery(bttry_value1);*/
			Lcd_Cmd(0xc0);Lcd_String("Exiting.."); _delay_ms(400);Lcd_Cmd(0x01);j=2;k=2;break;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));//j=2;k=2;
			
		}
	}
}




void  CUTOFF_LVLD_Update()
{
	unsigned long bttry_value1=0;
	int pos = 0;
	int update_pos = 0;
	int update_value = 0,k=1,j=0;
	char list_data[]="0123456789";
	Lcd_Cmd(0x01);
	
	for(int i=0;i<3;i++)
	{
		Lcd_Data(ID_str1[i]);
		_delay_ms(100);
	}
	Lcd_Cmd(0xc0|pos);Lcd_String("-");
	while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) );
	while(bit_is_set(PINB,PB3)){Lcd_Cmd(0x01);Lcd_String("Exiting..");_delay_ms(400);Lcd_Cmd(0x01);break;}
	if(bit_is_set(PINB,PB2)){j=0;}
	while(j!=2)
	{
		if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String("  ");pos= pos+1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos>2){Lcd_Cmd(0xc0|(pos-1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
		{
			_delay_ms(100);
			Lcd_Cmd(0xc0|pos);Lcd_String(" ");pos= pos-1; Lcd_Cmd(0xc0|pos);Lcd_String("-"); update_pos = pos; if(pos < 0){Lcd_Cmd(0xc0|(pos+1));Lcd_String(" ");pos = 0;}
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
		}
		
		if((bit_is_set(PINB,PB2)) && (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)) )
		{
			Lcd_Cmd(0x94);Lcd_String("updating"); k=0;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
			while(k!=2)
			{
				if((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];  update_value += 1;// bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_set(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				// bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)))
				{
					update_value -= 1; Lcd_Cmd(0x80|update_pos); Lcd_Data(list_data[update_value]);ID_str1[update_pos+0]=list_data[update_value];//bttry_value=atoi(ID_str1);
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_set(PINB,PB1)) && (bit_is_clear(PINB,PB3)));
				}
				//bttry_value=atoi(ID_str1);
				if((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)))
				{
					Lcd_Cmd(0x94);Lcd_String("updated ");_delay_ms(500);Lcd_Cmd(0x94);Lcd_String("        ");update_value=0;update_pos=0;k=2;
					while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));
				}
			}
			// return bttry_value;
		}

		while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)) )
		{
			Lcd_Cmd(0x01);bttry_value1=atoi(ID_str1);Lcd_String(ID_str1);Lcd_Cmd(0xc0);Lcd_Data((bttry_value1/10)/10+48);Lcd_Data((bttry_value1/10)%10+48);CUTOFF_LVLD_value=bttry_value1/10;_delay_ms(500);EEPROM_write(9,CUTIN_LVLD_value);//int mem= read_from_memory(0);Lcd_Cmd(0xd4);
			//Lcd_Data(mem/10+48);
			//Lcd_Data(mem%10+48);/*eeprom_save_battery(bttry_value1);*/
			Lcd_Cmd(0xc0);Lcd_String("Exiting.."); _delay_ms(400);Lcd_Cmd(0x01);j=2;k=2;break;
			while((bit_is_clear(PINB,PB2))&& (bit_is_clear(PINB,PB0)) && (bit_is_clear(PINB,PB1)) && (bit_is_set(PINB,PB3)));//j=2;k=2;
			
		}
	}
}


   
   unsigned int EEPROM_read(unsigned int uiAddress)
   {
	   /* Wait for completion of previous write */
	   while(EECR & (1<<EEWE))
	   ;
	   /* Set up address register */
	   EEAR = uiAddress;
	   /* Start eeprom read by writing EERE */
	   EECR |= (1<<EERE);
	   /* Return data from data register */
	   return EEDR;
   }
   
   void EEPROM_write(unsigned int uiAddress, unsigned int ucData)
   {
	   /* Wait for completion of previous write */
	   while(EECR & (1<<EEWE))
	   ;
	   /* Set up address and data registers */
	   EEAR = uiAddress;
	   EEDR = ucData;
	   /* Write logical one to EEMWE */
	   EECR |= (1<<EEMWE);
	   /* Start eeprom write by setting EEWE */
	   EECR |= (1<<EEWE);
   }

/*
void main ()
{
	DDRC=0x00;
	
	char out_str[30] = {0};
	Lcd_Init();
	ADC_init();
	
	while (1)
	{
		
		int adc1= adc_read(1);
		int volt = (adc1*2.5*10)/1024;
		//int bttry=volt/1023;
		
		sprintf(out_str, "volt = %d\r\n", volt);
		Lcd_Cmd(0xc0);
		Lcd_Data(volt/10+48);
		Lcd_Data(volt%10+48);
		//_delay_ms(1000);
	}
	
}*/








