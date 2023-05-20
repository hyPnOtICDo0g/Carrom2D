#include <GL/freeglut.h>

#include "menu.h"
#include "carrom.h"
#include "context.h"
#include "utilities.h"

void menu(int option) {
    switch(option) {
        case MENU_SUB_SINGLE_PLAYER_GAME:
            // restart the game only if it is not a single-player game
            if(state->numberOfPlayers > 0) {
                restartGame(1);
            }
            break;

        case MENU_SUB_TWO_PLAYER_GAME:
            // restart the game only if it is not a two-player game
            if(state->numberOfPlayers > 1 || state->numberOfPlayers == 0) {
                restartGame(2);
            }
            break;

        case MENU_SUB_FOUR_PLAYER_GAME:
            // restart the game only if it is not a four-player game
            if(state->numberOfPlayers < 3) {
                restartGame(4);
            }
            break;

        case MENU_RESTART:
            restartGame(-1);
            break;

        case MENU_QUIT:
            glutLeaveMainLoop();
            break;
    }
}

void createGameMenu(void) {
    int subMenuId = glutCreateMenu(menu);
    glutAddMenuEntry("Single Player", MENU_SUB_SINGLE_PLAYER_GAME);
    glutAddMenuEntry("Two Players", MENU_SUB_TWO_PLAYER_GAME);
    glutAddMenuEntry("Four Players", MENU_SUB_FOUR_PLAYER_GAME);
    // create the main menu and attach the submenu
    glutCreateMenu(menu);
    glutAddSubMenu("New Game", subMenuId);
    glutAddMenuEntry("Restart", MENU_RESTART);
    glutAddMenuEntry("Quit", MENU_QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
