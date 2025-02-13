#include <stdio.h>
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

QueueHandle_t xQueue;

char uart_read()
{
	    // Configure a temporary buffer for the incoming data                                                                                                                
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        char data=[8];
        data = uart_read_bytes(ECHO_UART_PORT_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        
        return data;
    }
}
}


void control_task_left(void *arg)
{
    while(1)
    {
      
      data_left=[8];
      
      data_left=uart_read();

        ESP_LOGI(TAG, "Left Forward GPIO[%d]: %d, Left Backward GPIO[%d]: %d", go_left_forward, gpio_18, go_left_backward, gpio_35);

        if()  // left forward
        {
            gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 1);
            gpio_set_level(IN2, 0);
            ESP_LOGI(TAG, "Left motor moving forward");
        }
        else if ()
        {
			gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 1);
            ESP_LOGI(TAG, "Left motor moving backwards");
		}
        else  // Stop
        {
            gpio_set_level(ENA, 0);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 0);
            ESP_LOGI(TAG, "Left motor stopped");
        }

        vTaskDelay(200/ portTICK_PERIOD_MS);
    }
}

void control_task_right(void *arg)
{
    while(1)
    {
       
        int gpio_19 = gpio_get_level(go_right_forward);
        int gpio_39 = gpio_get_level(go_right_backward);

        ESP_LOGI(TAG, "Right Forward GPIO[%d]: %d, Right Backward GPIO[%d]: %d", go_right_forward, gpio_19, go_right_backward, gpio_39);
  
         data_left=[8];
      
         data_left=uart_read();

        if()  // right forward
        {
            gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 1);
            gpio_set_level(IN4, 0);
            ESP_LOGI(TAG, "Right motor moving forward");
        }
        else if ()
        {
			gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 1);
            ESP_LOGI(TAG, "Right motor moving backward");
		}
        else  // Stop
        {
            gpio_set_level(ENB, 0);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 0);
            ESP_LOGI(TAG, "Right motor stopped");
        }

        vTaskDelay(2-0 / portTICK_PERIOD_MS);
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
    
      * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;
    
     ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));



    
    ESP_LOGI(TAG, "GPIOs configured for motor control");

     xQueue = xQueueCreate(5, sizeof(char));
    // Create tasks for left and right motor control
    xTaskCreatePinnedToCore(&control_task_left, "control task left", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&control_task_right, "control task right", 4096, NULL, 5, NULL, 1);
}
