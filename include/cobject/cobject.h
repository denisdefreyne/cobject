#ifndef __COBJECT_COBJECT_H__
#define __COBJECT_COBJECT_H__

#include <stdlib.h>

// Destructor
typedef void (*CODestructor)(void *aSelf);

// Class
struct _COClass
{
	struct _COClass *superclass;
	CODestructor destructor;
};
typedef struct _COClass COClass;

// Guts
typedef struct _COGuts COGuts;
struct _COGuts
{
	COClass *class;
	size_t referenceCount;
};

// Initializing
void COInitialize(void *aSelf, COClass *aClass);

// Retaining and releasing
void *CORetain(void *aSelf);
void CORelease(void *aSelf);

// Accessing (retain+release)
#define CO_SET_RR(a, b) { CORetain((b)); CORelease((a)); a = b; }

#endif
