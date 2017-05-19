#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List_{
    PList_Element first_list_element;
    PList_Element last__list_element;
    int element_num;

    CLONE_ELEMENT CloneElementFunc;
    DELET_ELEMENT DeleteElementFunc;
    COMPARE_ELEMENTS CompareElementFunc;
    PRINT_ELEMENT PrintElementFunc;
};

struct List_Element_{
    PElement Element;
    PList_Element Next_Element;
};

typedef Result (*CLONE_ELEMENT)(PElement, PElement);
typedef void (*DELETE_ELEMENT)(PElement);
typedef BOOL (*COMPARE_ELEMENT)(PElement, PElement);
typedef void (*PRINT_ELEMENT)(PElement);

PList ListCreate(CLONE_ELEMENT CloneElement,DELET_ELEMENT DeleteElement,COMPARE_ELEMENTS CompareElement,PRINT_ELEMENT PrintElement){
    PList list = (PList)malloc(sizeof(PList));

    if (list != NULL) {
        list->element_num = 0;
        list->first_list_element = NULL;
        list->last__list_element = NULL;
        list->CloneElementFunc = CloneElement;
        list->CompareElementFunc = CompareElement;
        list->DeleteElementFunc = DeleteElement;
        list->PrintElementFunc = PrintElement;
    }
    return list;
}

void ListDestroy(PList list){

    PList_Element list_element =  list->first_list_element;
    while (element != NULL){
        list->DeleteElementFunc(list_element ->Element);
        list_element->Next_element;
    }
    free(PList);
}

Result ListAdd(PList list, PElement element){
    PList_Element new_list_element = (PList_Element)malloc(sizeof(PList_Element));

    list->CloneElementFunc(element,new_element)
}
Result ListRemove(PList, PElement);
PElement ListGetFirst(PList);
PElement ListGetNext(PList);
BOOL ListCompare(PElement, PElement);
void ListPrint(PList);

