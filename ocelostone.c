#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include"ocelostone.h"
#include"object.h"
#include"oceloboard.h"

#define CIRCLE_VERTEX 100
#define OCELO_STONE_RADIUS 20
#define REVERSE_STATE_TIME 500 //(ms)

void StateProgress(Stone *stone, StoneState next);
StoneStateContena InitStoneStateContena(StoneState state);
void StateAutoMaton(Stone *stone);
void DrawStone(Object *obj);
void DeleteStone(Object *obj);
void UpdateStone(Object *obj);
GLdouble CalcAngle(Stone *stone);

void UpdateStone(Object *obj) {
  Stone *stone = obj->object.stone;

  StateAutoMaton(stone);
  stone->angle = CalcAngle(stone);
}

//this function generates OceloStone and set initial setting
Stone* InitOceloStone(int x, int y, OceloStoneColor type) {
  Stone *stone;
  Object *obj;

  stone = (Stone*)malloc(sizeof(Stone));
  if(stone == NULL) return NULL;
  obj = (Object*)malloc(sizeof(Object));
  if(obj == NULL) return NULL;

  switch(type) {
    case STONE_COLOR_BLACK: 
      stone->stone = STONE_COLOR_BLACK;
      stone->state = InitStoneStateContena(STONE_STATE_BLACK);
      stone->angle = 0;
      break;
    case STONE_COLOR_WHITE:
      stone->stone = STONE_COLOR_WHITE;
      stone->state = InitStoneStateContena(STONE_STATE_WHITE);
      stone->angle = 180.0;
      break;
    default:
      printf("(%s)Error line:%d\n", __FILE__, __LINE__);
      exit(1);
  }

  stone->pos[0] = x;
  stone->pos[1] = y;

  obj->type = OBJECT_OCELO_STONE;
  obj->object.stone = stone;
  obj->Update = UpdateStone;
  obj->Delete = DeleteStone;
  obj->Draw = DrawStone;

  if(AddObject(obj) == 0) return NULL;

  return stone;
}

GLdouble CalcAngle(Stone *stone) {
  switch(stone->state.state) {
    case STONE_STATE_BLACK:
      return 0;
    case STONE_STATE_WHITE:
      return 180;
    case STONE_STATE_REVERSE_B2W:
      return ((GLdouble)180 / REVERSE_STATE_TIME) * stone->state.stateTime;
    case STONE_STATE_REVERSE_W2B:
      return ((GLdouble)180 / REVERSE_STATE_TIME) * stone->state.stateTime + 180.0;
  }

  return 0;
}

void StateAutoMaton(Stone *stone) {
  switch(stone->state.state) {
    case STONE_STATE_BLACK:
    case STONE_STATE_WHITE:
      return;
    case STONE_STATE_REVERSE_B2W:
      StateProgress(stone, STONE_STATE_WHITE);
      return;
    case STONE_STATE_REVERSE_W2B:
      StateProgress(stone, STONE_STATE_BLACK);
      return;
  }
}

void StateProgress(Stone *stone, StoneState next) {
  if(stone->state.startTime == 0) stone->state.startTime = glutGet(GLUT_ELAPSED_TIME);

  stone->state.stateTime = glutGet(GLUT_ELAPSED_TIME) - stone->state.startTime;

  if(stone->state.stateTime > stone->state.shiftTime) {
    stone->state = InitStoneStateContena(next);
    //StateAutoMaton(stone);
  }

  return;
}

StoneStateContena InitStoneStateContena(StoneState state) {
  StoneStateContena s = {state, 0, 0, 0};

  switch(state) {
    case STONE_STATE_BLACK:
    case STONE_STATE_WHITE:
      break;
    case STONE_STATE_REVERSE_B2W:
    case STONE_STATE_REVERSE_W2B:
      s.shiftTime = REVERSE_STATE_TIME;
      break;
  }

  return s;
}

void DrawStone(Object *obj) {
  int xx, yy;
  Stone *stone;

  stone = obj->object.stone;

  xx = OCELO_MARGIN + OCELO_SQUARE_SIZE * stone->pos[0] + (OCELO_SQUARE_SIZE / 2);
  yy = OCELO_MARGIN + OCELO_SQUARE_SIZE * stone->pos[1] + (OCELO_SQUARE_SIZE / 2);

  int i;
  double cx, cy;

  if((stone->angle >= 0 && stone->angle < 90.0) || 
     (stone->angle >= 270.0 && stone->angle < 360.0))     glColor3d(0, 0, 0);
  if(stone->angle >= 90.0 && stone->angle < 270.0)        glColor3d(1, 1, 1);
  
  
  glTranslated((GLdouble)xx, (GLdouble)yy, 0);
  glRotated(stone->angle, 0, 1.0, 0);
  glBegin(GL_POLYGON);
  for(i = 0; i < CIRCLE_VERTEX; i++) {
    cx = OCELO_STONE_RADIUS * cos(2 * M_PI * ((double)i / CIRCLE_VERTEX));
    cy = OCELO_STONE_RADIUS * sin(2 * M_PI * ((double)i / CIRCLE_VERTEX));

    glVertex2d(cx, cy);
  }
  glEnd();
}

void TriggerOfReverse(Stone *stone) {
  switch(stone->state.state) {
    case STONE_STATE_BLACK:
      stone->state = InitStoneStateContena(STONE_STATE_REVERSE_B2W);
      stone->stone = STONE_COLOR_WHITE;
      return;
    case STONE_STATE_WHITE:
      stone->state = InitStoneStateContena(STONE_STATE_REVERSE_W2B);
      stone->stone = STONE_COLOR_BLACK;
      return;
    default:
      printf("(%s)Error line:%d\n", __FILE__, __LINE__);
      exit(1);
  }
}

void DeleteStone(Object *obj) {
  free(obj->object.stone);
}

