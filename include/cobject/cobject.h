#ifndef __COBJECT_COBJECT_H__
#define __COBJECT_COBJECT_H__

// Guts
typedef struct _COGuts COGuts;

// Destructor
typedef void (*CODestructor)(void *aSelf);

// Initializing
void COInitialize(void *aSelf);
void COSetDestructor(void *aSelf, CODestructor aDestructor);

// Retaining and releasing
void *CORetain(void *aSelf);
void CORelease(void *aSelf);

// Accessing (retain+release)
#define CO_SET_RR(a, b) { CORetain((b)); CORelease((a)); a = b; }

#endif
