#ifndef _LIST_H_
#define _LIST_H_

typedef struct List_* PList;
typedef void* List_Element;

typedef Result (*CLONE_ELEMENT)(List_Element, List_Element);
typedef void (*DELETE_ELEMENT)(List_Element);
typedef BOOL (*COMPARE_ELEMENT)(List_Element, List_Element);
typedef void (*PRINT_ELEMENT)(List_Element);

PList ListCreate(CLONE_ELEMENT,DELET_ELEMENT,COMPARE_ELEMENTS,PRINT_ELEMENT);
void ListDestroy(PList);
Result ListAdd(PList, List_Element);
Result ListRemove(PList, List_Element);
List_Element ListGetFirst(PList);
List_Element ListGetNext(PList);
BOOL ListCompare(List_Element, List_Element);
void ListPrint(PList);

#endif
