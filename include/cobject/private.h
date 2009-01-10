#ifndef __COBJECT_PRIVATE_H__
#define __COBJECT_PRIVATE_H__

#include <stddef.h>

// Object
struct _COObject
{
	COGuts *guts;
};

// Guts
struct _COGuts
{
	size_t       referenceCount;
	CODestructor destructor;
};

#endif
