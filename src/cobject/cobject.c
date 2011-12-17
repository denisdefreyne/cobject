#include <stdlib.h>

#include <cobject/cobject.h>

// Object
struct _COObject
{
	COGuts *guts;
};
typedef struct _COObject COObject;

// Guts
struct _COGuts
{
	size_t       referenceCount;
	CODestructor destructor;
};

bool COInitialize(void *aSelf)
{
	// Cast
	COObject *self = (COObject *)aSelf;

	// Create guts
	self->guts = malloc(sizeof(COGuts));
	if(!self->guts)
		return false;

	// Initialize
	self->guts->destructor     = NULL;
	self->guts->referenceCount = 1;

	// Done
	return true;
}

void COSetDestructor(void *aSelf, CODestructor aDestructor)
{
	// Cast
	COObject *self = (COObject *)aSelf;

	// Set destructor
	self->guts->destructor = aDestructor;
}

void *CORetain(void *aSelf)
{
	// Cast
	COObject *self = (COObject *)aSelf;

	// Retain
	self->guts->referenceCount++;

	return aSelf;
}

void CORelease(void *aSelf)
{
	// Cast
	COObject *self = (COObject *)aSelf;

	// Release
	self->guts->referenceCount--;

	// Destroy if necessary
	if(self->guts->referenceCount == 0)
	{
		// Call destructor
		if (self->guts->destructor)
		  self->guts->destructor(self);

		// Destroy object
		free(self->guts);
		free(self);
	}
}
