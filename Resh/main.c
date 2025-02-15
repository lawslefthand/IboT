#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
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

#define TXD_PIN 17
#define RXD_PIN 16
#define BUF_SIZE 1024
    
static const char* TAG = "UART";



void control_task(void *arg)
{
   
		 uint8_t data[BUF_SIZE];
    while (1)
    {
        int len = uart_read_bytes(UART_NUM_1, data, BUF_SIZE, 100 / portTICK_PERIOD_MS);
        if (len > 0)
        {
            data[len] = '\0'; // Null-terminate string
            ESP_LOGI(TAG, "Received: %s", data);
           // uart_write_bytes(UART_NUM_1, (const char *)data, len); // Echo back
        }
        vTaskDelay(pdMS_TO_TICKS(10));
      
        if(data[0] == 'F')  // left forward
        {
            gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 1);
            gpio_set_level(IN2, 0);
            printf("left motor moving forwards\n");
             ESP_LOGI(TAG,"Left motor going forwards\n");
            
        }
        else if (data[0] == 'B')
        {
			gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 1);
           printf("left motor moving backwardss");
           ESP_LOGI(TAG,"Left motor going backwards\n");
            
		}
        else if(data[0]== 'T')  
        {
            gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 1);
            gpio_set_level(IN4, 0);
            printf("Right motor going forward\n");
            ESP_LOGI(TAG,"Right motor going forward\n");
        }
        else if (data[0] == 'X')
        {
			gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 1);
            printf("Right motor going backwards\n");
            ESP_LOGI(TAG,"Right motor going Backwards\n");
            
         }
         else if (data[0] == 'A')
         {
			    gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 1);
            gpio_set_level(IN2, 0);
            printf("left motor moving forwards\n");
             ESP_LOGI(TAG,"Left motor going forwards\n");
              gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 1);
            gpio_set_level(IN4, 0);
            printf("Right motor going forward\n");
            ESP_LOGI(TAG,"Right motor going forward\n");
             
		 }
           
        else  // Stop
        {
            gpio_set_level(ENB, 0);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 0);
            gpio_set_level(ENA, 0);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 0);
            printf("left motor stopped\n");
           ESP_LOGI(TAG,"Left motor stopped\n");
            printf("Right motors stopped\n");
             ESP_LOGI(TAG,"Right motor stopped\n");
            
           
        }

        vTaskDelay(200/ portTICK_PERIOD_MS);
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
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_1, BUF_SIZE, 0, 0, NULL, 0);
   
    // Create tasks for left and right motor control
   xTaskCreatePinnedToCore(&control_task, "control task", 4096, NULL, 5, NULL, 1);
}
