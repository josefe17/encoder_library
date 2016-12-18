/*
 * Encoder_multi_mode.c
 *
 * Created: 18/12/2016 13:16:44
 * Author : josefe
 */ 

#include "encoder_multi.h"

#ifdef ENCODER_X1

void encoder_init_x1(void)
{
	DDR_A |= (PIN_AS_INPUT<<PIN_A_NUMBER);
	DDR_B |= (PIN_AS_INPUT<<PIN_B_NUMBER);

	INTERRUPT_A_MODE_REGISTER |= (INTERRUPT_A_MODE_MASK & (INTERRUPT_FALLING_EDGE<<INTERRUPT_A_MODE_NUMBER));
	ENCODER_A_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
}

void disable_encoder_interrupts_x1(void)
{
	ENCODER_A_INTERRUPTS_ENABLE &= ~(INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
}

void enable_encoder_interrupts_x1(void)
{
	ENCODER_A_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
}

void encoder_ISR_x1(unsigned char* increments, unsigned char* decrements)
{
	if ((PIN_B & (1<<PIN_B_NUMBER)) && (*increments)<MAX_INCREMENTS)
	{
		(*increments)++;
	}
	if (!(PIN_B & (1<<PIN_B_NUMBER)) && (*decrements)<MAX_DECREMENTS)
	{
		(*decrements)++;
	}
}

#endif // ENCODER_X1


#ifdef ENCODER_X2

void encoder_init_x2(void)
{
	DDR_A |= (PIN_AS_INPUT<<PIN_A_NUMBER);
	DDR_B |= (PIN_AS_INPUT<<PIN_B_NUMBER);

	INTERRUPT_A_MODE_REGISTER |= (INTERRUPT_A_MODE_MASK & (INTERRUPT_ON_CHANGE<<INTERRUPT_A_MODE_NUMBER));
	ENCODER_A_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
}

void disable_encoder_interrupts_x2(void)
{
	ENCODER_A_INTERRUPTS_ENABLE &= ~(INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
}

void enable_encoder_interrupts_x2(void)
{
	ENCODER_A_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
}

void encoder_ISR_x2(unsigned char* increments, unsigned char* decrements)
{
	if (((PIN_A>>PIN_A_NUMBER) & 1) ^ ((PINB >> PIN_B_NUMBER) & 1))
	{
		if ((*increments)<MAX_INCREMENTS)
		{
			(*increments)++;
		}
	}
	else
	{
		if ((*decrements)<MAX_DECREMENTS)
		{
			(*decrements)++;
		}
	}
}

#endif //ENCODER_X2


#ifdef ENCODER_X4

void encoder_init_x4(unsigned char* previous_st)
{
	DDR_A |= (PIN_AS_INPUT<<PIN_A_NUMBER);
	DDR_B |= (PIN_AS_INPUT<<PIN_B_NUMBER);
	
	(*previous_st)=((PIN_A>>PIN_A_NUMBER) & 1) | ((PIN_B<<(7-PIN_A_NUMBER)) & 128);

	INTERRUPT_A_MODE_REGISTER |= (INTERRUPT_A_MODE_MASK & (INTERRUPT_ON_CHANGE<<INTERRUPT_A_MODE_NUMBER));
	INTERRUPT_B_MODE_REGISTER |= (INTERRUPT_B_MODE_MASK & (INTERRUPT_ON_CHANGE<<INTERRUPT_B_MODE_NUMBER));
	ENCODER_A_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
	ENCODER_B_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_B_INTERRUPTS_ENABLE_NUMBER);
	
}

void disable_encoder_interrupts_x4(unsigned char* previous_st)
{
	ENCODER_A_INTERRUPTS_ENABLE &= ~(INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
	ENCODER_B_INTERRUPTS_ENABLE &= ~(INTERRUPTS_ENABLED<<ENCODER_B_INTERRUPTS_ENABLE_NUMBER);
}

void enable_encoder_interrupts_x4(unsigned char* previous_st)
{
	(*previous_st)=((PIN_A>>PIN_A_NUMBER) & 1) | ((PIN_B<<(7-PIN_A_NUMBER)) & 128);
	
	ENCODER_A_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_A_INTERRUPTS_ENABLE_NUMBER);
	ENCODER_B_INTERRUPTS_ENABLE |= (INTERRUPTS_ENABLED<<ENCODER_B_INTERRUPTS_ENABLE_NUMBER);
}

void encoder_ISR_x4(unsigned char* increments, unsigned char* decrements, unsigned char* previous_st)
{
	unsigned char pin_a_tmp = PIN_A;
	unsigned char pin_b_tmp = PIN_B;
	if (((pin_a_tmp>>PIN_A_NUMBER) & 1) ^ ((pin_b_tmp >> PIN_B_NUMBER) & 1))
	{
		if (((pin_a_tmp>>PIN_A_NUMBER) & 1) ^ (((*previous_st)>>PIN_A_NUMBER) & 1))
		{
			if ((*increments)<MAX_INCREMENTS)
			{
				(*increments)++;
			}
		}
		else
		{
			if ((*decrements)<MAX_DECREMENTS)
			{
				(*decrements)++;
			}	
		}
	}
	else
	{
		if (((pin_b_tmp<<(7-PIN_A_NUMBER)) & 128) ^ (((*previous_st)<<(7-PIN_A_NUMBER)) & 128))
		{
			if ((*increments)<MAX_INCREMENTS)
			{
				(*increments)++;
			}
		}
		else
		{
			if ((*decrements)<MAX_DECREMENTS)
			{
				(*decrements)++;
			}
		}
	}
	(*previous_st)=((pin_a_tmp>>PIN_A_NUMBER) & 1) | ((pin_b_tmp<<(7-PIN_A_NUMBER)) & 128);
}

#endif //ENCODER_X4












