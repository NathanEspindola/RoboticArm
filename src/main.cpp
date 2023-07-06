/*
 * PUCRS - Pontifícia Universidade Católica do Rio Grande do Sul
 * Escola Politécnica
 * Engenharia da Computação
 * Trabalho de Conclusão de Curso
 * Aluno Nathan Espindola
 * Orientador Professor Mestre Julio Cesar Marques de Lima
 * Avaliador Professor Mestre Marlon Leandro Moraes
 */

// P I N   M A N A G E R

// BUTTONS
// 00 - Up Button
// 35

// LEFT SIDE
// 12 - Servo1 | GARRA
// 13 - Servo2 | Elevação da Garra
// 15 - Servo3 | Rotação da Garra
// 2
// 17
// 22
// 21

// RIGHT SIDE
// 27 - Servo4 | Elevação Antebraço
// 26 - Servo5 | Elevação Braço
// 25 - Servo6 | Base Rotativa
// 33
// 32
// SVN
// 38
// 37
// SVP

#include <ESP32Servo.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <Ultrasonic.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// DISPLAY ================================================================

TFT_eSPI tft = TFT_eSPI(); 

boolean initial = 1;
byte xcolon = 0;
unsigned int colour = 0;

void displaySetup(void)
{
	tft.init();
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);
	tft.setTextColor(TFT_YELLOW, TFT_BLACK); 
}

// BUTTON ================================================================

int ButtonPin = 0;
bool ButtonState = 0;

void ButtonConfig() 
{
	pinMode(ButtonPin, INPUT_PULLUP);
}

// OPENCV ================================================================

char number[50];
char c;
int state = 0;
String myStringRec;
int stringCounter = 0;
bool stringCounterStart = false;
String myRevivedString;
int stringLength = 6;
int servoPinky,servoMiddle,servoIndex,servoThumb,servoRing;
int myVals[] = {0, 0, 0, 0, 0};

void receiveData() 
{
	int i = 0;
	while (Serial.available()) 
	{
		char c = Serial.read();
  
    	if (c == '$') 
		{
      		stringCounterStart = true;
    	}

    	if (stringCounterStart == true )
    	{
      	
			if (stringCounter < stringLength)
      		{
        		myRevivedString = String(myRevivedString + c);
        		stringCounter++;
      		}

      		if (stringCounter >= stringLength) 
	  		{
				stringCounter = 0; stringCounterStart = false;
				servoThumb = myRevivedString.substring(1, 2).toInt();
				servoIndex = myRevivedString.substring(2, 3).toInt();
				servoMiddle = myRevivedString.substring(3, 4).toInt();
				servoRing = myRevivedString.substring(4, 5).toInt();
				servoPinky = myRevivedString.substring(5, 6).toInt();    
				myRevivedString = "";
      		}	
    	}
	}
}

// SERVO ================================================================

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int minUs = 500;
int maxUs = 2400;

int servo1Pin = 12;
int servo2Pin = 13;
int servo3Pin = 15;
int servo4Pin = 27;
int servo5Pin = 26;
int servo6Pin = 25;

ESP32PWM pwm;

//void vInitHW(void);

void vInitHW(void)
{
	Serial.begin(115200);

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	servo1.setPeriodHertz(250);   
	servo2.setPeriodHertz(250);    
 	servo3.setPeriodHertz(250);    
	servo4.setPeriodHertz(250);    
	servo5.setPeriodHertz(250);    
	servo6.setPeriodHertz(250);    

	servo1.attach(servo1Pin, minUs, maxUs);
	servo2.attach(servo2Pin, minUs, maxUs);
	servo3.attach(servo3Pin, minUs, maxUs);
	servo4.attach(servo4Pin, minUs, maxUs);
	servo5.attach(servo5Pin, minUs, maxUs);
	servo6.attach(servo6Pin, minUs, maxUs);
}

// RTOS TASKS ================================================================

TaskHandle_t xTask1Handle, xTask2Handle, xTask3Handle, xTask4Handle;
TaskHandle_t xTask5Handle, xTask6Handle, xTask7Handle, xTask8Handle;

void vTask1(void *arg);
void vTask2(void *arg);
void vTask3(void *arg);
void vTask4(void *arg);
void vTask5(void *arg);
void vTask6(void *arg);
void vTask7(void *arg);
void vTask8(void *arg);

void loop() { 
    vTaskDelay(pdMS_TO_TICKS(3000));
}

void vTask1(void *arg) // Controle Servo 1 | Garra
{
	(void) arg;
	
	while(1)
	{
			receiveData();

		if (ButtonState == 0)
		{
			for( int pos1 = 80; pos1 >= 5; pos1-- )
			{
				servo1.write(pos1);
				delay(20);
			}
		
			for( int pos1 = 5; pos1 <= 80; pos1++ )
			{
				servo1.write(pos1);
				delay(20);
			}   
		}

		else if (ButtonState == 1)
		{
			if (servoThumb == 1)
			{  
				servo1.write(90);
				delay(20);
			}

			else
			{
				servo1.write(10);
				delay(20);
			}
		}
		      
    vTaskDelay(pdMS_TO_TICKS(100));    

	}
}

void vTask2(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{
			receiveData();

		if (ButtonState == 0)
		{
			for( int pos2 = 180; pos2 >= 80; pos2-- )
			{
				servo2.write(pos2);
				delay(20);
			}
		
			for( int pos2 = 80; pos2 <= 180; pos2++ )
			{
				servo2.write(pos2);
				delay(20);
			}
		}

		else if (ButtonState == 1)
		{
			
		if (servoIndex == 1)
		{  
			servo2.write(90);
		}  
		 
		else
		{
			servo2.write(30);
		}

		}

   	vTaskDelay(pdMS_TO_TICKS(100));    

	}
}

void vTask3(void *arg) // Controle Servo 3
{
	(void) arg;

	while(1)
	{

	receiveData();

		if (ButtonState == 0)
		{
			for( int pos3 = 0; pos3 <= 90; pos3++ )
			{
				servo3.write(pos3);
				delay(20);
			}
		
			for( int pos3 = 90; pos3 >= 0; pos3-- )
			{
				servo3.write(pos3);
				delay(20);
			}       
		}

		else if (ButtonState == 1)
		{
			servo3.write(0);
			delay(20);
		}
		
   	vTaskDelay(pdMS_TO_TICKS(100));    

	}
}

void vTask4(void *arg) // Controle Servo 4
{
	(void) arg;

	while(1)
	{

	receiveData();

		if (ButtonState == 0)
		{
			for( int pos4 = 150; pos4 >= 100; pos4-- )
			{
				servo4.write(pos4);
				delay(50);
			}
		
			for( int pos4 = 100; pos4 <= 150; pos4++ )
			{
				servo4.write(pos4);
				delay(50);
			}   
		}

		else if (ButtonState == 1)
		{
			if (servoRing == 1)
			{  
				servo4.write(90);
				delay(50);

			}   
			
			else
			{
				servo4.write(135);
				delay(50);
			}
		}

   		vTaskDelay(pdMS_TO_TICKS(100));   
	}
}

void vTask5(void *arg) // Controle Servo 5
{
	(void) arg;

	while(1)
	{
			receiveData();

		if (ButtonState == 0)
		{
			for( int pos5 = 60; pos5 <= 90; pos5++ )
			{
				servo5.write(pos5);
				delay(50);
			}
		
			for( int pos5 = 90; pos5 >= 60; pos5-- )
			{
				servo5.write(pos5);
				delay(50);
			}      
		}

		else if (ButtonState == 1)
		{
			if (servoPinky == 1)
			{  
				servo5.write(90);
				delay(80);
			}   

			else
			{
				servo5.write(65);
				delay(80);
			}
		}		

   		vTaskDelay(pdMS_TO_TICKS(100));    
	}
}

void vTask6(void *arg) // Controle Servo 6
{
	(void) arg;

	while(1)
	{

		receiveData();

		if (ButtonState == 0)
		{
			for( int pos6 = 135; pos6 >= 60; pos6-- )
			{
				servo6.write(pos6);
				delay(50);
			}
		
			for( int pos6 = 60; pos6 <= 135; pos6++ )
			{
				servo6.write(pos6);
				delay(50);
			}
		}
		
		if (ButtonState == 1)
		{
			if (servoMiddle == 1)
			{  
				servo6.write(90);
				delay(20);
			}  	
	
			else
			{
				servo6.write(130);
				delay(20);
			}
		}

   		vTaskDelay(pdMS_TO_TICKS(100));  
	}
}

void vTask7(void *arg) // Display
{
	(void) arg;

	while(1)
	{
    // IMPRIME DISTANCIA EM cm NO DISPLAY TFT ==================================
    //float updatecm;

   // if(distance != updatecm)
    //{
     // tft.setTextColor(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
     // tft.drawString("8888", 0, 75, 7); // Overwrite the text to clear it
   // }

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
	tft.setTextDatum(MC_DATUM);
	tft.setTextSize(5);

	if (ButtonState == 0)
	{
		tft.drawString("Auto", tft.width() / 2, tft.height() / 2);
	}

	else if (ButtonState == 1)
	{
		tft.drawString("Hand", tft.width() / 2, tft.height() / 2);
	}
    
    vTaskDelay(pdMS_TO_TICKS(10));     
  }
}

void vTask8(void *arg) // Button
{
	(void) arg;

	while(1)
	{	
		if(digitalRead(ButtonPin) == LOW)
		{
			ButtonState = !ButtonState;
			while (digitalRead(ButtonPin) == LOW);
			delay(100);
		}
		
		Serial.println(ButtonState);

		vTaskDelay(pdMS_TO_TICKS(100));
	}
}

// INICIALIZA ================================================================

void setup()
{
	vInitHW();
	displaySetup();
	receiveData();
	ButtonConfig();

// Endereço da Task1, Identificação da Task, Bytes Disponibilizados para Task1, Permite Enviar um Parametro para Task, Prioridade (pode ser de 1 a 5), Handler
	xTaskCreate(vTask1, "servo1", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask1Handle);
	xTaskCreate(vTask2, "servo2", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask2Handle);
	xTaskCreate(vTask3, "servo3", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask3Handle);
	xTaskCreate(vTask4, "servo4", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask4Handle);
	xTaskCreate(vTask5, "servo5", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask5Handle);
	xTaskCreate(vTask6, "servo6", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask6Handle);
	xTaskCreate(vTask7, "Display", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask7Handle);
	xTaskCreate(vTask8, "Button", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask8Handle);		
		
}