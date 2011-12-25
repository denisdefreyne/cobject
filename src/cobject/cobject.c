#include <cobject/cobject.h>

void *COCreate(COClass *aClass)
{
	COGuts *instance = calloc(1, aClass->size);
	COInit(instance, aClass);
	instance->isOnHeap = true;
	return instance;
}

void COInit(void *aSelf, COClass *aClass)
{
	COGuts *self = aSelf;

	self->class          = aClass;
	self->referenceCount = 1;
}

void *CORetain(void *aSelf)
{
	COGuts *self = aSelf;
	if (!self)
		return aSelf;

	self->referenceCount++;

	return aSelf;
}

static void _CODestroyAsClass(void *aSelf, COClass *aClass)
{
	if (!aClass)
		return;

	if (aClass->destructor)
		aClass->destructor(aSelf);

	_CODestroyAsClass(aSelf, aClass->superclass);
}

void CORelease(void *aSelf)
{
	COGuts *self = aSelf;
	if (!self)
		return;

	self->referenceCount--;
	if (self->referenceCount == 0)
	{
		_CODestroyAsClass(self, self->class);
		if (self->isOnHeap)
			free(self);
	}
}
