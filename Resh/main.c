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

#define TAG "Motor_Control"  // Define a tag for logging


#define go_left_forward      18  // Changed to D18
#define go_left_backward     35
#define go_right_forward     19  // Changed to D19
#define go_right_backward    39

#define ENA   32
#define IN1   33
#define IN2   25

#define ENB   26
#define IN3   27
#define IN4   14

void control_task_left(void *arg)
{
    while(1)
    {
      
        int gpio_35 = gpio_get_level(go_left_backward);
        int gpio_18 = gpio_get_level(go_left_forward);

        ESP_LOGI(TAG, "Left Forward GPIO[%d]: %d, Left Backward GPIO[%d]: %d", go_left_forward, gpio_18, go_left_backward, gpio_35);

        if(gpio_18 == 1)  // left forward
        {
            gpio_set_level(ENA, 1);
            gpio_set_level(IN1, 1);
            gpio_set_level(IN2, 0);
            ESP_LOGI(TAG, "Left motor moving forward");
        }
        else  // Stop
        {
            gpio_set_level(ENA, 0);
            gpio_set_level(IN1, 0);
            gpio_set_level(IN2, 0);
            ESP_LOGI(TAG, "Left motor stopped");
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void control_task_right(void *arg)
{
    while(1)
    {
       
        int gpio_19 = gpio_get_level(go_right_forward);
        int gpio_39 = gpio_get_level(go_right_backward);

        ESP_LOGI(TAG, "Right Forward GPIO[%d]: %d, Right Backward GPIO[%d]: %d", go_right_forward, gpio_19, go_right_backward, gpio_39);

        if(gpio_19 == 1)  // right forward
        {
            gpio_set_level(ENB, 1);
            gpio_set_level(IN3, 1);
            gpio_set_level(IN4, 0);
            ESP_LOGI(TAG, "Right motor moving forward");
        }
        else  // Stop
        {
            gpio_set_level(ENB, 0);
            gpio_set_level(IN3, 0);
            gpio_set_level(IN4, 0);
            ESP_LOGI(TAG, "Right motor stopped");
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
   
    gpio_config_t input_conf;
    input_conf.intr_type = GPIO_INTR_DISABLE;
    input_conf.mode = GPIO_MODE_INPUT;
    input_conf.pin_bit_mask = (1ULL << go_left_backward) | (1ULL << go_left_forward) |
                              (1ULL << go_right_backward) | (1ULL << go_right_forward);
    input_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    input_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&input_conf);

    gpio_config_t output_conf;
    output_conf.intr_type = GPIO_INTR_DISABLE;
    output_conf.mode = GPIO_MODE_OUTPUT;
    output_conf.pin_bit_mask = (1ULL << ENA) | (1ULL << IN1) | (1ULL << IN2) |
                               (1ULL << ENB) | (1ULL << IN3) | (1ULL << IN4);
    output_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    output_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&output_conf);
    
    ESP_LOGI(TAG, "GPIOs configured for motor control");

    // Create tasks for left and right motor control
    xTaskCreatePinnedToCore(&control_task_left, "control task left", 4096, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&control_task_right, "control task right", 4096, NULL, 5, NULL, 1);
}
