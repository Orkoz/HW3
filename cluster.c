#include "defs.h"
#include "list.h"
#include "point.h"
#include "cluster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cluster_  {
	int dim;
	int point_count;
	int MSD;
	PList point_list;
};


//*************************************************************************
//* Function name: ClusterCreate
//* Description: creates a new cluster of dimention dim.
//* Parameters:
//*		- int dim - the dimention of the cluster
//* Return Value: pointer to new cluster.
//*************************************************************************


PCluster ClusterCreate(int dim)
{
	PCluster new_cluster = (PCluster)malloc(sizeof(Cluster));
	if (!new_cluster)
		return NULL;
	new_cluster->dim = dim;
	new_cluster->point_count = 0;
	new_cluster->MSD = 1000;
	new_cluster->point_list = ListCreate(clonePoint, PointDestroy, comparePoint, PointPrint);
	if (new_cluster->point_list == NULL)
	{
		free(new_cluster);
		return NULL;
	}
	return new_cluster;
}

//*************************************************************************
//* Function name: ClusterDestroy
//* Description: Deletes cluster from memory.
//* Parameters:
//*		- PCluster cluster - pointer for cluster to delete.
//* Return Value: none.
//*************************************************************************

void ClusterDestroy(PCluster cluster)
{
	if (cluster == NULL)
		return;
	if (cluster->point_list != NULL)
		ListDestroy(cluster->point_list);
	free(cluster);
	return;
}

//*************************************************************************
//* Function name: ClusterAddPoint
//* Description: Adds a point ADT to the cluster
//* Parameters:
//*		- PCluster cluster - a pointer to the cluster
//*     - PElement element - a pointer to the point element
//* Return Value: SUCCESS if added or FAIL if not.
//*************************************************************************

Result ClusterAddPoint(PCluster cluster, PElement element)
{
	if (cluster == NULL || element == NULL)
		return FAIL;
	// checking if both in same dimention and size
	if (cluster->dim != getPointDim(element))
		return FAIL;
	if (cluster->dim != getPointSize(element))
		return FAIL;
	//checking if there is a point like this already
	if (isElementExists(cluster->point_list, element) == TRUE)
		return FAIL;
	//creating new point and adding it
	PPoint new_point = clonePoint(element);
	if (new_point == NULL)
		return FAIL;
	
	int distance;
	if (cluster->point_count != 0)
		distance = ClusterGetMinDistance(cluster, new_point);

	if (ListAdd(cluster->point_list, new_point) == FAIL)
	{
		PointDestroy(new_point);
		return FAIL;
	}

	if (cluster->point_count == 1) 
	{
		// if this is the second point added, update MSD to eliminate first value of 1000
		cluster->MSD = distance;
	}
	else if (cluster->point_count != 0 && distance < cluster->MSD) 
	{
		// if this is the 3rd point added (or more), chk distance and update if smaller than current MSD
		cluster->MSD = distance;
	}

	cluster->point_count = cluster->point_count + 1;

	PointDestroy(new_point);
	return SUCCESS;
}

//*************************************************************************
//* Function name: ClusterGetMinDistance
//* Description: calculates the minimum distance between a point and a clu-
//*              -ster
//* Parameters:
//*		- PCluster cluster - pointer to cluster
//*     - PElement element - pointer to point to check distance with
//* Return Value: returns the distance or 1000 if error occurs
//*************************************************************************

int ClusterGetMinDistance(PCluster cluster, PElement element)
{
	if (cluster == NULL || element == NULL)
		return 1000;

	PElement curr_point = ListGetFirst(cluster->point_list);

	int minDist = getDistanceOfTwoPoints(curr_point, element);
	if (minDist == 1000)
		return 1000;

	int i = 1;
	for (; i < cluster->point_count; i++)
	{
		curr_point = ListGetNext(cluster->point_list);
		int currMin = getDistanceOfTwoPoints(curr_point, element);
		if (currMin < minDist)
			minDist = currMin;
	}

	return minDist;
}


//*************************************************************************
//* Function name: ClusterPrint
//* Description: print a cluster
//* Parameters:
//*		- PCluster cluster - pointer to cluster to print
//* Return Value: none.
//*************************************************************************

void ClusterPrint(PCluster cluster)
{
	if (cluster == NULL)
		return;
	printf("Cluster's dimension: %d\n", cluster->dim);
	ListPrint(cluster->point_list);
	printf("Minimum Square Distance: %d\n", cluster->MSD);
	return;
}