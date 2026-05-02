/*
 * led_effect.c
 *
 *  Created on: May 1, 2026
 *      Author: ADMIN
 */


#include "main.h"


static void turn_all_led_on();
static void turn_all_led_off();
static void turn_all_odd_led_on();
static void turn_all_even_led_on();
static void led_control(int value);

void led_effect_stop(void)
{
	for(int i=0;i<4;i++)
	{
		xTimerStop(led_timer[i],portMAX_DELAY);
	}

}


void led_effect(int n)
{
	led_effect_stop();
	xTimerStart(led_timer[n-1],portMAX_DELAY);
}


void LED_effect1(void)
{
	static uint8_t flag =0;
	(flag ^= 1)? turn_all_led_on():turn_all_led_off();
}


void LED_effect2(void)
{
	static uint8_t flag =0;
	(flag ^= 1)? turn_all_odd_led_on():turn_all_even_led_on();
}


void LED_effect3(void)
{
	static int i=0;
	led_control(0x1<<(i++ %4));
}


void LED_effect4(void)
{
	static int i=0;
	led_control(0x8>>(i++ %4));

}

static void turn_all_led_on()
{
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD3_Pin, GPIO_PIN_SET);

}
static void turn_all_led_off()
{
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

}
static void turn_all_odd_led_on()
{
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD3_Pin, GPIO_PIN_SET);

}
static void turn_all_even_led_on()
{
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LD4_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

}
static void led_control(int value)
{
	for(int i=0;i<4;i++)
		HAL_GPIO_WritePin(LD4_GPIO_Port, (LD4_Pin<<i), (value>>i)&(0x1));

}
