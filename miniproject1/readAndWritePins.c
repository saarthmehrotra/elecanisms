#include <p24FJ128GB206.h>
#include "config.h"
#include "common.h"
#include "ui.h"
#include "timer.h"
#include "pin.h"
#include "oc.h"

int16_t main(void) {
    init_clock();
    init_ui();
    init_timer();
    init_pin();
    init_oc();

    float freq = 25000;
    uint16_t duty = 50;
    led_on(&led1);
    led_off(&led2);
    timer_setPeriod(&timer2, 0.5);
    timer_start(&timer2);
//    timer_setPeriod(&timer3, 0.5);
    timer_start(&timer3);



    while (1) {
        if (timer_flag(&timer2)) {
            timer_lower(&timer2);
            led_toggle(&led1);
            led_toggle(&led2);
        }


        
        oc_pwm(&oc8, &D[8], &timer3, freq, duty); 
        oc_pwm(&oc8, &D[6], &timer3, freq, duty);     
    }
}