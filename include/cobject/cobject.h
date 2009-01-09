#include <stdbool.h>

// Object
typedef struct _COObject COObject;

// Guts
typedef struct _COGuts COGuts;

// Destructor
typedef void (*CODestructor)(void *aObject);

// Initializing
bool COObjectInitialize(void *aObject);
void COObjectSetDestructor(void *aObject, CODestructor aDestructor);

// Retaining and releasing
void COObjectRetain(void *aObject);
void COObjectRelease(void *aObject);
