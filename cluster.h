#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include "defs.h"
#include "list.h"
#include "point.h"

typedef struct Cluster_ Cluster, *PCluster;



PCluster ClusterCreate(int);
void ClusterDestroy(PCluster);
Result ClusterAddPoint(PCluster, PElement);
int ClusterGetMinDistance(PCluster, PElement);
void ClusterPrint(PCluster);

#endif
