/*
 * task_handler.c
 *
 *  Created on: Apr 30, 2026
 *      Author: ADMIN
 */

#include "main.h"

void process_cmd(command_t *cmd);
int extract_cmd(command_t *cmd);
state_t state_of_command;
const char *msg_inv = "////Invalid option////\n";


void cmd_handle_task(void * parameter)
{
	BaseType_t state_of_cmd_noti;
	command_t cmd;

	while(1)
	{
		state_of_cmd_noti = xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		if(state_of_cmd_noti ==pdTRUE)
		{
			process_cmd(&cmd);
		}
	}

}

// from state of command to notify proper task
void process_cmd(command_t *cmd)
{

	extract_cmd(cmd);
	switch (state_of_command) {
		case sMainMenu:
			xTaskNotify(menu_handler,(uint32_t)cmd,eSetValueWithOverwrite);
			break;
		case sLedEffect:
			xTaskNotify(led_handler,(uint32_t)cmd,eSetValueWithOverwrite);
			break;
		default:
			break;
	}


}

//extract command from queue to command_t cmd
int extract_cmd(command_t *cmd)
{
	uint8_t status_of_queue = uxQueueMessagesWaiting(q_data);
	if (!status_of_queue) return -1;

	uint8_t item;// item receive data from queue
	uint8_t i=0;// count length of queue ( command )

	do
	{
		status_of_queue = xQueueReceive(q_data, &item, 0);
		if(status_of_queue ==pdPASS)
		{
			cmd->payload[i++]= item;
		}

	}while(item != '\r');

	cmd->length = i-1;
	cmd->payload[i-1]='\0';

	return 0;
}

void led_handle_task(void * parameter)
{
	const char *msg_led = "========================\r\n"
			  "|      LED Effect     |\r\n"
			  "========================\r\n"
			  "(none,e1,e2,e3,e4)\r\n"
			  "Enter your choice here : ";
	command_t *cmd;
	uint32_t cmd_address;
	char *p;

	while(1)
	{
		// wait to notify led menu
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

		//send qprint led msg
		xQueueSend(q_print,&msg_led,portMAX_DELAY);

		//wait command for led task
		xTaskNotifyWait(0,0,&cmd_address,portMAX_DELAY);

		cmd = (command_t *)cmd_address;

		p= (char *)cmd->payload;

		//handle led command
		if(cmd->length <=4)
		{
			if(! strcmp (p,"none") )
			{
				led_effect_stop();

			}else if(! strcmp (p,"e1") )
			{
				led_effect(1);

			}else if(! strcmp (p,"e2") )
			{
				led_effect(2);

			}else if(! strcmp (p,"e3") )
			{
				led_effect(3);

			}else if(! strcmp (p,"e4") )
			{
				led_effect(4);

			}else{

				xQueueSend(q_print,&msg_inv,portMAX_DELAY);

			}

		}else {

			xQueueSend(q_print,&msg_inv,portMAX_DELAY);

		}


		state_of_command = sMainMenu;

		xTaskNotify(menu_handler,0,eNoAction);

	}// end super loop


}

void menu_handle_task(void * parameter)
{
	const char *msg_menu = "\r\n========================\r\n"
	                       "|         Menu         |\r\n"
	                       "========================\r\n"
	                       "LED effect    ----> 0\r\n"
	                       "Date and time ----> 1\r\n"
	                       "Exit          ----> 2\r\n"
	                       "Enter your choice here : ";

	uint32_t cmd_address;
	command_t *cmd;
	int option;

	while(1)
	{
		//send message to print task
		// queue need address of variable
		//( in this case variable is address of pointer)
		xQueueSend(q_print,&msg_menu,portMAX_DELAY);

		//wait command address from cmd task
		xTaskNotifyWait(0,0,&cmd_address,portMAX_DELAY);

		cmd =(command_t *) cmd_address;

		if(cmd->length ==1)
		{
			option = cmd->payload[0]-48;

			switch (option) {
				case 0:
					state_of_command = sLedEffect;
					xTaskNotify(led_handler,0,eNoAction);
					break;
				case 2:
					break;
				default:
					xQueueSend(q_print,&msg_inv,portMAX_DELAY);
					continue;
			}
		}else {

			xQueueSend(q_print,&msg_inv,portMAX_DELAY);
			continue;

		}

		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

	}//end super loop


}

void print_handle_task(void * parameter)
{
	uint32_t *msg;

	while(1)
	{
		// receive address of message
		xQueueReceive(q_print, &msg, portMAX_DELAY);

		//send message to terminal by uart
		HAL_UART_Transmit(&huart2,(uint8_t *) msg, strlen((char *)msg), HAL_MAX_DELAY);
	}


}



