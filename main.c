/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Created by Tommy Gartlan

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F46K22
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define ENTRANCE PORTAbits.RA0
#define EXIT PORTAbits.RA1
#define CAR_FULL 10
#define CAR_FULL_LIGHT LATBbits.LB7

#define decrease_cars()  do { if(num != 0) num--; if(num <= CAR_FULL) CAR_FULL_LIGHT=0;} while(0)

void Initial(void);
void delay_1s(void);
void increase_cars(void);

//Global variables
unsigned char num = 0;
/*
                         Main application
 */
void main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();
    Initial();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        while (!ENTRANCE && !EXIT);
       
        if(ENTRANCE)
        {
            increase_cars();
        }
        else
        {
            decrease_cars();        
        }
        
        while (ENTRANCE || EXIT );
        
        LATB = LATB & 0x80;
        LATB = LATB | num;
    }
}

void Initial(void)
{
    //Note ANSELB
	//ADCON1 = 0x0f; //no longer relevant for this device
	//TRISA = 0xff;
	//TRISB = 0x00;
    
	LATB = 0x00;
    delay_1s();
    delay_1s();
    LATB = 0xFF;
    delay_1s();
    delay_1s();
    LATB = 0x00;
}

void delay_1s(void)
{
    unsigned char i;
    for (i=0;i<25;i++)
            __delay_ms(40);  //max value is 40 since this depends on the _delay() function which has a max number of cycles
    
}

void increase_cars(void)
{
    if(num != 31)
                num++;
            if(num > CAR_FULL)
                CAR_FULL_LIGHT=1;
}
/**
 End of File
*/