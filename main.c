#define F_CPU 16000000UL
#define USART_BAUDRATE 9600 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void Usart_init(void);
unsigned char Usart_receive(void);
void Usart_send(unsigned char value);
void send_string(char *s);
void move(a,b,c,d);
void move_fr(a,b,c,d);
void move_r(a,b,c,d);
void move_l(a,b,c,d);

unsigned char a,b,c,d;
int rd=0;
int gn=0;
int bl=0;
char send[];
int val1;
static volatile int pulse = 0;
static volatile int i = 0;
int16_t count_a = 0; 
char show_a[16];

int main(void){

	Usart_init();
	init();
	_delay_ms(5000);
	
	while(1){
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_l(120,0,0,120);//left
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_r(0,120,120,0);//right
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_r(0,120,120,0);//right
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_r(0,120,120,0);//right
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_r(0,120,120,0);//right
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_l(120,0,0,120);//left
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move_fr(0,255,0,160);//forward
		for(int i=0;i<10;i++){
			detectClr();
			obstacle();
		}
		
		move(0,0,0,0);
		
		break;
	}
}

void init(void){

	DDRC=1<<PC3|1<<PC4|1<<PC5;	
	ADCSRA =1<<ADEN|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADMUX = 1<<REFS0|1<<MUX1;
	
	DDRD=1<<PD5|1<<PD6|0<<PD2|1<<PD3;
	DDRB=1<<PB1|1<<PB2|1<<PB3|1<<PB4|1<<PB5;
	_delay_ms(50);
	
	TCCR0A=1<<COM0A1|1<<COM0B1|1<<WGM01|1<<WGM00;
	TCCR0B=1<<CS00;
	
	TCCR1A=1<<COM1A1|1<<COM1B1|1<<WGM12|1<<WGM10;
	TCCR1B=1<<CS10;

	EIMSK |= 1<<INT0;
	EICRA |= 1<<ISC00;

	sei();
	
}

void obstacle(void){

	PORTD = 1<<PD3;
    _delay_us(15);
    PORTD = 0<<PD3;
    count_a = pulse;
	sprintf(show_a,"Dist = %d\n", count_a);
	send_string(show_a);//Send msg
	if(count_a<10){
		send_string("1\n");
	}else{
		send_string("0\n");
	}
	
}

void detectClr(void){
	PORTC=1<<PC3;//red
	_delay_ms(40);
	rd = avg();
	PORTC=0<<PC3;
	_delay_ms(10);

	PORTC=1<<PC4;//green
	_delay_ms(40);
	gn =avg();
	PORTC=0<<PC4;
	_delay_ms(10);
	
	PORTC=1<<PC5;//blue
	_delay_ms(40);
	bl = avg();
	PORTC=0<<PC5;
	_delay_ms(10);
	
	compare();
}

int avg(void) {
	int sum = 0;
	val1=0;
    for(int j=1;j<=20;j++){	
		val1 = ReadADC();
		sum +=val1;
	}
    return (sum/20);
}

int compare(void){
	
	if((bl>gn)&&(rd>bl)){
		send_string("color : red\n");
		
	}
	
	if((rd>bl)&&(gn>rd)){
		send_string("color : green\n");
		
	}
	
	if((bl>rd)&&(gn>bl)){
		send_string("color : blue\n");
		
	}
}
	
int ReadADC(void){											
	ADCSRA = ADCSRA|(1<<ADSC); 
	while((ADCSRA & (1<<ADSC))==0);	
	return ADC;
}

void move(a,b,c,d){

	OCR0A = a;
	OCR0B = b;
	OCR1A = c;
	OCR1B = d;
	
	_delay_ms(1000);
	
}

void move_fr(a,b,c,d){

	OCR0A = a;
	OCR0B = b;
	OCR1A = c;
	OCR1B = d;
	
	_delay_ms(500);
	
}

void move_r(a,b,c,d){

	OCR0A = a;
	OCR0B = b;
	OCR1A = c;
	OCR1B = d;
	
	_delay_ms(7);
	
}

void move_l(a,b,c,d){

	OCR0A = a;
	OCR0B = b;
	OCR1A = c;
	OCR1B = d;
	
	_delay_ms(5);
	
}

void Usart_init(void){
	UCSR0B |= (1<<TXEN0)|(1<<RXEN0);//Enable Transmit, Receive
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);//Select UCSRC, Select transmit and receive bit-size - 8bit
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;//Set baudrate 9600
}

unsigned char Usart_receive(void){
	while(!(UCSR0A&(1<<RXC0)));//Wait for byte receive
	return(UDR0);//UDR store received msg
}

void Usart_send(unsigned char value){
	while(!(UCSR0A&(1<<UDRE0)));//Wait for UDR empty
	UDR0 = value;//Load message UDR to sent
	while(!(UCSR0A&(1<<TXC0)));//Wait for msg sent
}

void send_string(char *s){//send string
	for(unsigned char i=0; s[i]!=0; i++){
		Usart_send(s[i]);
	}
}

ISR(INT0_vect)
{
  if(i == 0)
  {
    TCCR2B |= 1<<CS20|1<<CS21|1<<CS22;
    i = 1;
  }
  else
  {
    TCCR2B = 0;
    pulse = TCNT2;
    TCNT2 = 0;
    i = 0;
  }
}