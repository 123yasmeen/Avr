
#include "DIO.h"
#include "../../Bit_calculations.h"
uint8_t DIO_init(uint8_t portnumber,uint8_t pinnumber,uint8_t direction)//initialize directions
{
	switch (portnumber)//using switch to decide which port will be used
	{
		case PORT_A:
		//figuring out which direction
		if(direction==IN)
		{
			CLEAR(DDRA,pinnumber);
		}
		else if(direction==OUT)
		{
			SET(DDRA,pinnumber);
		}
		else
		{
			return DIO_ERROR;//error handling
		}
		break;
		case PORT_B:
		if(direction==IN)
		{
			CLEAR(DDRB,pinnumber);
		}
		else if(direction==OUT)
		{
		   SET(DDRB,pinnumber);
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		case PORT_C:
		if(direction==IN)
		{
			CLEAR(DDRC,pinnumber);
		}
		else if(direction==OUT)
		{
			SET(DDRC,pinnumber);
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		case PORT_D:
		if(direction==IN)
		{
			CLEAR(DDRD,pinnumber);
		}
		else if(direction==OUT)
		{
			SET(DDRD,pinnumber);
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		default:
		return DIO_ERROR;
		break;
	}
	return DIO_OK;
}
uint8_t DIO_write(uint8_t portnumber,uint8_t pinnumber,uint8_t value)
{
	switch (portnumber)
	{
		case PORT_A:
		if(value==LOW)
		{
			CLEAR(PORTA,pinnumber);
		}
		else if(value==HIGH)
		{
			SET(PORTA,pinnumber);
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		case PORT_B:
		if(value==LOW)
		{
				CLEAR(PORTB,pinnumber);
		}
		else if(value==HIGH)
		{
			SET(PORTB,pinnumber);;
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		case PORT_C:
		if(value==LOW)
		{
		   CLEAR(PORTC,pinnumber);
		}
		else if(value==HIGH)
		{
			SET(PORTC,pinnumber);
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		case PORT_D:
		if(value==LOW)
		{
		  CLEAR(PORTD,pinnumber);
		}
		else if(value==HIGH)
		{
			SET(PORTD,pinnumber);
		}
		else
		{
			return DIO_ERROR;
		}
		break;
		default:
		return DIO_ERROR;
		break;
	}
	return DIO_OK;
}
uint8_t DIO_toggle(uint8_t portnumber,uint8_t pinnumber)
{
	switch (portnumber)
	{
		case PORT_A:
		PORTA^=(1<<pinnumber);
		break;
		case PORT_B:
		PORTB^=(1<<pinnumber);
		break;
		case PORT_C:
		PORTC^=(1<<pinnumber);
		break;
		case PORT_D:
		PORTD^=(1<<pinnumber);
		break;
		default:
		return DIO_ERROR;
		break;
	}
	return DIO_OK;
}
uint8_t DIO_read(uint8_t portnumber,uint8_t pinnumber,uint8_t *value)
{
	switch (portnumber)
	{
		case PORT_A:
		*value=(PINA&(1<<pinnumber))>>pinnumber;
		break;
		case PORT_B:
		*value=(PINB&(1<<pinnumber))>>pinnumber;
		break;
		case PORT_C:
		*value=(PINC&(1<<pinnumber))>>pinnumber;
		break;
		case PORT_D:
		*value=(PIND&(1<<pinnumber))>>pinnumber;
		break;
		default:
		return DIO_ERROR;
		break;
	}
	return DIO_OK;
}