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

	   GPIOA->MODER  &=~ (1<<20); //PA10
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

	    GPIOB->MODER  |= (1<<12); // PB6 IN1
	    GPIOB->MODER  &=~ (1<<13);

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

	 GPIOB->ODR &= ~GPIO_ODR_6; // IN1 LOW
		    GPIOB->ODR |= GPIO_ODR_2;  // IN2 HIGH
		    GPIOB->ODR |= GPIO_ODR_0;  // ENA HIGH (Enable Motor A)
		    GPIOB->ODR |= GPIO_ODR_4;  // IN3 HIGH
		    	    GPIOB->ODR &= ~GPIO_ODR_5; // IN4 LOW
		    	    GPIOB->ODR |= GPIO_ODR_3;  // ENB HIGH (Enable Motor B)

}

void full_speed_left(void)
{
	 GPIOB->ODR |= GPIO_ODR_6; // IN1 high
		    GPIOB->ODR &=~ GPIO_ODR_2;  // IN2 low
		//    GPIOB->ODR |= GPIO_ODR_0;  // ENA HIGH (Enable Motor A)


}
void full_speed_right(void)
{
	GPIOB->ODR |= GPIO_ODR_4;  // IN3 HIGH
	    GPIOB->ODR &= ~GPIO_ODR_5; // IN4 LOW
	    GPIOB->ODR |= GPIO_ODR_3;  // ENB HIGH (Enable Motor B)

}

void reverse_left(void)
{
	   GPIOB->ODR &=~ GPIO_ODR_6; // IN1 low
	    GPIOB->ODR |= GPIO_ODR_2;  // IN2 high
	    GPIOB->ODR |= GPIO_ODR_0;  // ENA HIGH (Enable Motor A)

}
void reverse_right(void)
{
	GPIOB->ODR &= ~GPIO_ODR_4; // IN3 LOW
	    GPIOB->ODR |= GPIO_ODR_5;  // IN4 HIGH
	    GPIOB->ODR |= GPIO_ODR_3;  // ENB HIGH (Enable Motor B)

}

void stop_left(void)
{
	GPIOB->ODR &= ~GPIO_ODR_0 ;  // ENA and ENB LOW (disable both motors)


}

void stop_right(void)
{
	GPIOB->ODR &= ~GPIO_ODR_3;  // ENA and ENB LOW (disable both motors)
}

void stop(void)
{
	GPIOB->ODR &= ~(GPIO_ODR_0 | GPIO_ODR_3);  // ENA and ENB LOW (disable both motors)

}

void delay_1_sec(void) {
    uint32_t count = 100000;

    while (count > 0) {
        count--;
    }
}

void pwm_config(void)
{
    // Configure TIM3 for PWM
    TIM3->PSC = 19;  // Prescaler for 20 kHz PWM
    TIM3->ARR = 39;  // Auto-reload value
    TIM3->CCR3 = 0;  // Initial duty cycle (0%)

    // Configure TIM3 Channel 3 as PWM mode 1
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE; // PWM mode 1, preload enable
    TIM3->CCER |= TIM_CCER_CC3E; // Enable output on Channel 3
    TIM3->CR1 |= TIM_CR1_ARPE;   // Enable auto-reload preload
    TIM3->CR1 |= TIM_CR1_CEN;    // Enable the timer
}

void alt_gpiob_output_config(void)
{


	   GPIOB->MODER &= ~(3 << (0 * 2)); // Clear mode bits for PB0
	    GPIOB->MODER |= (2 << (0 * 2));  // Set PB0 to alternate function mode
	    GPIOB->AFR[0] &= ~(0xF << (0 * 4)); // Clear AFR for PB0
	    GPIOB->AFR[0] |= (1 << (0 * 4));    // Set PB0 to AF1 (TIM3_CH3)

	    GPIOB->MODER  |= (1<<12); // PB6 IN1
	    GPIOB->MODER  &=~ (1<<13);

	   GPIOB->MODER  |= (1<<4); //PB2  IN2
	   GPIOB->MODER  &=~ (1<<5);

	   GPIOB->MODER  |= (1<<6); //PB3  ENB
	   GPIOB->MODER  &=~ (1<<7);

	   GPIOB->MODER  |= (1<<8); //PB4  IN3
	   GPIOB->MODER  &=~ (1<<9);

	   GPIOB->MODER  |= (1<<10); //PB5 IN4
	   GPIOB->MODER  &=~ (1<<11);


}





