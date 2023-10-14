void uart_SetBaudRate(int BaudRate);
void uart_init(int BaudRate);
void uart_transmit(unsigned char data);
void uart_transmitstring(char data[], int length);
unsigned char uart_receive(void);
int uart_receive_ready(void);