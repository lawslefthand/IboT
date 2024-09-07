/*
 * lazarus_header.h
 *
 *  Created on: Sep 5, 2024
 *      Author: danba
 */

#ifndef SRC_LAZARUS_HEADER_H_
#define SRC_LAZARUS_HEADER_H_

void gpioa_input_config(void);
void clk_en(void);
void gpiob_output_config(void);
void pwm_config(void);
void pwm_en(void);
void full_speed(void);
void half_speed(void);
void stop(void);
void full_speed_left(void);
void full_speed_right(void);
void half_speed_left(void);
void half_speed_right(void);
void stop_right(void);
void stop_left(void);



#endif /* SRC_LAZARUS_HEADER_H_ */
