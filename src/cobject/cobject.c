#include <stdlib.h>

#include <cobject/cobject.h>
#include <cobject/private.h>

bool COObjectInitialize(void *aObject)
{
	// Create guts
	((COObject *)aObject)->guts = malloc(sizeof(COGuts));
	if(!((COObject *)aObject)->guts)
		return false;

	// Initialize
	((COObject *)aObject)->guts->referenceCount = 0;

	// Done
	return true;
}

void COObjectSetDestructor(void *aObject, CODestructor aDestructor)
{
	// Set destructor
	((COObject *)aObject)->guts->destructor = aDestructor;
}

void COObjectRetain(void *aObject)
{
	// Retain
	((COObject *)aObject)->guts->referenceCount++;
}

void COObjectRelease(void *aObject)
{
	// Release
	((COObject *)aObject)->guts->referenceCount--;

	// Destroy if necessary
	if(((COObject *)aObject)->guts->referenceCount == 0)
		((COObject *)aObject)->guts->destructor(aObject);
}
