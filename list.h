#ifndef _LIST_H_
#define _LIST_H_

#include "defs.h"

typedef struct List_* PList;
typedef struct List_Element_* PList_Element;
typedef void* PElement;

typedef Result (*CLONE_ELEMENT)(PElement, PElement);
typedef void (*DELETE_ELEMENT)(PElement);
typedef BOOL (*COMPARE_ELEMENTS)(PElement, PElement);
typedef void (*PRINT_ELEMENT)(PElement);

PList ListCreate(CLONE_ELEMENT,DELETE_ELEMENT,COMPARE_ELEMENTS,PRINT_ELEMENT);
void ListDestroy(PList);
Result ListAdd(PList, PElement);
BOOL isElementExists(PList, PElement);
Result ListRemove(PList, PElement);
PElement ListGetFirst(PList);
PElement ListGetNext(PList);
BOOL ListCompare(PList , PList);
void ListPrint(PList);

#endif
