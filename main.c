#include <msp430.h> 
#include "LCD.h"
#include "button.h"
#include "game.h"
/*
 * main.c
 */
unsigned char player;
int reset = 0;
int TIMER = 0;
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


	char winMess[] ={'Y','0','U'};
	char winMess2[] = {'W','1','N'};

	char loseMess[] ={'G','@','M','3'};
	char loseMess2[] = {'0','V','3','R'};


	initSPI();
	LCDinit();
	LCDclear();

	player = initPlayer();

	init_timer();
	init_buttons();
	__enable_interrupt();
	printPlayer(player);

	while(1){
		if( didPlayerWin( player )){
			LCDclear();
			createString(winMess,3);
			cursorToLineTwo();
			createString(winMess2,3);
			reset = 0;
			while(reset == 0){}
			LCDclear();
			player = initPlayer();
			printPlayer(player);
			TIMER = 0;

		}
		if (TIMER == 4){
			LCDclear();
			createString(loseMess,4);
			cursorToLineTwo();
			createString(loseMess2,4);
			reset = 0;
			while(reset == 0){}
			LCDclear();
			player = initPlayer();
			printPlayer(player);
			TIMER = 0;
		}


	}
}

#pragma vector=TIMER0_A1_VECTOR		// idea from Ryan Good
__interrupt void TIMER0_A1_ISR()
	{
		TACTL &= ~TAIFG; // clear interrupt flag
		TIMER ++;

	}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1_ISR(void){

		if( P1IFG & BIT1 ){
			if (isP1ButtonPressed(BIT1)){
				clearPlayer(player);
				player = movePlayer(player, 1);
				printPlayer(player);
				TAR = 0;
				TIMER = 0;

			}
			P1IFG &= ~BIT1;

		}

		if( P1IFG & BIT2 ){
			if (isP1ButtonPressed(BIT2)){
				clearPlayer(player);
				player = movePlayer(player, 2);
				printPlayer(player);
				TAR = 0;
				TIMER = 0;

			}
			P1IFG &= ~BIT2;

		}
		if( P1IFG & BIT3 ){
			if (isP1ButtonPressed(BIT3)){
				clearPlayer(player);
				player = movePlayer(player, 3);
				printPlayer(player);
				TAR = 0;
				TIMER = 0;

			}
			P1IFG &= ~BIT3;

		}
		if( P1IFG & BIT4 ){
			if (isP1ButtonPressed(BIT4)){
				clearPlayer(player);
				player = movePlayer(player, 4);
				printPlayer(player);
				TAR = 0;
				TIMER = 0;

			}
			P1IFG &= ~BIT4;

		}
		reset = 1;



	}








void init_timer()
{
	TACTL &= ~(MC1|MC0);
	TACTL |= TACLR;
	TACTL |= TASSEL1;
	TACTL |= ID1|ID0;
	TACTL &= ~TAIFG;
	TACTL |= MC1;
	TACTL |= TAIE;
	_enable_interrupt();
}

void init_buttons()
{
	configureP1PinAsButton(BIT1|BIT2|BIT3|BIT4);
	 P1IE |= BIT1|BIT2|BIT3|BIT4;
	 P1IES |= BIT1|BIT2|BIT3|BIT4;
}
