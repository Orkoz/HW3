#ifndef _PERSON_H_
#define _PERSON_H_
#include "defs.h"
#include "list.h"

typedef struct Person_ Person,*PPerson;

PPerson PersonCreate(char*, int, int);
PElement clonePerson(PElement);
void destroyPerson(PElement);
BOOL comparePersons(PElement, PElement);
void printPerson(PElement);

#endif
