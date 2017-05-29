#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"

typedef struct Point_ Point, *PPoint;
typedef struct Coordinate_ Coord, *PCoord;

PPoint PointCreate(int);
void PointDestroy(PElement);
Result PointAddCoordinate(PElement, int);
int PointGetFirstCoordinate(PElement);
int PointGetNextCoordinate(PElement);
void PointPrint(PElement);

int getDistanceOfTwoPoints(PElement, PElement);
int getPointDim(PElement);
int getPointSize(PElement);

PElement clonePoint(PElement);
BOOL comparePoint(PElement, PElement);

PCoord createCoord(int);
PElement cloneCoord(PElement);
void destroyCoord(PElement);
BOOL compareCoord(PElement, PElement);
void printCoord(PElement);

#endif
