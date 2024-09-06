#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/idf_additions.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "soc/gpio_num.h"

//

#define go_left_forward
#define go_left_backward
#define go_right_forward
#define go_right_backward

//yet to be defined

#define ENA   
#define IN1  
#define IN2  

#define ENB   
#define IN3
#define IN4  


void control_task_left(void *arg)
{
	//gpio value holders
 
   
    
	if() //left forward
	{
	   
	   
	}
	else if() //;eft backward
    {
		
	}

}

void control_task_right(void *arg)
{
	//gpio value holders
 
   
    
	if() //right forward
	{
	   
	   
	}
	else if() //right backward
    {
		
	}

}



void app_main(void)
{
	//gpio config start
	//gpio config
	gpio_set_direction(35, GPIO_MODE_INPUT);
    gpio_set_direction(36, GPIO_MODE_INPUT);
    gpio_set_direction(39, GPIO_MODE_INPUT);
    gpio_set_direction(35, GPIO_MODE_INPUT);
    
   
    //output gpio config
    gpio_config_t io_conf;
    io_conf.intr_type= GPIO_INTR_DISABLE;
    io_conf.mode=GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask =  (1ULL << GPIO_NUM_25) | (1ULL << GPIO_NUM_26) | (1ULL << GPIO_NUM_27) | (1ULL << GPIO_NUM_32); //more to be defined
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);
    
   
    
    xTaskCreatePinnedToCore(&control_task_left,"control task left" , 4092, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&control_task_right,"control task right" , 4092, NULL, 5, NULL, 0);
  

}
