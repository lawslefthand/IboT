#include <stdint.h>
#include "stm32f030x8.h"
#include "usart.h"
#include <stdio.h>
#include "lazarus_header.h"

int main()
{

    clk_en();
    gpioa_input_config();
    alt_gpiob_output_config();
    usart_init();
    usart_gpio_init();
    pwm_config();

    while(1)
    {
        if(!(GPIOA->IDR & (1 << 7)) && !(GPIOA->IDR & (1 << 5))  && (GPIOA->IDR & (1 << 10)) && (GPIOA->IDR & (1 << 6)))
    	{
        	 while (!(GPIOA->IDR & (1 << 7)))
        	    {
        	        turn_right();
        	    }
    	}
    	else if(!(GPIOA->IDR & (1 << 10)) && !(GPIOA->IDR & (1 << 6))  && (GPIOA->IDR & (1 << 7)) && (GPIOA->IDR & (1 << 5)))
    	{
    		 while (!(GPIOA->IDR & (1 << 10))) 
    		    {
    		        turn_left();
    		    }
    	}
        else if(!(GPIOA->IDR & (1 << 7))  && (GPIOA->IDR & (1 << 10)))
    	{
    	 turn_right();
    	}
        else if(!(GPIOA->IDR & (1 << 10)) && (GPIOA->IDR & (1 << 7)))
    	{
    	  turn_left();
    	}
        else
        {
          full_speed();
        }

     }
}
