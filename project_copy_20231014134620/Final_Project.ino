#include <avr/io.h> // Provides access to AVR microcontroller I/O registers.
#include <util/delay.h> //Allows creating delays.
#include "initial.h"//custom header files for this project.
#include "dio.h"
#include <string.h>//Provides string manipulation functions.

#define BAUD 9600 //defining the BAUD rate globally

const int PUSH_BUTTON = 4; //push button at digital pin 4
const int LED = 5; //LED at digital pin 5

int main(void){

  DIO_init();//to initialize Digital Input/Output.

  char received_word[8];
  int count = 0;

  uart_init(BAUD); 

  while(1){ //infinite loop
    
     if((UCSR0A)&(1<<RXC0)){
      char data = uart_receive();
      if(data != '\n'){
          received_word[count++] = data;
      }else{
        if( count == 6 && strncmp(received_word,"led_on",6)==0 ){//Checks if the received command is "led_on" or "led_off"
          uart_transmitstring("LED turned on\n",14);
          //PORTB |= 0b00100000; 
          DIO_SetPinState('d',5,'h');
        }
        else if( count == 7 && strncmp(received_word,"led_off",7)==0){
          uart_transmitstring("LED turned off\n",15);
          //PORTB &= 0b11011111; 
          DIO_SetPinState('d',4,'l');
        }else{
          uart_transmitstring("Incorrect command\n",18); 
        }
        count = 0; 
      }
    }

   int Button_state = ((PIND>>PIND4)&1); //put the state of the button in a variable
  //Reads the state of the push button connected to digital pin 4 
    if(Button_state == HIGH){ //check for rising edge signal of a button
      uart_transmitstring("button is pressed\n",18);//Sends a message over UART indicating whether the button is pressed or not
    }else if (Button_state == LOW){
      uart_transmitstring("button is not pressed\n",22);
    }

    _delay_ms(500);
  }
  return 0;
}