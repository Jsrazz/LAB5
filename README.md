Lab 5 Moving Asterisk Game

Uses LCD abnd Button libraries from lab 4, along with the shell code provided by Captain Branchflower.
Implements design through use of interupts with both timer A and buttons.

player is represented by an asterisk and needs to reach the bottom right corner of the lcd, using push buttons to move.

Code

    unsigned char initPlayer();
        returns the address of the first position in the game (Ox80)
        this can be called to place the player at the starting position
    void printPlayer(unsigned char player);
        prints the player symbol to the passed in location
    void clearPlayer(unsigned char player);
        clears the passed in location by printing a space
    unsigned char movePlayer(unsigned char player, unsigned char direction);
        returns an updated position based on an input position and direction of movement
        uses 1, 2, 3 and 4 to correspond with each different button used.
    char didPlayerWin(unsigned char player);
        returns 1 if the player is at the winning position, 0 
        used with an if statement that will clear the lcd and then print the winning statement.
        Also waits for a reset in order to restart the game.
    void init_buttons();
    initializes pins one through four as inputs for the push buttons, also enables them to trigger the interrupt flag on port 1.

Instructions

button 1 moves left, 2 right, 3 down, 4 up.
Does not allow loop arounds when trying to enter a location off of the display.
If two seconds pass without a movement the player loses.
If the asterisk reaches the bottom right location, victory.

Documentation:

Received help from C2C Mordan with an explaination of how the interrupts worked. 
