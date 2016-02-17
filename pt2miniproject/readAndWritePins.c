#include <p24FJ128GB206.h>
#include <stdint.h>
#include <stdio.h>
#include "config.h"
#include "common.h"
#include "ui.h"
#include "usb.h"
#include "pin.h"
#include "spi.h"
#include "oc.h"
#include "uart.h"
#include "timer.h"

#define TOGGLE_LED1         1
#define TOGGLE_LED2         2
#define READ_SW1            3
#define ENC_WRITE_REG       4
#define ENC_READ_REG        5
#define SET_VALS            6
#define GET_VALS
#define TOGGLE_LED3         8 
#define READ_SW2            9
#define READ_SW3            10

#define REG_MAG_ADDR        0x3FFE

uint16_t val1, val2;
uint16_t revs = 0;
int16_t prevAngle = 0;

_PIN *ENC_SCK, *ENC_MISO, *ENC_MOSI;
_PIN *ENC_NCS;
_PIN *VOLTAGE0;

WORD enc_readReg(WORD address) {
    WORD cmd, result;
    uint16_t degree;
    cmd.w = 0x4000|address.w; //set 2nd MSB to 1 for a read
    cmd.w |= parity(cmd.w)<<15; //calculate even parity for

    pin_clear(ENC_NCS);
    spi_transfer(&spi1, cmd.b[1]);
    spi_transfer(&spi1, cmd.b[0]);
    pin_set(ENC_NCS);

    pin_clear(ENC_NCS);
    result.b[1] = spi_transfer(&spi1, 0);
    result.b[0] = spi_transfer(&spi1, 0);
    pin_set(ENC_NCS);
    // printf("b[0]: %i\n\r", result.b[0]);
    // printf("b[1]: %i\n\r", result.b[1]);
    degree = (result.b[1]<<8) | result.b[0];
    //printf("Print Degree: %i\n\r", degree);
    resultMath(degree);
    return result;

}

//TOREAD ON SCREEN run
// screen /dev/ttyUSB0 19200

void resultMath(uint16_t result) {
    int16_t Angle; 
    int16_t diff;

    //printf("Print Result: %i\n\r", result);
    // printf("%u\n\r", (result >> 15));
    // printf("%u\n\r", (result >> 15) & (uint8_t)01);
    if(~((result >> 15) & 1)) {
        Angle = result & 16383;
        diff = Angle-prevAngle;
        if (diff> 5000){
            revs++;
        }
        else if (diff< -5000){
                revs--;
            }


        // printf("Print Angle: %i\n\r", Angle);
        // printf("Print PrevA: %i\n\r", prevAngle);
        // printf("Print diff: %i\n\r", diff);     
        // printf("Print revs: %i\n\r", revs);   
        prevAngle = Angle;

        //Angle = Angle << 2; 
        //printf("%u\n\r", Angle);
        // degree = (Angle * 45);
        // printf("%u\n\r", degree);
        // degree = degree/(01<<12);
        // printf("%u\n\r", degree);
        //return degree;
    }

}

//void ClassRequests(void) {
//    switch (USB_setup.bRequest) {
//        default:
//            USB_error_flags |= 0x01;                    // set Request Error Flag
//    }
//}

void VendorRequests(void) {
    WORD32 address;
    WORD result;
    WORD temp; 

    switch (USB_setup.bRequest) {
        case TOGGLE_LED1:
            led_toggle(&led1);
            BD[EP0IN].bytecount = 0;         // set EP0 IN byte count to 0
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        case TOGGLE_LED2:
            led_toggle(&led2);
            BD[EP0IN].bytecount = 0;         // set EP0 IN byte count to 0
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        case READ_SW1:
            BD[EP0IN].address[0] = (uint8_t)sw_read(&sw1);
            BD[EP0IN].bytecount = 1;         // set EP0 IN byte count to 1
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        case ENC_READ_REG:
            result = enc_readReg(USB_setup.wValue);
            BD[EP0IN].address[0] = result.b[0];
            BD[EP0IN].address[1] = result.b[1];
            BD[EP0IN].bytecount = 2;         // set EP0 IN byte count to 1
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        case TOGGLE_LED3:
            led_toggle(&led3);
            BD[EP0IN].bytecount = 0;         // set EP0 IN byte count to 0
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        case READ_SW2:
            BD[EP0IN].address[0] = (uint8_t)sw_read(&sw2);
            BD[EP0IN].bytecount = 1;         // set EP0 IN byte count to 1
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        case READ_SW3:
            BD[EP0IN].address[0] = (uint8_t)sw_read(&sw3);
            BD[EP0IN].bytecount = 1;         // set EP0 IN byte count to 1
            BD[EP0IN].status = 0xC8;         // send packet as DATA1, set UOWN bit
            break;
        // case SET_VALS:
        //     val1 = USB_setup.wValue.w;
        //     val2 = USB_setup.wIndex.w;
        //     BD[EP0IN].bytecount = 0;    // set EP0 IN byte count to 0 
        //     BD[EP0IN].status = 0xC8;    // send packet as DATA1, set UOWN bit
        //     break;
        // case GET_VALS:
        //     temp.w = val1;
        //     BD[EP0IN].address[0] = temp.b[0];
        //     BD[EP0IN].address[1] = temp.b[1];
        //     temp.w = val2;
        //     BD[EP0IN].address[2] = temp.b[0];
        //     BD[EP0IN].address[3] = temp.b[1];
        //     BD[EP0IN].bytecount = 4;    // set EP0 IN byte count to 4
        //     BD[EP0IN].status = 0xC8;    // send packet as DATA1, set UOWN bit
        //     break;        
        default:
            USB_error_flags |= 0x01;    // set Request Error Flag
    }
}

void VendorRequestsIn(void) {
    switch (USB_request.setup.bRequest) {
        default:
            USB_error_flags |= 0x01;                    // set Request Error Flag
    }
}

void VendorRequestsOut(void) {
//    WORD32 address;
//
//    switch (USB_request.setup.bRequest) {
//        case ENC_WRITE_REGS:
//            enc_writeRegs(USB_request.setup.wValue.b[0], BD[EP0OUT].address, USB_request.setup.wLength.b[0]);
//            break;
//        default:
//            USB_error_flags |= 0x01;                    // set Request Error Flag
//    }
}

int16_t main(void) {
    init_clock();
    init_ui();
    init_pin();
    init_spi();
    init_timer();
    init_oc();
    init_uart();

    float freq = 10000;
    uint16_t duty = 50;
    uint8_t val = 1;


    ENC_MISO = &D[1];
    ENC_MOSI = &D[0];
    ENC_SCK = &D[2];
    ENC_NCS = &D[3];
    VOLTAGE0 = &A[0];

    int val1 = 0;
    int val2 = 0;

    // resultMath(0000111100001111); 

    pin_digitalOut(ENC_NCS);
    pin_set(ENC_NCS);

    timer_setPeriod(&timer2, .9);
    timer_start(&timer2);

    spi_open(&spi1, ENC_MISO, ENC_MOSI, ENC_SCK, 2e6 ,1);

    InitUSB();                              // initialize the USB registers and serial interface engine
    while (USB_USWSTAT!=CONFIG_STATE) {     // while the peripheral is not configured...
        ServiceUSB();                       // ...service USB requests
    }



    while (1) {
        oc_pwm(&oc1, &D[8], &timer3, freq, duty); 
        oc_pwm(&oc1, &D[6], &timer3, freq, duty); 
        ServiceUSB();                       // service any pending USB requests
        
        if (timer_flag(&timer2)) {
            timer_lower(&timer2);
            uint16_t voltage0Reading = pin_read(VOLTAGE0);
            printf("Voltage 0 = %u\n\r", voltage0Reading);
            led_toggle(&led1);
        }



    }
}