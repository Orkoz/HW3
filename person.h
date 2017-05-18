#ifndef _PERSON_H_
#define _PERSON_H_

typedef struct Person_ Person,*PPerson;

PPerson PersonCreate(int*, int*);
Result clonePerson(PPerson, PPerson);
void deletePerson(PPerson);
BOOL comparePerson(PPerson, PPerson);
void printPerson(PPerson);

#endif
