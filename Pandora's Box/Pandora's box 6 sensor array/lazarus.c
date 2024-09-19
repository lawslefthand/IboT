#include "lazarus_header.h"
#include <stdint.h>
#include "stm32f030x8.h"
#include "usart.h"
#include <stdio.h>
#include "lazarus_header.h"



void clk_en(void)
{
	//GPIO A Clk Access
	RCC->AHBENR |=  (1<<17);
	//GPIO B Clk Access
	RCC->AHBENR |=  (1<<18);
	//TIM3 Clk Access
	RCC->APB1ENR |= (1<<1);

}

void gpioa_input_config(void)
{

	   GPIOA->MODER  &=~ (1<<0); //PA0
	   GPIOA->MODER  &=~ (1<<1);

	   GPIOA->MODER  &=~ (1<<2); //PA1
	   GPIOA->MODER  &=~ (1<<3);

	   GPIOA->MODER  &=~ (1<<4); //PA2
	   GPIOA->MODER  &=~ (1<<5);

	   GPIOA->MODER  &=~ (1<<20); //PA3
	   GPIOA->MODER  &=~ (1<<21);

	   GPIOA->MODER  &=~ (1<<8); //PA4
	   GPIOA->MODER  &=~ (1<<9);

	   GPIOA->MODER  &=~ (1<<10); //PA5
	   GPIOA->MODER  &=~ (1<<11);

	   GPIOA->MODER  &=~ (1<<12); //PA6
	   GPIOA->MODER  &=~ (1<<13);

	   GPIOA->MODER  &=~ (1<<14); //PA7
	   GPIOA->MODER  &=~ (1<<15);
}

void gpiob_output_config(void)
{


	   GPIOB->MODER  |= (1<<0); //PB0  ENA
	   GPIOB->MODER  &=~ (1<<1);

	   GPIOB->MODER  |= (1<<2); //PB1  IN1
	   GPIOB->MODER  &=~ (1<<3);

	   GPIOB->MODER  |= (1<<4); //PB2  IN2
	   GPIOB->MODER  &=~ (1<<5);

	   GPIOB->MODER  |= (1<<6); //PB3  ENB
	   GPIOB->MODER  &=~ (1<<7);

	   GPIOB->MODER  |= (1<<8); //PB4  IN3
	   GPIOB->MODER  &=~ (1<<9);

	   GPIOB->MODER  |= (1<<10); //PB5 IN4
	   GPIOB->MODER  &=~ (1<<11);


}

void gpio_pupdr_config(void)
{
    // Pull-down enabled for all relevant pins
    GPIOA->PUPDR &=~ ((1 << 0) | (1 << 1));  // PA0 pull-down
    GPIOA->PUPDR |=  (1 << 1);               // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 2) | (1 << 3));  // PA1 pull-down
    GPIOA->PUPDR |=  (1 << 3);               // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 4) | (1 << 5));  // PA2 pull-down
    GPIOA->PUPDR |=  (1 << 5);               // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 20) | (1 << 21));  // PA3 pull-down
    GPIOA->PUPDR |=  (1 << 21);               // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 8) | (1 << 9));  // PA4 pull-down
    GPIOA->PUPDR |=  (1 << 9);               // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 10) | (1 << 11)); // PA5 pull-down
    GPIOA->PUPDR |=  (1 << 11);              // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 12) | (1 << 13)); // PA6 pull-down
    GPIOA->PUPDR |=  (1 << 13);              // Ensure the second bit is set

    GPIOA->PUPDR &=~ ((1 << 14) | (1 << 15)); // PA7 pull-down
    GPIOA->PUPDR |=  (1 << 15);              // Ensure the second bit is set
}




void full_speed(void)
{
	 GPIOB->BSRR |=  (1<<0);
	 GPIOB->BSRR |=  (1<<1);
	 GPIOB->BSRR &=~ (1<<2);
	 GPIOB->BSRR |=  (1<<3);
	 GPIOB->BSRR |=  (1<<4);
	 GPIOB->BSRR &=~ (1<<5);

}

void full_speed_left(void)
{
	GPIOB->BSRR |=  (1<<0);
    GPIOB->BSRR |=  (1<<1);
    GPIOB->BSRR &=~ (1<<2);

    GPIOB->BSRR |=  (1<<3);
    GPIOB->BSRR &=~  (1<<4);
    GPIOB->BSRR &=~ (1<<5);


}
void full_speed_right(void)
{
	GPIOB->BSRR |=  (1<<3);
    GPIOB->BSRR |=  (1<<4);
    GPIOB->BSRR &=~ (1<<5);

    GPIOB->BSRR  |=    (1<<0);
    GPIOB->BSRR  &=~  (1<<1);
    GPIOB->BSRR  &=~   (1<<2);

}

void reverse_left(void)
{
	    GPIOB->BSRR |=  (1<<0);
	    GPIOB->BSRR &=~  (1<<1);
	    GPIOB->BSRR |= (1<<2);


}
void reverse_right(void)
{
	  GPIOB->BSRR |=  (1<<0);
	  GPIOB->BSRR &=~  (1<<1);
	  GPIOB->BSRR |=    (1<<2);

}

void stop_left(void)
{
	    GPIOB->BSRR &=~  (1<<3);
	    GPIOB->BSRR &=~  (1<<4);
	    GPIOB->BSRR &=~ (1<<5);


}

void stop_right(void)
{
	  GPIOB->BSRR &=~  (1<<3);
      GPIOB->BSRR &=~  (1<<4);
      GPIOB->BSRR &=~ (1<<5);
}

void stop(void)
{
	        GPIOB->BSRR &=~  (1<<3);
		    GPIOB->BSRR &=~  (1<<4);
		    GPIOB->BSRR &=~ (1<<5);
		    GPIOB->BSRR &=~  (1<<3);
		    GPIOB->BSRR &=~  (1<<4);
		    GPIOB->BSRR &=~ (1<<5);

}

void delay_1_sec(void) {
    uint32_t count = 100000;

    while (count > 0) {
        count--;
    }
}




