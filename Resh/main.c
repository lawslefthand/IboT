\#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/idf_additions.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "portmacro.h"
#include "soc/gpio_num.h"
#include "esp_log.h" 
#include "driver/uart.h"

#define ENA   32
#define IN1   33
#define IN2   25

#define ENB   26
#define IN3   27
#define IN4   14
    

#define BUF_SIZE (1024)

QueueHandle_t xQueue;

char uart_read()
{
	   

    while (1) {
        // Read data from the UART
       
        char data;
        uart_read_bytes(0, &data, (BUF_SIZE)-1,  20 / portTICK_PERIOD_MS);
        
        return data; 
    }
}



void control_task_left(void *arg)
{
    while(1)
    {
      
      char data_left;
      
      data_left=uart_read();

       
        if(data_left == 'L')  // left forward
        {
            gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 1);
            gpio_set_level(IN2, 0);
            printf("left motor moving forwards");
        }
        else if (data_left == 'B')
        {
			gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 1);
           printf("left motor moving backwardss");
		}
        else  // Stop
        {
            gpio_set_level(ENA, 0);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 0);
            printf("left motor stopped");
        }

        vTaskDelay(200/ portTICK_PERIOD_MS);
    }
}

void control_task_right(void *arg)
{
    while(1)
    {
       
         char data_right=0;
      
         data_right=uart_read();

        if(data_right == 'R')  // right forward
        {
            gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 1);
            gpio_set_level(IN4, 0);
            printf("Right motor going forward");
        }
        else if (data_right == 'B')
        {
			gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 1);
            printf("Right motor going backwards");
         }
           
        else  // Stop
        {
            gpio_set_level(ENB, 0);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 0);
            printf("Both motors stopped");
           
        }

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
   


    gpio_config_t output_conf;
    output_conf.intr_type = GPIO_INTR_DISABLE;
    output_conf.mode = GPIO_MODE_OUTPUT;
    output_conf.pin_bit_mask = (1ULL << ENA) | (1ULL << IN1) | (1ULL << IN2) |
                               (1ULL << ENB) | (1ULL << IN3) | (1ULL << IN4);
    output_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    output_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&output_conf);
    
      
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;
    
   uart_driver_install(0, BUF_SIZE*2, 0, 0, NULL, intr_alloc_flags);
   uart_param_config(0, &uart_config);
   uart_set_pin(0, 1, 3, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
   
    // Create tasks for left and right motor control
    xTaskCreatePinnedToCore(&control_task_left, "control task left", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&control_task_right, "control task right", 4096, NULL, 5, NULL, 1);
}
