


#ifndef REGISTERS_H_
#define REGISTERS_H_
#include "types.h"
//PORTA
#define PORTA (*(volatile uint8_t*)(0x3B))
#define DDRA (*(volatile uint8_t*)(0x3A))
#define PINA (*(volatile uint8_t*)(0x39))
//PORTB
#define PORTB (*(volatile uint8_t*)(0x38))
#define DDRB (*(volatile uint8_t*)(0x37))
#define PINB (*(volatile uint8_t*)(0x36))
//PORTC
#define PORTC (*(volatile uint8_t*)(0x35))
#define DDRC (*(volatile uint8_t*)(0x34))
#define PINC (*(volatile uint8_t*)(0x33))
//PORTD
#define PORTD (*(volatile uint8_t*)(0x32))
#define DDRD (*(volatile uint8_t*)(0x31))
#define PIND (*(volatile uint8_t*)(0x30))
//timers 
#define TCCR0 (*(volatile uint8_t*)(0x53))
#define TCNT0 (*(volatile uint8_t*)(0x52))
#define TIFR (*(volatile uint8_t*)(0x58))

#endif /* REGISTERS_H_ */