#include "defs.h"
#include "list.h"
#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person_ {
    char *name;
    int age, ID;
};


//*************************************************************************
//* Function name: PersonCreate
//* Description: creates a person ADT according to the given parameters.
//* Parameters:
//*		-  name – a string of the person name.
//*		-  age – the age of the person.
//*		-  ID – the ID pf the person (unique for each person).
//* Return Value: a person ADT pointer.
//*************************************************************************

PPerson PersonCreate(char *name, int age, int ID){

    PPerson new_person = (PPerson)malloc(sizeof(Person));
    if (new_person == NULL)
        return NULL;

    new_person->name = (char*)malloc(1+strlen(name));
    if (new_person->name == NULL){
		free(new_person->name);
        free(new_person);
        return NULL;
    }

    strcpy(new_person->name, name);
    new_person->age=age;
    new_person->ID=ID;
    return new_person;
}


//*************************************************************************
//* Function name: clonePerson
//* Description: creates a copy of a person ADT
//* Parameters:
//*		-  source_person  - a pointer to a person ADT which will be copied from.
//* Return Value: Pointer to cloned person adt.
//*************************************************************************

PElement clonePerson(PElement pElem_two){
    //if (pElem_one == NULL || pElem_two == NULL)
    //    return FAIL;

    //PPerson target_person = (PPerson)pElem_one;
    PPerson source_person = (PPerson)pElem_two;
	PPerson cloned_person = PersonCreate(source_person->name, source_person->age, source_person->ID);
	return (PElement)cloned_person;

    //target_person->ID = source_person->ID;
    //target_person->age = source_person->age;

    //target_person->name= (char*) malloc(1+strlen(source_person->name));
	//if (target_person->name == NULL)
	//{
	//	free(target_person->name); // שחרור של השם
	//	return FAIL;
	//}

    //strcpy(target_person->name, source_person->name);
    //return SUCCESS;
}


//*************************************************************************
//* Function name: destroyPerson
//* Description: removes a person ADT from memory.
//* Parameters:
//*		-  person - a person ADT pointer.
//* Return Value: None.
//*************************************************************************

void destroyPerson(PElement pElem){
    if (pElem == NULL)
        return;

    PPerson person = (PPerson)pElem;
	free(person->name); // הוספתי
    free(person); // האם צריך לעשות שחרור לשם הבנאדם בנפרד??
}


//*************************************************************************
//* Function name: comparePerson
//* Description: compare two persons ADTs base on there ID.
//* Parameters:
//*		-  person_one  - a pointer to a person ADT to be compare.
//*		-  person_two  - a pointer to a person ADT to be compare.
//* Return Value: SUCCESS if the action succeeded and FAIL otherwise.
//*************************************************************************

BOOL comparePersons(PElement pElem_one, PElement pElem_two){
    //all users check first that person one and person two are not NULL

    PPerson person_one = (PPerson)pElem_one;
    PPerson person_two = (PPerson)pElem_two;

    if (person_one->ID == person_two->ID)
        return TRUE;

    return FALSE;


}


//*************************************************************************
//* Function name: printPerson
//* Description: print the person ADT parameters.
//* Parameters:
//*		-  person - a pointer to a person ADT.
//* Return Value: None.
//*************************************************************************

void printPerson(PElement pElem){
    if (pElem == NULL)
        return;

    PPerson person = (PPerson)pElem;

    printf("Name: %s, ID: %d, Age: %d\n",person->name,person->ID,person->age);
}

