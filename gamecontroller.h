#ifndef HEADER_GAMECONTROLLER
#define HEADER_GAMECONTROLLER

#include"ocelostone.h"

#define WIDTH 640
#define HEIGHT 640

typedef enum GameState {
  GAMESTATE_INIT = 1,
  GAMESTATE_WAIT_OPPONENT,
  GAMESTATE_GET_PUTABLE,
  GAMESTATE_SEND_SIGNAL,
  GAMESTATE_WAIT_MYTURN_SIGN,
  GAMESTATE_WAIT_OPTURN_SIGN,
  GAMESTATE_WAIT_MYPUT,
  GAMESTATE_SEND_POSITION,
  GAMESTATE_WAIT_OPPUT,
  GAMESTATE_REVERSE,
  GAMESTATE_WAIT_GAMEOVER_SIGN,
  GAMESTATE_RESULT_PUTSTONE,
  GAMESTATE_RESULT_SHOWRESULT,
  GAMESTATE_CONNECITON_LOST
}GameState;

int ControlGameWithState();
int SetSocket(int argc, char **argv);

extern GameState gameState;
extern OceloStoneColor myStoneColor;
extern OceloStoneColor enemyStoneColor;
extern int isFirstPlayer;

#endif