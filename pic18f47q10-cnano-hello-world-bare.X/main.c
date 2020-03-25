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

#include <xc.h>
#include <stdint.h>
#include <string.h>

#define PPS_CONFIG_RD0_EUSART2_OUT 0x0B
#define BAUD_RATE_SYNC_0_BRG16_1_FOSC_1MHZ 0x19

static void CLK_init(void);
static void EUSART2_init(void);
static void PPS_init(void);
static void PORT_init(void);
static void EUSART2_write(uint8_t txData);

static void CLK_init(void)
{   
    /* Set HFINTOSC as new oscillator source. */
    OSCCON1 = _OSCCON1_NOSC1_MASK | _OSCCON1_NOSC2_MASK;

    /* Set HFFRQ to 1 MHz. */
    OSCFRQ = ~_OSCFREQ_HFFRQ_MASK;
}

static void EUSART2_init(void)
{
    BAUD2CON = _BAUD2CON_BRG16_MASK;
    
    RC2STA = _RC2STA_SPEN_MASK;
    
    TX2STA = _TX2STA_TXEN_MASK | _TX2STA_BRGH_MASK;
    
    SP2BRGL = BAUD_RATE_SYNC_0_BRG16_1_FOSC_1MHZ;
}

static void PPS_init(void) 
{
    RD0PPS = PPS_CONFIG_RD0_EUSART2_OUT; 
}

static void PORT_init(void)
{
    /* Configure RD0 as output. */
    TRISD &= ~_TRISD_TRISD0_MASK;
}

static void EUSART2_write(uint8_t txData)
{
    while(!(PIR3 & _PIR3_TX2IF_MASK))
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
