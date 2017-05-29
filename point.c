#include "defs.h"
#include "list.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point_ {
	int dim;
	int coord_count;
	PList coord_list;
};

struct Coordinate_ {
	int x;
};


//*************************************************************************
//* Function name: PointCreate
//* Description: Creates a new point with dimention N.
//* Parameters:
//*		-  int n - Dimention of the point
//* Return Value: ADT pointer for the new point.
//*************************************************************************

PPoint PointCreate(int n)
{
	PPoint new_point = (PPoint)malloc(sizeof(Point));
	if (!new_point)
		return NULL;
	new_point->dim = n;
	new_point->coord_count = 0;
	new_point->coord_list = ListCreate(cloneCoord, destroyCoord, compareCoord, printCoord);

	if (new_point->coord_list == NULL)
	{
		free(new_point);
		return NULL;
	}
	return new_point;
}


//*************************************************************************
//* Function name: PointDestroy
//* Description: deleting the point ADT and all coordinates ADTs
//* Parameters:
//*		-  PPoint point - a pointer to a point ADT
//* Return Value: none.
//*************************************************************************

void PointDestroy(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL)
		return;
	if (point->coord_list != NULL)
	{
		ListDestroy(point->coord_list);
	}
	free(point);
	return;
}

//*************************************************************************
//* Function name: PointAddCoordinate
//* Description: creates a new coordinate in a point
//* Parameters:
//*		-  PPoint point - pointer to point ADT
//*     -  int x - the coordinate to add
//* Return Value: SUCCESS if we addeed the coordinate or FAIL if not
//*************************************************************************

Result PointAddCoordinate(PElement element, int x)
{
	PPoint point = (PPoint)element;
	if (point == NULL)
		return FAIL;
	if (point->coord_count >= point->dim)
		return FAIL; ///////// לבדוק שזה מה שנדרש
	PCoord new_coord = createCoord(x);
	if (!ListAdd(point->coord_list, new_coord))
	{
		destroyCoord(new_coord);
		return FAIL;
	}
	point->coord_count = point->coord_count + 1;
	destroyCoord(new_coord);
	return SUCCESS;
}



//*************************************************************************
//* Function name: PointGetFirstCoordinate
//* Description: Getting the first coordinate of a point
//* Parameters:
//*		-  PPoint point - a pointer to a point element
//* Return Value: an int with coordinate or 0 if no coordinate is there.
//*************************************************************************

int PointGetFirstCoordinate(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL || point->coord_count == 0)
		return 0;
	PCoord coord = (PCoord)ListGetFirst(point->coord_list);
	if (coord == NULL)
		return 0;
	int first_coord = coord->x;
	return first_coord;
}

//*************************************************************************
//* Function name: PointGetNextCoordinate
//* Description: Getting the next coordinate of a point
//* Parameters:
//*		-  PPoint point - a pointer to a point element
//* Return Value: an int with coordinate or 0 if no coordinate is there.
//*************************************************************************

int PointGetNextCoordinate(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL || point->coord_count == 0)
		return 0;
	PCoord coord = (PCoord)ListGetNext(point->coord_list);
	if (coord == NULL)
		return 0;
	int next_coord = coord->x;
	return next_coord;
}

//*************************************************************************
//* Function name: PointPrint
//* Description: printing the point given with pointer 'point'
//* Parameters:
//*		-  PElement element - a pointer to a point
//* Return Value: none.
//*************************************************************************

void PointPrint(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL)
		return;
	printf("Point Dimension: %d, Size: %d, Coordinates: ", point->dim, point->coord_count);
	ListPrint(point->coord_list);
	//printf("\n");
	return;
}

//*************************************************************************
//* Function name: getPointDim
//* Description: returns the dim of the point
//* Parameters:
//*		-  PElement element - pointer to point
//* Return Value: the dimention
//*************************************************************************


int getPointDim(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL)
		return 0;
	return point->dim;
}

//*************************************************************************
//* Function name: getPointSize
//* Description: returns the size of the point
//* Parameters:
//*		-  PElement element - pointer to point
//* Return Value: the size
//*************************************************************************

int getPointSize(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL)
		return 0;
	return point->coord_count;
}
//*************************************************************************
//* Function name: clonePoint
//* Description: creating a new point the same as given.
//* Parameters:
//*		-  PElement element - pointer to point
//* Return Value: a pointer to the cloned point
//*************************************************************************

PElement clonePoint(PElement element)
{
	PPoint point = (PPoint)element;
	if (point == NULL)
		return NULL;
	PPoint cloned_p = PointCreate(point->dim);
	PCoord coord = ListGetFirst(point->coord_list);

	while (coord != NULL)
	{
		if (PointAddCoordinate(cloned_p, coord->x) == FAIL)
		{
			PointDestroy(cloned_p);
			return NULL;
		}
		coord = ListGetNext(point->coord_list);
	}
	return (PElement)cloned_p;
}

//*************************************************************************
//* Function name: comparePoint
//* Description: compares two points
//* Parameters:
//*		-  PElement element1,2 - two pointers to points
//* Return Value: TRUE if they are the same or FALSE otherwise.
//*************************************************************************

BOOL comparePoint(PElement element1, PElement element2)
{
	PPoint point1 = (PPoint)element1;
	PPoint point2 = (PPoint)element2;
	if (point1->dim != point2->dim)
		return FALSE;
	if (point1->coord_count != point2->coord_count)
		return FALSE;
	if (ListCompare(point1->coord_list, point2->coord_list) == FALSE)
		return FALSE;
	return TRUE;
}

//*************************************************************************
//* Function name: getDistanceOfTwoPoints
//* Description: calculates the distance between two points
//* Parameters:
//*		-  PElement element1,2 - pointer to point two elements
//* Return Value: returns an int with the distance.
//*************************************************************************

int getDistanceOfTwoPoints(PElement element1, PElement element2)
{
	PPoint point1 = (PPoint)element1;
	PPoint point2 = (PPoint)element2;
	if (point1->dim != point2->dim || point1->coord_count != point2->coord_count)
		return 1000;
	PCoord coord1 = (PCoord)(ListGetFirst(point1->coord_list));
	PCoord coord2 = (PCoord)(ListGetFirst(point2->coord_list));
	int sum = 0;
	int i = 0;
	for (; i < point1->dim; i++)
	{
		sum = sum + (coord1->x - coord2->x)*(coord1->x - coord2->x);
		coord1 = (PCoord)(ListGetNext(point1->coord_list));
		coord2 = (PCoord)(ListGetNext(point2->coord_list));
	} 
	return sum;
}

//*************************************************************************
//* Function name: createCoord
//* Description: creates a new coordinate ADT for Point list
//* Parameters:
//*		-  int x - the coordinate
//* Return Value: a pointer to the coordinate
//*************************************************************************

PCoord createCoord(int x)
{
	PCoord new_coord = (PCoord)malloc(sizeof(Coord));
	if (!new_coord)
		return NULL;
	new_coord->x = x;
	return new_coord;
}

//*************************************************************************
//* Function name: cloneCoord
//* Description: cloning a coordinate to a new coordinate adt.
//* Parameters:
//*		-  PElement coord - a pointer to a coordinate to clone
//* Return Value: a pointer to the new cloned coordinate
//*************************************************************************

PElement cloneCoord(PElement coord)
{
	if (coord == NULL)
		return NULL;
	PCoord old_coord = (PCoord)coord;
	PCoord cloned_coord = (PCoord)malloc(sizeof(Coord));
	if (!cloned_coord)
		return NULL;
	cloned_coord->x = old_coord->x;
	return (PElement)cloned_coord;
}

//*************************************************************************
//* Function name: destroyCoord
//* Description: freeing a coordinate ADT
//* Parameters:
//*		-  PElemnt coord - a pointer to coordinate ADT to free
//* Return Value: none.
//*************************************************************************

void destroyCoord(PElement coord)
{
	if (coord == NULL)
		return;
	PCoord coord_to_destroy = (PCoord)coord;
	free(coord_to_destroy);
	return;
}

//*************************************************************************
//* Function name: compareCoord
//* Description: Compares to coordinates
//* Parameters:
//*		- PElement element1 - first pointer to element to compare
//*     - PElement element2 - second pointer to element to compare
//* Return Value: TRUE if they are the same and FALSE if not
//*************************************************************************

BOOL compareCoord(PElement element1, PElement element2)
{
	PCoord coord1 = (PCoord)element1;
	PCoord coord2 = (PCoord)element2;
	if (coord1->x == coord2->x)
		return TRUE;
	return FALSE;
}

//*************************************************************************
//* Function name: printCoord
//* Description: Printing a single coordinate
//* Parameters:
//*		-  PElement element - a pointer to a coordinate element
//* Return Value: none.
//*************************************************************************

void printCoord(PElement element)
{
	if (element == NULL)
		return;
	PCoord coord = (PCoord)element;
	printf("%d ", coord->x);
	return;
}