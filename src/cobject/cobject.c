#include <stdlib.h>

#include <cobject/cobject.h>
#include <cobject/private.h>

bool COInitialize(void *aObject)
{
	// Create guts
	((COObject *)aObject)->guts = malloc(sizeof(COGuts));
	if(!((COObject *)aObject)->guts)
		return false;

	// Initialize
	((COObject *)aObject)->guts->referenceCount = 1;

	// Done
	return true;
}

void COSetDestructor(void *aObject, CODestructor aDestructor)
{
	// Set destructor
	((COObject *)aObject)->guts->destructor = aDestructor;
}

void CORetain(void *aObject)
{
	// Retain
	((COObject *)aObject)->guts->referenceCount++;
}

void CORelease(void *aObject)
{
	// Release
	((COObject *)aObject)->guts->referenceCount--;

	// Destroy if necessary
	if(((COObject *)aObject)->guts->referenceCount == 0)
	{
		// Call destructor
		((COObject *)aObject)->guts->destructor(aObject);

		// Destroy object
		free(((COObject *)aObject)->guts);
		free((COObject *)aObject);
	}
}
