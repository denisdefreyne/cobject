#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cobject/cobject.h>

struct MyStruct
{
	COGuts *guts;

	char *stuff;
};

static void _MyStructDelete(void *aStruct)
{
	puts("destructor called");

	free(((struct MyStruct *)aStruct)->stuff);
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
