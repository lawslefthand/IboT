#include <stdint.h>
#include "stm32f030x8.h"
#include "usart.h"
#include <stdio.h>
#include "lazarus_header.h"

int main()
{
    // Initialize clock, GPIOs, and USART
    clk_en();
    gpioa_input_config();
    gpiob_output_config();
    usart_init();
    usart_gpio_init();
    usart_init();

    while(1)
    {
    	delay_1_sec();

      
        printf("PA0 (Center): %d, PA1 (Front Center): %d, PA7 (Left): %d, PA5 (Left): %d, PA10 (Right): %d, PA6 (Right): %d\n",
                !(GPIOA->IDR & (1 << 0)), !(GPIOA->IDR & (1 << 1)), !(GPIOA->IDR & (1 << 7)),
                !(GPIOA->IDR & (1 << 5)), !(GPIOA->IDR & (1 << 10)), !(GPIOA->IDR & (1 << 6)));

        // Left T-junction detected
        if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (!(GPIOA->IDR & (1 << 7)) || !(GPIOA->IDR & (1 << 5))) && (GPIOA->IDR & (1 << 10)))
        {
            printf("Left T-junction detected\n");
            while (!(GPIOA->IDR & (1 << 10)))
            {
                full_speed_right();
                stop_left();
            }
        }

        // Right T-junction detected
        else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 7)) && (!(GPIOA->IDR & (1 << 10)) || !(GPIOA->IDR & (1 << 6))))
        {
            printf("Right T-junction detected\n");
            while (!(GPIOA->IDR & (1 << 7)))
            {
                full_speed_left();
                stop_right();
            }
        }

        // Straight T-junction detected
        else if (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (!(GPIOA->IDR & (1 << 7))) && !(GPIOA->IDR & (1 << 10)))
        {
            static int x = 0;
            x++;
            printf("Straight T-junction detected, count: %d\n", x);
            if ((x == 0) || (x == 1))
            {
                full_speed();
            }
            else if ((x == 2) || (x == 3))
            {
                while (!(GPIOA->IDR & (1 << 10)))
                {
                    full_speed_right();
                    stop_left();
                }
            }
        }

        // Turning right
        else if (((GPIOA->IDR & (1 << 7)) || (GPIOA->IDR & (1 << 5))) && (!(GPIOA->IDR & (1 << 10)) || !(GPIOA->IDR & (1 << 6))))
        {
            printf("Turning right\n");
            full_speed_left();
            stop_right();
        }

        // Turning left
        else if ((!(GPIOA->IDR & (1 << 7)) || !(GPIOA->IDR & (1 << 5)))  && ((GPIOA->IDR & (1 << 10)) || (GPIOA->IDR & (1 << 6))))
        {
            printf("Turning left\n");
            full_speed_right();
            stop_left();
        }

        // Partial straight
        else if (!(GPIOA->IDR & (1 << 0)) || !(GPIOA->IDR & (1 << 1)))
        {
            printf("Partial straight detected\n");
            full_speed();
        }

        // Full straight
        else if  (!(GPIOA->IDR & (1 << 0)) && !(GPIOA->IDR & (1 << 1)) && (GPIOA->IDR & (1 << 7)) && (GPIOA->IDR & (1 << 10)))
        {
            printf("Going straight\n");
            full_speed();
        }
        else
        {
            printf("No line detected, stopping\n");
            stop();
            stop_right();
            stop_left();
        }
    }
}
