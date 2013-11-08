#include <msp430.h>
#include "game.h"
#include "LCD.h"
#include "button.h"


unsigned char initPlayer()
{
	return 0x80;
}

void printPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{




	if (direction == 1){
		if( (player & 0x0f) < 7 )
		{
			player ++;
		}
		waitForP1ButtonRelease(BIT1);
		debounce();

	}


	else if (direction == 2){

		if( (player & 0x0f) > 0 )
		{
			player --;
		}
		waitForP1ButtonRelease(BIT2);
		debounce();

	}




	else if (direction == 3){
		player &= ~ROW_MASK;
		waitForP1ButtonRelease(BIT3);
		debounce();
	}


	else if (direction == 4){

		player |= ROW_MASK;
		waitForP1ButtonRelease(BIT4);
		debounce();
	}


	//
	// update player position based on direction of movement
	//


	return player;
}
unsigned char checkButton(unsigned char player)	{		// Idea from Ryan Good
	if (isP1ButtonPressed(BIT1))
	{
		//timer = 0;
		movePlayer(player, 1);
	}
	else if (isP1ButtonPressed(BIT2))
	{
		//	timer = 0;
		movePlayer(player, 2);
	}
	else if (isP1ButtonPressed(BIT3))
	{
		//	timer = 0;
		movePlayer(player, 3);
	}
	else if (isP1ButtonPressed(BIT4))
	{
		//timer = 0;
		movePlayer(player, 4);

	}

	return 0;
}

char didPlayerWin(unsigned char player)
{
	return player == 0xC7;
}
