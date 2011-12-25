#include <stdio.h>
#include <cobject/cobject.h>

void _ModelDestroy(void *aSelf)
{
	printf("Destroying model    %p\n", aSelf);
}

void _BodyDestroy(void *aSelf)
{
	printf("Destroying body     %p\n", aSelf);
}

void _AsteroidDestroy(void *aSelf)
{
	printf("Destroying asteroid %p\n", aSelf);
}

struct Model
{
	COGuts guts;
	void *world;
};

struct Body
{
	struct Model model;
	int x, y;
};

struct Asteroid
{
	struct Body body;
	int radius;
};

COClass ModelType = {
	.size       = sizeof (struct Model),
	.superclass = NULL,
	.destructor = &_ModelDestroy
};

COClass BodyType = {
	.size       = sizeof (struct Body),
	.superclass = &ModelType,
	.destructor = &_BodyDestroy
};

COClass AsteroidType = {
	.size       = sizeof (struct Asteroid),
	.superclass = &BodyType,
	.destructor = &_AsteroidDestroy
};

void test_heap(void)
{
	puts("*** Doing the heap dance!");

	struct Asteroid *heapAsteroid = COCreate(&AsteroidType);

	heapAsteroid->body.model.world = (void *)0x1234; // ridiculous value
	heapAsteroid->body.x = 500;
	heapAsteroid->body.y = 570;
	heapAsteroid->radius = 20;

	CORetain(heapAsteroid);
	CORelease(heapAsteroid);
	CORelease(heapAsteroid);
}

void test_stack(void)
{
	puts("*** Doing the stack dance!");

	struct Asteroid stackAsteroid CO_OBJECT;
	COInit(&stackAsteroid, &AsteroidType);

	stackAsteroid.body.model.world = (void *)0x1234; // ridiculous value
	stackAsteroid.body.x = 500;
	stackAsteroid.body.y = 570;
	stackAsteroid.radius = 20;

	CORetain(&stackAsteroid);
	CORelease(&stackAsteroid);
	CORelease(&stackAsteroid);

	stackAsteroid.radius = 30; // silly, but the memory is still there
}

void test_stack_nonzeroReferenceCount(void)
{
	puts("*** Doing the stack dance with a nonzero reference count!");

	struct Asteroid stackAsteroid CO_OBJECT;
	COInit(&stackAsteroid, &AsteroidType);

	stackAsteroid.body.model.world = (void *)0x1234; // ridiculous value
	stackAsteroid.body.x = 500;
	stackAsteroid.body.y = 570;
	stackAsteroid.radius = 20;

	CORetain(&stackAsteroid);
	CORelease(&stackAsteroid);
}

int main(void)
{
	test_heap();
	test_stack();
	test_stack_nonzeroReferenceCount();

	return 0;
}
