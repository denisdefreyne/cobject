#ifndef __COBJECT_COBJECT_H__
#define __COBJECT_COBJECT_H__

#include <stdbool.h>

// Object
typedef struct _COObject COObject;

// Guts
typedef struct _COGuts COGuts;

// Destructor
typedef void (*CODestructor)(void *aSelf);

// Initializing
bool COInitialize(void *aSelf);
void COSetDestructor(void *aSelf, CODestructor aDestructor);

// Retaining and releasing
void CORetain(void *aSelf);
void CORelease(void *aSelf);

#endif
