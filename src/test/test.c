#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cobject/cobject.h>

struct MyStruct
{
	// Guts
	COGuts *guts;

	// Contents
	char *stuff;
};

static void _MyStructDelete(void *aSelf)
{
	puts("destructor called");

	// Cast
	struct MyStruct *self = (struct MyStruct *)aSelf;

	// Delete contents
	free(self->stuff);
}

struct MyStruct *MyStructCreate(void)
{
	puts("constructor called");

	// Create
	struct MyStruct *newStruct = malloc(sizeof(struct MyStruct));
	if(!newStruct)
		return NULL;

	// Create contents
	newStruct->stuff = malloc(100*sizeof(char));
	strcpy(newStruct->stuff, "hello world");

	// Init
	COInitialize(newStruct);
	COSetDestructor(newStruct, &_MyStructDelete);

	// Done
	return newStruct;
}

int main(void)
{
	struct MyStruct *myStruct = MyStructCreate();

	CORetain(myStruct);
	CORetain(myStruct);
	CORetain(myStruct);

	CORelease(myStruct);
	CORelease(myStruct);
	CORelease(myStruct);
	CORelease(myStruct);

	return 0;
}
