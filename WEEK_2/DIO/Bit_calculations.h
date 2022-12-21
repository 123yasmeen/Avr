


#ifndef BIT_CALCULATIONS_H_
#define BIT_CALCULATIONS_H_
#define SET(REG,BIT) ((REG|=(1<<BIT)))
#define CLEAR(REG,BIT) ((REG&=~(1<<BIT)))
#define TOGGLE(REG,BIT) ((REG^=(1<<BIT)))
#define GET(REG,BIT) (((REG)>>(BIT))&0x01)



#endif /* BIT_CALCULATIONS_H_ */