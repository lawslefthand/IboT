#include <stdint.h>
#include "stm32f030x8.h"
#include "usart.h"
#include <stdio.h>
#include "lazarus_header.h"

int main()
{
     //note to check init always before checking
  clk_en();
  gpioa_input_config();
  gpiob_output_config();
  pwm_config();
  //can also implement count based junction identification
  //first test with 4 central ir
  //second with 6 central ir
  while(1)
  {
	  //       1
	  //   2        3  - ir sensor placement corresponding with gpios (4 central)
	  //       0

	  //        1
	  //  5 2       3  6  - ir sensor placement corresponding with gpios (6 central) - current version
	  //        0

	  if (GPIOA->IDR == (1 << 6))  // main if super-structure for light surface (non-inverted)
	  {
         if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3))) // Going straight
         {
        	 printf("going straight\n");
        	 full_speed();
         }
         else if ((!(GPIOA->IDR & (1 << 2)) || !(GPIOA->IDR & (1 << 5))  ) && ((GPIOA->IDR & (1 << 3)) || (GPIOA->IDR & (1 << 6)))) // Turning left
		 {
        	 printf("turning left\n");
        	 full_speed_right();
        	 stop_left();
		 }
         else if (((GPIOA->IDR & (1 << 2)) || (GPIOA->IDR & (1 << 5))) && (!(GPIOA->IDR & (1 << 3)) || !(GPIOA->IDR & (1 << 6))))
         {
             printf("turning right\n");
        	 full_speed_left();
             stop_right();
         }
         else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (!(GPIOA->IDR & (1 << 2))) && !(GPIOA->IDR & (1 << 3)))
         {
        	 printf("t junction detected\n");
        	 full_speed();
         }
         else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (!(GPIOA->IDR & (1 << 2)) || !(GPIOA->IDR & (1 << 5)) ) && (GPIOA->IDR & (1 << 3)))
         {
        	 printf("left t junction detected\n");
        	 full_speed_right();
        	 stop_left();
         }
         else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && (!(GPIOA->IDR & (1 << 3)) || !(GPIOA->IDR & (1 << 6))))
        {
             printf("right t junction detected\n");
             full_speed_left();
             stop_right();
        }
         else if (!(GPIOA->IDR & (1 << 0)) || !(GPIOA->IDR & (1 << 1)))
        {
             printf("partial straight\n");
             full_speed();

       }
	  }
	  else  // else super-structure for dark surface (inverted)
	  {
		  if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && !(GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3))) // Going straight
		          {
		         	 printf("going straight inv\n");
		         	 full_speed();
		          }
		          else if ((GPIOA->IDR & (1 << 2)) && !(GPIOA->IDR & (1 << 3))) // Turning left
		 		 {
		         	 printf("turning left inv\n");
		         	 full_speed_right();
		         	 stop_left();
		 		 }
		          else if (!(GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3)))
		          {
		              printf("turning right inv\n");
		         	 full_speed_left();
		         	 stop_right();
		          }
		          else if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 2)) && (GPIOA->IDR & (1 << 3)))
		          {
		         	 printf("junction detected inv\n");
		         	 full_speed();
		          }
		          else if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && ((GPIOA->IDR & (1 << 2)) || (GPIOA->IDR & (1 << 5))) && (!(GPIOA->IDR & (1 << 3))))
		          {
		         	 printf("left t junction detected inv\n");
		         	 full_speed_right();
		         	 stop_left();
		          }
		          else if ((GPIOA->IDR & (1 << 0)) && (GPIOA->IDR & (1 << 1)) && !(GPIOA->IDR & (1 << 2)) && ((GPIOA->IDR & (1 << 3)) || (GPIOA->IDR & (1 << 6))))
		         {
		              printf("right t junction detected inv\n");
		              full_speed_left();
		              stop_right();
		         }
		          else if ((GPIOA->IDR & (1 << 0)) || (GPIOA->IDR & (1 << 1)))
		         {
		                    printf("partial straight inv\n");
		                    full_speed();
                 }

	  }
  }


}





