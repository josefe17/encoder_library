/*
 * encoder_multi.h
 *
 * Created: 18/12/2016 13:22:15
 *  Author: josefe
 */ 



#ifndef ENCODER_MULTI_H_
#define ENCODER_MULTI_H_

#include <avr/io.h>

/*Pins which reads inputs from encoder*/
#define CH_A_PIN			(PIN_CH_A & (1<<CH_A_PIN_NUMBER)>>CH_A_PIN_NUMBER)
#define CH_B_PIN			(PIN_CH_B & (1<<CH_B_PIN_NUMBER)>>CH_B_PIN_NUMBER)

/*Max values for data read*/
#define MAX_INCREMENTS 127
#define MAX_DECREMENTS 127

/*Control mode selection*/
#define ENCODER_X1
// #define ENCODER_X2
// #define ENCODER_X4

/*Function prototypes*/

/*Function that handles encoder rotation interrupts.
@param: void (*callback_function)(signed char) Function that process data read from encoder. Receives as param if the
rotation direction is clockwise (1) or counterclockwise (-1).
*/

#ifdef ENCODER_X1
	void encoder_init_x1(void);
	void disable_encoder_interrupts_x1(void);
	void enable_encoder_interrupts_x1(void);
	void encoder_ISR_x1(unsigned char*, unsigned char*);
#endif // ENCODER_X1

#ifdef ENCODER_X2
	void encoder_init_x2(void);
	void disable_encoder_interrupts_x2(void);
	void enable_encoder_interrupts_x2(void);
	void encoder_ISR_x2(unsigned char*, unsigned char*);
#endif // ENCODER_X2

#ifdef ENCODER_X4
	void encoder_init_x4(unsigned char*);
	void disable_encoder_interrupts_x4(unsigned char*);
	void enable_encoder_interrupts_x4(unsigned char*);
	void encoder_ISR_x4(unsigned char*, unsigned char*, unsigned char*);
#endif // ENCODER_X4

/*Custom values according to hardware*/
#define ENCODER_A_INTERRUPTS_ENABLE				EIMSK		//Register that controls interrupt enablE
#define ENCODER_A_INTERRUPTS_ENABLE_NUMBER		INT1		//Bit position of interrupt enable
#define INTERRUPT_A_MODE_REGISTER				EICRA		//register that controls interrupts mode
#define INTERRUPT_A_MODE_MASK					0b00001100	//Mask for writing on proper interrupt pin
#define INTERRUPT_A_MODE_NUMBER					2			//Number of LSL to place the Mode value

#ifdef ENCODER_X4
	#define ENCODER_B_INTERRUPTS_ENABLE				EIMSK		//Register that controls interrupt enablE
	#define ENCODER_B_INTERRUPTS_ENABLE_NUMBER		INT0		//Bit position of interrupt enable
	#define INTERRUPT_B_MODE_REGISTER				EICRA		//register that controls interrupts mode
	#define INTERRUPT_B_MODE_MASK					0b00000011	//Mask for writing on proper interrupt pin
	#define INTERRUPT_B_MODE_NUMBER					0			//Number of LSL to place the Mode value
#endif // ENCODER_X4

#define PIN_A_NUMBER				PIND3		//Bit position at I/O registers for pin A
#define PIN_B_NUMBER				PIND4		//Bit position at I/O registers for pin B

#define PIN_A						PIND		//Data input register for pin A
#define PIN_B						PIND		//Data input register for pin B

#define DDR_A						DDRD		//Direction register for pin A
#define DDR_B						DDRD		//Direction register for pin B

#define PULLUP_A					PORTD		//Pull-up enabling register for pin A
#define PULLUP_B					PORTD		//Pull-up enabling register for pin B

#define PIN_AS_INPUT			0			//Logic level for setting a pin as input
#define PULLUP_ENABLED			1			//Logic level for enabling pull-up resistors
#define INTERRUPTS_ENABLED		1			//Logic level for enabling interrupts
#define INTERRUPT_FALLING_EDGE	0b10		//Interrupt mode for mode x1
#define INTERRUPT_ON_CHANGE		0b01		//Interrupt mode for modes x2 & x4

#endif /* ENCODER_MULTI_H_ */