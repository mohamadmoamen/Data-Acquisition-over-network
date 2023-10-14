#include <stdio.h>
#include <util/delay.h>

void DIO_init(){
  DIO_SetPinDirection('d',4,'i');

  DIO_SetPinDirection('d',5,'o');
}

void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction){
  if(port == 'd' & pin <= 7 & pin >= 0){
    if (direction == 'o'){
      DDRD |= (1<<pin);
    }else if(direction == 'i'){
      DDRD &= ~(1<<pin);
    }
  }
}

void DIO_SetPinState(unsigned char port, int pin, unsigned char state){
  if(port == 'd' & pin <= 7 & pin >= 0){
    if(state == 'h'){
      PORTD |= (1<<pin);
    }else if(state == 'l'){
      PORTD &= ~(1<<pin);
    }
  }
}