#include <stdlib.h>

#include <cobject/cobject.h>
#include <cobject/private.h>

bool COInitialize(void *aSelf)
{
	// Cast
	COObject *self = (COObject *)aSelf;

	// Create guts
	self->guts = malloc(sizeof(COGuts));
	if(!self->guts)
		return false;

	// Initialize
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

void CORetain(void *aSelf)
{
	// Cast
	COObject *self = (COObject *)aSelf;

	// Retain
	self->guts->referenceCount++;
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
		self->guts->destructor(self);

		// Destroy object
		free(self->guts);
		free(self);
	}
}
