#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cobject/cobject.h>

struct MyStruct
{
	COGuts *guts;

	char *stuff;
};

static void _MyStructDelete(struct MyStruct *aStruct)
{
	puts("destructor called");

	free(aStruct->stuff);
	free(aStruct);
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
	COObjectInitialize(newStruct);
	COObjectSetDestructor(newStruct, &_MyStructDelete);

	// Done
	return newStruct;
}

int main(void)
{
	struct MyStruct *myStruct = MyStructCreate();

	COObjectRetain(myStruct);
	COObjectRetain(myStruct);
	COObjectRetain(myStruct);

	COObjectRelease(myStruct);
	COObjectRelease(myStruct);
	COObjectRelease(myStruct);
	COObjectRelease(myStruct);

	return 0;
}
