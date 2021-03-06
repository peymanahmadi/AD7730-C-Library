#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <alcd.h>
#include <spi.h>
#include <stdlib.h>                       

#define ADC_RDY         PINC.0
#define ADC_CS          PORTC.1
#define SYS_ZERO_MODE   0b11000000
#define SELF_CALB_MODE  0b10100000
#define CONT_CNV_MODE   0b00100000                         
#define UPDATE_RATE     150
#define ADC_Vin         1 //0=10mv,1=20mv,2=40mv,3=80mv
#define MODE_LOW        0b10000000|(16*ADC_Vin)

unsigned char ADC_MODE_BH;

//********************************************************

void RESET_AD7730(void)
    {  
    ADC_CS=0;
    spi(255);
    spi(255);
    spi(255);
    spi(255);
    ADC_CS=1;
    }
            
//********************************************************

void ADC_FILTER_SET(void)
    {
    unsigned int filter;
    unsigned char filterL,filterH;
    filter=307200/UPDATE_RATE;
    if(filter>2048) filter=2048;
    filterL=filter % 16;
    filterL=filterL*16;
    filterH=filter / 16;        
    ADC_CS=0;
    spi(0b00000011);
    spi(filterH);
    spi(filterL);
    spi(0);
    ADC_CS=1;
    }
            
//********************************************************

void ADC_MODE_SET(void)
    {     
    ADC_CS=0;
    spi(0b00000010);
    spi(ADC_MODE_BH);
    spi(MODE_LOW);
    ADC_CS=1;
    }
     
//********************************************************

unsigned int ADC_READ_DATA(void)
    {
    unsigned int adc_val;
    ADC_CS=0;
    spi(0b00010001);
    adc_val=(unsigned int) spi(255)*256 + spi(255);
    ADC_CS=1;
    return(adc_val);
    }
      
//********************************************************

void main(void)
{
unsigned int ADC; 
bit ADC_SEL,ZERO_ADC;
unsigned char sum_cntr,ADC1,ADC2;
unsigned long int sum;
PORTA=0x00;
DDRA=0x00;

PORTB=0x00;
DDRB=0b10111111;

PORTC=0x00;
DDRC=0b11111110;

PORTD=0x00;
DDRD=0xff;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 9600
UCSRA=0x00;
UCSRB=0x18;
UCSRC=0x86;
UBRRH=0x00;
UBRRL=0x33;

// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 250.000 kHz
// SPI Clock Phase: Cycle Half
// SPI Clock Polarity: High
// SPI Data Order: MSB First
SPCR=0x54;
SPSR=0x00;

lcd_init(16);
lcd_clear();
lcd_gotoxy(0,0);
lcd_putsf("FORCE:        Kg");

RESET_AD7730();
ADC_FILTER_SET();
ADC_MODE_BH=SYS_ZERO_MODE;
ADC_MODE_SET();
ADC_MODE_BH= CONT_CNV_MODE;
ADC_MODE_SET();
delay_ms(1000);
ZERO_ADC=0;
ADC_SEL=1;
sum_cntr=0;
sum=0;
ADC=0;

while (1) 
  {  
         
   
    //********************************************************************                
    
    if(ADC_RDY==0)
        {        
           
               ADC=ADC_READ_DATA(); 
                sum=sum+ADC;
                if(++sum_cntr==50)
                    {                   
                    sum_cntr=0;
                    ADC=sum/50;                   
                    sum=0;
                    ADC&=0xFFFC;
                                                            
                    ADC1=ADC;
                    ADC2=ADC>>8;
                    putchar (ADC1);
                    putchar (ADC2);                                      
                                                                          
                     lcd_gotoxy(11,0);
                      lcd_putchar((ADC%10)+48);
                         ADC/=10;         
                    lcd_gotoxy(10,0);
                      lcd_putchar((ADC%10)+48);
                        ADC/=10;        
                     lcd_gotoxy(9,0);
                      lcd_putchar((ADC%10)+48);
                        ADC/=10;       
                     lcd_gotoxy(8,0);
                        lcd_putchar((ADC%10)+48);
                             ADC/=10;        
                     lcd_gotoxy(7,0);
                        lcd_putchar((ADC%10)+48);
                           ADC/=10;
                      
                    }; 
               
            
        }; 
    
   }
   }
   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
    
    
    
    
     if(ADC_RDY==0){
      ADC=ADC_READ_DATA(); 
             
       ADC=ADC_READ_DATA(); 
                sum=sum+ADC;
                if(++sum_cntr==50)
                    {                   
                    sum_cntr=0;
                    ADC=sum/50;
                    sum=0; 
                    
                       lcd_gotoxy(11,0);
                      lcd_putchar((ADC%10)+48);
                         ADC/=10;         
                    lcd_gotoxy(10,0);
                      lcd_putchar((ADC%10)+48);
                        ADC/=10;        
                     lcd_gotoxy(9,0);
                      lcd_putchar((ADC%10)+48);
                        ADC/=10;       
                     lcd_gotoxy(8,0);
                        lcd_putchar((ADC%10)+48);
                             ADC/=10;        
                     lcd_gotoxy(7,0);
                        lcd_putchar((ADC%10)+48);
                           ADC/=10;
                    
         }
           
                 
                             
    };
}

}

  */















      
  
    
          
           
      
      
      
      
      
              
      
      
      
      
      
      
      //********************************************************************                
     /* if(ADC_RDY==0)
        { PORTC.2=1;
         
        if(ZERO_ADC)
            {   
            ADC_MODE_BH=SYS_ZERO_MODE;
            ADC_MODE_SET();
            ZERO_ADC=0;
            ADC_SEL=1;
            }
        else
            {
            if(ADC_SEL)
                { 
                ADC_SEL=0;     
                ADC_MODE_BH=CONT_CNV_MODE;
                ADC_MODE_SET();		        
                }
            else
                {        
                temp=ADC_READ_DATA(); 
                sum=sum+temp;
                if(++sum_cntr==50)
                    {                   
                    sum_cntr=0;
                    ADC=sum/50;
                    sum=0; 
                     temp=ADC_READ_DATA();
                     lcd_gotoxy(11,0);
                      lcd_putchar((ADC%10)+48);
                         ADC/10;         
                    lcd_gotoxy(10,0);
                      lcd_putchar((ADC%10)+48);
                        ADC/10;        
                     lcd_gotoxy(9,0);
                      lcd_putchar((ADC%10)+48);
                        ADC/10;       
                     lcd_gotoxy(8,0);
                        lcd_putchar((ADC%10)+48);
                             ADC/10;        
                     lcd_gotoxy(7,0);
                        lcd_putchar((ADC%10)+48);
                           ADC/10;
                    
                    
                    // ftoa((ADC-32768)/100,2,str1); 
                     //lcd_gotoxy(7,0);
                     //lcd_puts(str1);   
                    }; 
                };
            };
        };                      */           
    