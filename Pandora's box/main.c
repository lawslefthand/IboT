#include <stdint.h>
#include "stm32f030x8.h"
#include "usart.h"
#include <stdio.h>
#include "lazarus_header.h"

int main()
{
  clk_en();
  gpioa_input_config();
  gpiob_output_config();
  pwm_config();
  while(1)
  {
	  //       1
	  //   2        3  - ir sensor placement corresponding with gpios
	  //       0
	  if (GPIOA->IDR == (1 << 6))  // main if superstructure for light surface (non-inverted)
	  {
         if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3))) // Going straight
         {
        	 printf("going straight\n");
        	 full_speed();
         }
         else if (!(GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3))) // Turning left
		 {
        	 printf("turning left\n");
        	 full_speed_right();
        	 half_speed_left();
		 }
         else if ((GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3)))
         {
             printf("turning right\n");
        	 full_speed_left();
        	 half_speed_right();
         }
         else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && !(GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3)))
         {
        	 printf("junction detected\n");
        	 full_speed();
         }
         else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && !(GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3)))
         {
        	 printf("left t junction detected\n");
        	 full_speed_right();
        	 half_speed_left();
         }
         else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3)))
        {
             printf("right t junction detected\n");
             full_speed_left();
             half_speed_right();
        }
	  }
	  else  // else super-structure for dark surface (inverted)
	  {
		  if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && !(GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3))) // Going straight
		          {
		         	 printf("going straight\n");
		         	 full_speed();
		          }
		          else if ((GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3))) // Turning left
		 		 {
		         	 printf("turning left\n");
		         	 full_speed_right();
		         	 half_speed_left();
		 		 }
		          else if (!(GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3)))
		          {
		              printf("turning right\n");
		         	 full_speed_left();
		         	 half_speed_right();
		          }
		          else if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3)))
		          {
		         	 printf("junction detected\n");
		         	 full_speed();
		          }
		          else if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3)))
		          {
		         	 printf("left t junction detected\n");
		         	 full_speed_right();
		         	 half_speed_left();
		          }
		          else if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && !(GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3)))
		         {
		              printf("right t junction detected\n");
		              full_speed_left();
		              half_speed_right();
		         }
	  }
  }


}





