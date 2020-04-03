/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. 
    
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

/* Disable Watch Dog Timer */
#pragma config WDTE = OFF   
/* Low voltage programming enabled , RE3 pin is MCLR */
#pragma config LVP = ON

#include <xc.h>
#include <stdint.h>
#include <string.h>

static void CLK_init(void);
static void EUSART2_init(void);
static void PPS_init(void);
static void PORT_init(void);
static void EUSART2_write(uint8_t txData);

static void CLK_init(void)
{   
    /* Set HFINTOSC as new oscillator source */
    OSCCON1bits.NOSC = 0b011;
    
    /* Set HFFRQ to 1 MHz */
    OSCFRQbits.HFFRQ = 0;
}

static void EUSART2_init(void)
{
    /* Transmit Enable */
    TX2STAbits.TXEN = 1;
    /* High Baud Rate Select */
    TX2STAbits.BRGH = 1;
    
    /* 16-bit Baud Rate Generator is used */
    BAUD2CONbits.BRG16 = 1;
    
    /* Baud rate 9600 */
    SP2BRGL = 0x19;
    
    /* Serial Port Enable */
    RC2STAbits.SPEN = 1;
}

static void PPS_init(void) 
{
    /* RD0 is TX2 */
    RD0PPS = 0x0B;
}

static void PORT_init(void)
{
    /* Configure RD0 as output. */
    TRISDbits.TRISD0 = 0;
}

static void EUSART2_write(uint8_t txData)
{
    while(0 == PIR3bits.TX2IF)
    {
        ;
    }

    TX2REG = txData;
}

void main(void)
{
    char msg[] = "Hello World\r\n";

    CLK_init();
    EUSART2_init();  
    PPS_init();   
    PORT_init();
    
    while(1) 
    {
        for(uint8_t i = 0; i < strlen(msg); i++) 
        {
            EUSART2_write(msg[i]);
        }
    }
}
