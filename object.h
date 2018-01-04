#ifndef HEADER_OBJECT
#define HEADER_OBJECT

#include"ocelostone.h"
#include"putpoint.h"
#include"string3d.h"

typedef enum ObjectType {
  OBJECT_OCELO_STONE,
  OBJECT_SELECTABLE_POINT,
  OBJECT_STRING
}ObjectType;

typedef union ObjectBody {
  Stone *stone;
  OceloPoint *point;
  String3D *string;
}ObjectBody;

typedef struct Object {
  ObjectType type;
  ObjectBody object;
}Object;

typedef struct ObjectList {
  Object *obj;
  ObjectList *next;
}ObjectList;

int DrawAllObject();
int UpdateAllObject();
int ObjectListInit();
int DeleteAllObject();
int DeleteObject(Object *obj);
int AddObject(Object *obj);
int DeleteSelectedTypeObject(ObjectType type);

#endif