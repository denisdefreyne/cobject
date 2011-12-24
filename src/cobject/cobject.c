#include <cobject/cobject.h>

// Object
struct _COObject
{
	COGuts guts;
};
typedef struct _COObject COObject;

void COInitialize(void *aSelf)
{
	COObject *self = aSelf;

	self->guts.destructor     = NULL;
	self->guts.referenceCount = 1;
}

void COSetDestructor(void *aSelf, CODestructor aDestructor)
{
	COObject *self = aSelf;

	self->guts.destructor = aDestructor;
}

void *CORetain(void *aSelf)
{
	COObject *self = aSelf;

	self->guts.referenceCount++;

	return aSelf;
}

void CORelease(void *aSelf)
{
	COObject *self = aSelf;
	if (!self)
		return;

	self->guts.referenceCount--;
	if(self->guts.referenceCount == 0)
	{
		if (self->guts.destructor)
		  self->guts.destructor(self);

		free(self);
	}
}
