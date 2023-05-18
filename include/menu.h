#ifndef MENU_H
#define MENU_H

/* MENU ITEM ID CONSTANTS */

#define SUBMENU_NEW 1
#define MENU_RESTART 2
#define MENU_QUIT 3
#define MENU_SUB_TWO_PLAYER_GAME 4
#define MENU_SUB_FOUR_PLAYER_GAME 5

// menu callback function for handling the user's selection from the menu
void menu(int option);

// create a game menu
void createGameMenu(void);

#endif
