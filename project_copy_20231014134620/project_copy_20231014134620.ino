#include <avr/io.h>

void uart_SetBaudRate(int BaudRate){
  int ubrr = ((F_CPU)/(BaudRate*16UL)-1);  
  UBRR0H = (ubrr>>8);              
  UBRR0L = ubrr;                    
}

void uart_init(int BaudRate){
  uart_SetBaudRate(BaudRate);
  UCSR0B |= (1<<TXEN0)|(1<<RXEN0); 
  UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
}

void uart_transmit(unsigned char data){
  int udr_empty;
  do{
    udr_empty = (UCSR0A & (1<<UDRE0)) != 0; 
  }while(!udr_empty);

  UDR0 = data; 
}

void uart_transmitstring(char data[], int length){
  for(int i = 0; i < length; i++){
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data[i];
  }
}

unsigned char uart_receive(void){
  if(!uart_receive_ready()){
    return;
  }else {
    return UDR0;
  } 
}

int uart_receive_ready(void){
  int flag = ((UCSR0A)&(1<<RXC0)) != 0; //checks the 7th bit of the register which means the received completed successfully
  return flag;
}