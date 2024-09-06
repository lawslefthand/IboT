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

	   GPIOA->MODER  &=~ (1<<6); //PA3
	   GPIOA->MODER  &=~ (1<<7);

	   GPIOA->MODER  &=~ (1<<8); //PA4
	   GPIOA->MODER  &=~ (1<<9);

	   GPIOA->MODER  &=~ (1<<10); //PA5
	   GPIOA->MODER  &=~ (1<<11);

	   GPIOA->MODER  &=~ (1<<12); //PA6
	   GPIOA->MODER  &=~ (1<<13);
}

void gpiob_output_config(void)
{

	   GPIOA->MODER  &=~(1<<8);
	   GPIOA->MODER  |= (1<<9);
	   //
	   GPIOA->MODER  &=~(1<<10);
	   GPIOA->MODER  |= (1<<11);

}

void gpio_pupdr_config(void)
{

	//Pull down enabled for all
	   GPIOA->PUPDR  &=~ (1<<0); //PA0
	   GPIOA->PUPDR  |= (1<<1);

	   GPIOA->PUPDR  &=~ (1<<2); //PA1
	   GPIOA->PUPDR  |= (1<<3);

	   GPIOA->PUPDR  &=~ (1<<4); //PA2
	   GPIOA->PUPDR  |= (1<<5);

	   GPIOA->PUPDR  &=~ (1<<6); //PA3
	   GPIOA->PUPDR  |= (1<<7);

	   GPIOA->PUPDR  &=~ (1<<8); //PA4
	   GPIOA->PUPDR  |= (1<<9);

	   GPIOA->PUPDR  &=~ (1<<10); //PA5
	   GPIOA->PUPDR  |= (1<<11);

	   GPIOA->PUPDR  &=~ (1<<12); //PA6
	   GPIOA->PUPDR  |= (1<<13);
}

void pwm_config(void)
{
   //PSC AND ARR VALUES
   TIM3->PSC = 	7;
   TIM3->ARR =  49;
   //CCMR RESET
   TIM3->CCMR1 = 0;
   //channel 1
   TIM3->CCMR1 &=~ (1<<4);
   TIM3->CCMR1 |= (1<<5);
   TIM3->CCMR1 |= (1<<6);
   TIM3->CCMR1 |=  (1<<3);
  //channel  2
   TIM3->CCMR1 &=~ (1<<12);
   TIM3->CCMR1 |= (1<<13);
   TIM3->CCMR1 |= (1<<14);
   TIM3->CCMR1 |=  (1<<15);

   TIM3->CCER  = 0;
   //CH1
   TIM3->CCER  |= (1<<0);
   //CH2
   TIM3->CCER |=  (1<<4);
   //CR RESET
   TIM3->CR1   = 0;



}

void pwm_en(void)
{

    TIM3->CR1 |= (1<<7);
	TIM3->CR1 |= (1<<0);

}

void full_speed(void)
{
	TIM3->CCR1 = 49;
	TIM3->CCR2 = 49;

}

void full_speed_left(void)
{
	TIM3->CCR1 = 49;

}
void full_speed_right(void)
{

	TIM3->CCR2 = 49;
}

void half_speed_left(void)
{
	TIM3->CCR1 = 25;
}

void half_speed_right(void)
{
	TIM3->CCR2 = 25;
}

void stop_left(void)
{
	TIM3->CCR1 = 0;

}

void stop_right(void)
{
	TIM3->CCR2 = 0;
}

void stop(void)
{
	TIM3->CCR1 = 0;
	TIM3->CCR2 = 0;
}



