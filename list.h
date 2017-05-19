#ifndef _LIST_H_
#define _LIST_H_

typedef struct List_* PList;
typedef struct List_Element_* PList_Element;
typedef void* PElement;

typedef Result (*CLONE_ELEMENT)(PElement, PElement);
typedef void (*DELETE_ELEMENT)(PElement);
typedef BOOL (*COMPARE_ELEMENT)(PElement, PElement);
typedef void (*PRINT_ELEMENT)(PElement);

PList ListCreate(CLONE_ELEMENT,DELET_ELEMENT,COMPARE_ELEMENTS,PRINT_ELEMENT);
void ListDestroy(PList);
Result ListAdd(PList, PElement);
Result ListRemove(PList, PElement);
PElement ListGetFirst(PList);
PElement ListGetNext(PList);
BOOL ListCompare(PElement, PElement);
void ListPrint(PList);

#endif
