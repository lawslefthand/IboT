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

//

#define go_left_forward      34
#define go_left_backward     35
#define go_right_forward     36
#define go_right_backward    39

//yet to be defined

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
	//gpio value holders
     
    int gpio_35 = gpio_get_level(35);
    int gpio_34 = gpio_get_level(34);
        
   
    
	if(gpio_34 == 1) //left forward
	{
	   gpio_set_level(ENA,1);
	   gpio_set_level(IN1,1);
	   gpio_set_level(IN2,0);
	   
	   
	}
	else if(gpio_35 == 1) //left backward
    {
	   gpio_set_level(ENA,1);
	   gpio_set_level(IN1,0);
	   gpio_set_level(IN2,1);
	  
	}
	else
	{
	   gpio_set_level(ENA,0);
	   gpio_set_level(IN1,0);
	   gpio_set_level(IN2,0);
	}
	
	vTaskDelay(25/portTICK_PERIOD_MS);

 }
}

void control_task_right(void *arg)
{
	//gpio value holders
 while(1)
 {
     int gpio_36 = gpio_get_level(36);
     int gpio_39 = gpio_get_level(39);
      
    
	if(gpio_36 == 1 ) //right forward
	{
	   gpio_set_level(ENB,1);
	   gpio_set_level(IN3,1);
	   gpio_set_level(IN4,0);
	   
	}
	else if(gpio_39 == 1) //right backward
    {
	    gpio_set_level(ENB,1);
	    gpio_set_level(IN3,0);
	    gpio_set_level(IN4,1);
	}
	else 
	{
		gpio_set_level(ENB,0);
	    gpio_set_level(IN3,0);
	    gpio_set_level(IN4,0);
	}
	
	vTaskDelay(25/portTICK_PERIOD_MS);

}
}
   



void app_main(void)
{
	//gpio config start
	//gpio config
	gpio_set_direction(35, GPIO_MODE_INPUT);
    gpio_set_direction(36, GPIO_MODE_INPUT);
    gpio_set_direction(39, GPIO_MODE_INPUT);
    gpio_set_direction(34, GPIO_MODE_INPUT);
    
   
    //output gpio config
    gpio_config_t io_conf;
    io_conf.intr_type= GPIO_INTR_DISABLE;
    io_conf.mode=GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask =  (1ULL << GPIO_NUM_32) | (1ULL << GPIO_NUM_33) | (1ULL << GPIO_NUM_25) | (1ULL << GPIO_NUM_26) | (1ULL << GPIO_NUM_27) | (1ULL << GPIO_NUM_14); //more to be defined
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);
    
   
    
    xTaskCreatePinnedToCore(&control_task_left,"control task left" , 4092, NULL, 5, NULL, 0);
    xTaskCreatePinnedToCore(&control_task_right,"control task right" , 4092, NULL, 5, NULL, 1);
  

}
