#include <cobject/cobject.h>

#include <strings.h>

#ifdef __GNUC__

void COAutoCleanupError(COGuts *object)
{
	fprintf(stderr, "*** CObject: Stack-allocated (auto) variable exits scope with nonzero reference count; destructor was not called.\n");
	fprintf(stderr, "*** CObject: Break at COAutoCleanupError() to debug.\n");
}

void COAutoCleanup(void *aObject)
{
	COGuts *object = aObject;
	if (object->referenceCount > 0)
		COAutoCleanupError(object);
}

#endif

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

	bzero(aSelf, aClass->size);

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
