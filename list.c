#include "list.h"
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

struct List_{
    PList_Element first_list_element;
    PList_Element last__list_element;
    PList_Element Iterator; //a pointer to a node in the list for implementing iterators on the list.

    CLONE_ELEMENT CloneElementFunc;
    DELETE_ELEMENT DeleteElementFunc;
    COMPARE_ELEMENTS CompareElementFunc;
    PRINT_ELEMENT PrintElementFunc;
};

struct List_Element_{
    PElement Element;
    PList_Element Next_Element;
};


//*************************************************************************
//* Function name: ListCreate
//* Description: creats a new empty ADT according to the given parameters.
//* Parameters:
//*		-  CloneElement – a pointer to function which clones an element.
//*		-  DeleteElement – a pointer to function which deletes an element.
//*		-  CompareElements – a pointer to function which compares two elements.
//*		-  PrintElement – a pointer to function which prints the element.
//* Return Value: a pointer to an ADT.
//*************************************************************************


PList ListCreate(CLONE_ELEMENT CloneElement, DELETE_ELEMENT DeleteElement, COMPARE_ELEMENTS CompareElement, PRINT_ELEMENT PrintElement){
    PList list = (PList)malloc(sizeof(PList));

    if (list != NULL) {
        list->first_list_element = NULL;
        list->last__list_element = NULL;
        list->Iterator = NULL;
        list->CloneElementFunc = CloneElement;
        list->CompareElementFunc = CompareElement;
        list->DeleteElementFunc = DeleteElement;
        list->PrintElementFunc = PrintElement;
    }
    return list;
}


//*************************************************************************
//* Function name: ListDestroy
//* Description: removes a list and all its contained elements from memory.
//* Parameters:
//*		-  list – a pointer to an ADT.
//* Return Value: None.
//*************************************************************************

void ListDestroy(PList list){
    if (list == NULL)
        return;

    PList_Element list_element =  list->first_list_element;
    PList_Element prev_list_element;
    while (list_element != NULL){
        list->DeleteElementFunc(list_element ->Element);
        prev_list_element = list_element;
        list_element->Next_Element;
        free(prev_list_element);
    }
    free(list);
}


//*************************************************************************
//* Function name: ListAdd
//* Description: adds a copy of the element to the ADT.
//* Parameters:
//*		-  list – a pointer to an ADT.
//*		-  element - a pointer to an element which will be insert to the ADT.
//* Return Value: SUCCESS if the action succeeded and FAIL otherwise.
//*************************************************************************

Result ListAdd(PList list, PElement element){
    if (list == NULL || element == NULL)
        return FAIL;

    PList_Element new_list_element = (PList_Element)malloc(sizeof(PList_Element));
    PElement new_element = (PElement)malloc(sizeof(PElement));
    Result clone_flag = FAIL;

	////////////////////////////////////////////////// לא בטוח שצריך את זה! ניתן שיהיו שני אנשים זהים
	// מה בקשר לשאר השאלה?
    if (isElementExists(list, element) == TRUE)
        return FAIL;
	///////////////////////////////////////////////

    if (new_element != NULL)
        clone_flag = list->CloneElementFunc(new_element, element);

    if ((new_list_element != NULL) && (clone_flag == SUCCESS)){
        new_list_element->Element = new_element;
        new_list_element->Next_Element=NULL;
        if (list->first_list_element == NULL) {
            list->first_list_element = new_element;
            list->last__list_element = new_element;
        } else {
            list->last__list_element->Next_Element = new_list_element; ////// אולי צריך להחליף בין האיבר האחרון לזה?
			list->last__list_element = new_list_element; //// הוספתי את זה בשביל זה
        }
        return SUCCESS;
    }

    free(new_list_element);
    free(new_element);
    return FAIL;
}



BOOL isElementExists(PList list, PElement element) {

    PElement tmp_element = ListGetFirst(list);

    while (tmp_element != NULL){
        if (list->CompareElementFunc(tmp_element,element) == TRUE)
            return TRUE;
        tmp_element = ListGetNext(list);
    }
    return FALSE;
}


//*************************************************************************
//* Function name: ListRemove
//* Description: removes the matched element in the ADT to the given element.
//* Parameters:
//*		-  list – a pointer to an ADT.
//*		-  element - a pointer to an element which will be removed from the ADT.
//* Return Value: SUCCESS if the action succeeded and FAIL otherwise.
//*************************************************************************

Result ListRemove(PList list, PElement element){

    if (list == NULL || element == NULL)
        return FAIL;

    PList_Element tmp_list_element = list->first_list_element;
    PList_Element prev_list_element = NULL; //an help pointer for the deleting action.
    PElement tmp_element = NULL;

    while (tmp_list_element != NULL){ //goes through all the nodes in the list.
        tmp_element = tmp_list_element->Element;
        if (list->CompareElementFunc(tmp_element,element) == TRUE){ // if we found a matched element we need to delete its node and it from the list.
            if (tmp_list_element == list->first_list_element){ //handling the first node case.
                list->first_list_element = tmp_list_element->Next_Element;
            } else { //handling all other cases.
                prev_list_element->Next_Element=tmp_list_element->Next_Element;
            }

            if (list->Iterator == tmp_list_element) //keeping the iterator on track
                list->Iterator = tmp_list_element->Next_Element;
            list->DeleteElementFunc(tmp_element);
            free(tmp_list_element);
            return SUCCESS;

        } else {
            prev_list_element = tmp_list_element;
            tmp_list_element = tmp_list_element->Next_Element;
        }
    }

    return FAIL;

}


//*************************************************************************
//* Function name: ListGetFirst
//* Description: get the first element in the ADT.
//* Parameters:
//*		-  list – a pointer to an ADT.
//* Return Value: a pointer to the first element in the ADT.
//*************************************************************************

PElement ListGetFirst(PList list){
    if (list == NULL)
        return NULL;

    list->Iterator = list->first_list_element;
    if (list->Iterator == NULL)
        return NULL;
    return list->Iterator->Element;
}


//*************************************************************************
//* Function name: ListGetNext
//* Description: get the Next element in the ADT (relative to the ADT iterator).
//* Parameters:
//*		-  list – a pointer to an ADT.
//* Return Value: a pointer to the next element in the ADT (relative to the ADT iterator).
//*************************************************************************

PElement ListGetNext(PList list){
    if (list == NULL)
        return NULL;

    list->Iterator = list->Iterator->Next_Element;
    if (list->Iterator == NULL)
        return NULL;
    return list->Iterator->Element;

}


//*************************************************************************
//* Function name: ListCompre
//* Description: compare between to ADTs.
//* Parameters:
//*		-  list_one – a pointer to the first ADT to be compared.
//*		-  list_two – a pointer to the second ADT to be compared.
//* Return Value: TRUE if the ADT are matched and FALSE otherwise.
//*************************************************************************

BOOL ListCompare(PList list_one, PList list_two){
    if (list_one == NULL || list_two == NULL)
        return FALSE;

    PElement list_one_element = ListGetFirst(list_one);
    PElement list_two_element = ListGetFirst(list_two);

    while ((list_one_element != NULL) && (list_two_element != NULL)){
        if (list_one->CompareElementFunc(list_one_element, list_two_element) == TRUE){
            list_one_element = ListGetNext(list_one);
            list_two_element = ListGetNext(list_two);
        } else {
            return FALSE;
        }
    }

    return TRUE; //if the two lists are empty returns TRUE
}


//*************************************************************************
//* Function name: ListPrint
//* Description: print the ADTs element details to the screen (new row for each element)
//* Parameters:
//*		-  list– a pointer to the ADT to be printed.
//* Return Value: None.
//*************************************************************************

void ListPrint(PList list){
    if (list == NULL)
        return;

    PElement element = ListGetFirst(list);
    //list->PrintElementFunc(element);
    while (element != NULL){
        list->PrintElementFunc(element); ///לא צריך להחליף ביניהם
        printf("\n");
        element = ListGetNext(list); ///
    }
}