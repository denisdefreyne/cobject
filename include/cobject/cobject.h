#ifndef __COBJECT_COBJECT_H__
#define __COBJECT_COBJECT_H__

#include <stdbool.h>

// Object
typedef struct _COObject COObject;

// Guts
typedef struct _COGuts COGuts;

// Destructor
typedef void (*CODestructor)(void *aObject);

// Initializing
bool COInitialize(void *aObject);
void COSetDestructor(void *aObject, CODestructor aDestructor);

// Retaining and releasing
void CORetain(void *aObject);
void CORelease(void *aObject);

#endif
