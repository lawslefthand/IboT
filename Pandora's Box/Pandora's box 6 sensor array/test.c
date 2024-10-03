
#include "stm32f0xx_hal.h"
#include <stdio.h>
#include "usart.h"
#include "lazarus_header.h"



// Main loop
int main(void) {
    // HAL initialization

	    clk_en();
	    gpioa_input_config();
	    alt_gpiob_output_config();
	    usart_init();
	    usart_gpio_init();
	    usart_init();
	    pwm_config();

    // GPIOA initialization code here (input for sensors, output for motors)

    while (1) {

    	        int duty=50;
    	        while(duty<100)
    	        {
    	        	 TIM3->CCR3 = duty;
    	        	 TIM3->CCR4 = duty;
    	        	 full_speed_left();
    	        	 full_speed_right();
    	        	 duty++;
    	        	 delay_1_sec();
    	        }
    	        while(duty>50)
    	        {
    	           	 TIM3->CCR3 = duty;
    	           	 TIM3->CCR4 = duty;
    	           	full_speed_left();
    	           	full_speed_right();
    	           	 duty--;
    	           	 delay_1_sec();
    	        }
    	        while(duty<100)
    	        {
    	          	        	 TIM3->CCR3 = duty;
    	          	        	 TIM3->CCR4 = duty;
    	          	        	 reverse_left();
    	          	        	 reverse_right();
    	          	        	 duty++;
    	          	        	 delay_1_sec();
    	        }
    	          	        while(duty>50)
    	          	        {
    	          	           	 TIM3->CCR3 = duty;
    	          	           	 TIM3->CCR4 = duty;
    	          	           	reverse_left();
    	          	           	reverse_right();
    	          	           	 duty--;
    	          	           	 delay_1_sec();
    	          	        }






              }
}
