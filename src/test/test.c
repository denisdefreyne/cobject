#include <stdio.h>
#include <cobject/cobject.h>

void _ModelDestroy(void *aSelf)
{
	printf("Destroying model %p\n", aSelf);
}

void _BodyDestroy(void *aSelf)
{
	printf("Destroying body %p\n", aSelf);
}

void _AsteroidDestroy(void *aSelf)
{
	printf("Destroying asteroid %p\n", aSelf);
}

COType ModelType = {
	.supertype = NULL,
	.destructor = &_ModelDestroy
};

COType BodyType = {
	.supertype = &ModelType,
	.destructor = &_BodyDestroy
};

COType AsteroidType = {
	.supertype = &BodyType,
	.destructor = &_AsteroidDestroy
};

struct Asteroid
{
	COGuts guts;
};

struct Asteroid *AsteroidCreate(void)
{
	struct Asteroid *asteroid = calloc(1, sizeof (struct Asteroid));
	COInitialize(asteroid, &AsteroidType);

	return asteroid;
}

int main(void)
{
	struct Asteroid *asteroid = AsteroidCreate();
	CORetain(asteroid);
	CORelease(asteroid);
	CORelease(asteroid);

	return 0;
}
