/*
 * PUCRS - Pontifícia Universidade Católica do Rio Grande do Sul
 * Escola Politécnica
 * Engenharia da Computação
 * Trabalho de Conclusão de Curso
 * Aluno Nathan Espindola
 * Orientador Professor Mestre Julio Cesar Marques de Lima
 */

// P I N   M A N A G E R
// 12 - Servo1
// 13 - Servo2
// 15 - Servo3
// 2
// 17
// 22 - Ultrasonic Trig
// 21 - Ultrasonic Echo
// 27 - Servo4
// 26 - Servo5
// 25 - Servo6
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

void displaySetup(void){

	tft.init();
	tft.setRotation(0);
	tft.fillScreen(TFT_BLACK);

	tft.setTextColor(TFT_YELLOW, TFT_BLACK); 
}

// SERVO ================================================================

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int minUs1 = 500;
int maxUs1 = 2500;
int minUs2 = 500;
int maxUs2 = 2500;

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

	servo1.attach(servo1Pin, minUs1, maxUs1);
	servo2.attach(servo2Pin, minUs1, maxUs1);
	servo3.attach(servo3Pin, minUs1, maxUs1);
	servo4.attach(servo4Pin, minUs2, maxUs2);
	servo5.attach(servo5Pin, minUs2, maxUs2);
	servo6.attach(servo6Pin, minUs2, maxUs2);

}

// ULTRASONIC ================================================================

const int echoPin = 21;
const int trigPin = 22;

#define SOUND_SPEED 0.034

long duration;
float distance;

void ultrasonicSetup(void)
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

// RTOS TASKS ================================================================

TaskHandle_t xTask1Handle,xTask2Handle, xTask3Handle, xTask4Handle;
TaskHandle_t xTask5Handle,xTask6Handle, xTask7Handle, xTask8Handle;
//TaskHandle_t xTask9Handle; //,xTask6Handle, xTask7Handle, xTask8Handle;


void vTask1(void *arg);
void vTask2(void *arg);
void vTask3(void *arg);
void vTask4(void *arg);
void vTask5(void *arg);
void vTask6(void *arg);
void vTask7(void *arg);
void vTask8(void *arg);
//void vTask9(void *arg);


void loop() { 
    vTaskDelay(pdMS_TO_TICKS(3000));
}

void vTask1(void *arg) // Controle Servo 1
{
	(void) arg;
	
	while(1)
	{

    if (distance <= 10)
      {
        servo1.write(45);
        delay(20);             
      }

    if (distance > 10) 
      {
        servo1.write(90);
        delay(20);
      }		

    vTaskDelay(pdMS_TO_TICKS(100));    

	}
}

void vTask2(void *arg) // Controle Servo 2
{
	(void) arg;

	while(1)
	{
		if (distance <= 10)
      	{
        	servo2.write(45);
        	delay(20);           
      	}

    	if (distance > 10) 
      	{
        	servo2.write(90);
        	delay(20);
      	}	

   	vTaskDelay(pdMS_TO_TICKS(100));    

	}
}

void vTask3(void *arg) // Controle Servo 3
{
	(void) arg;

	while(1)
	{

      if (distance <= 10)
      {
        servo3.write(45);
        delay(20);          
      }

      if (distance > 10) 
      {
        servo3.write(90);
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
		if (distance <= 10)
      {
        servo4.write(90);
        delay(20);      
      }

      if (distance > 10) 
      {
        servo4.write(135);
        delay(20);
      }	

   	vTaskDelay(pdMS_TO_TICKS(100));   

	}
}

void vTask5(void *arg) // Controle Servo 5
{
	(void) arg;

	while(1)
	{
      if (distance <= 10)
      {
        servo5.write(45);
        delay(20);    
      }

      if (distance > 10) 
      {
        servo5.write(90);
        delay(20);
      }	

   	vTaskDelay(pdMS_TO_TICKS(100));    

	}
}

void vTask6(void *arg) // Controle Servo 6
{
	(void) arg;

	while(1)
	{
		      if (distance <= 10)
      {
        servo6.write(135);
        delay(20);            
      }

      if (distance > 10) 
      {
        servo6.write(90);
        delay(20);
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
    float updatecm;

    if(distance != updatecm)
    {
      tft.setTextColor(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
      tft.drawString("8888", 0, 75, 7); // Overwrite the text to clear it
    }

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.drawNumber(distance, 0, 75, 7);
    updatecm = distance;

    vTaskDelay(pdMS_TO_TICKS(10));     
  }
}

void vTask8(void *arg) // Ultrasonic
{
	(void) arg;

	while(1)
	{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance
    float distanceCm = duration * SOUND_SPEED/2;

    distance = distanceCm;

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

   	vTaskDelay(pdMS_TO_TICKS(100));   
	}
}

// INICIALIZA ================================================================

void setup()
{
	vInitHW();
	displaySetup();
	ultrasonicSetup();

	// Endereço da Task1, Identificação da Task, Bytes Disponibilizados para Task1, Permite Enviar um Parametro para Task, Prioridade (pode ser de 1 a 5), Handler
	xTaskCreate(vTask1, "servo1", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask1Handle);
	xTaskCreate(vTask2, "servo2", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask2Handle);
    xTaskCreate(vTask3, "servo3", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask3Handle);
	xTaskCreate(vTask4, "servo4", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask4Handle);
	xTaskCreate(vTask5, "servo5", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask5Handle);
	xTaskCreate(vTask6, "servo6", configMINIMAL_STACK_SIZE + 1048, NULL, 3, &xTask6Handle);
	xTaskCreate(vTask7, "Display", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask7Handle);
  	xTaskCreate(vTask8, "Ultrasonic", configMINIMAL_STACK_SIZE + 1048, NULL, 2, &xTask8Handle);
  //xTaskCreate(vTask9, "MQTT", configMINIMAL_STACK_SIZE + 1048, NULL, 1, &xTask9Handle);
}