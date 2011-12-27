CObject
=======

_CObject_ is a library that adds support for object-orientation with 
inheritance, polymorphism, virtual destructors and reference counting to C.

Usage
-----

In _CObject_, an object is a struct allocated on the stack or the heap that 
starts with a “guts” struct that contains a pointer to the class as well as the 
reference count. A class is a struct that contains the size of its instances, a 
reference to the superclass and a function pointer to the destructor that will 
be called when the reference count reaches zero.

To prepare an object for use with _CObject_, set its first member to `COGuts`, 
like this:

	struct foo
	{
		COGuts guts;

		// ... other variables go here ...
		int *sampleArray;
	}

You will also need a class definition. Classes are `COClass` structs which can 
be defined like this:

	COClass fooClass = {
		.destructor = &_fooDestroy,
		.superclass = NULL
		.size       = sizeof (struct foo),
	};

The `destructor` contains a pointer to a function that will be called when the 
instance will be deleted. This function should not return anything and should 
take one `void *` as argument, the pointer to the object being deallocated. The 
destructor should undo anything allocated/retained during initalization. It 
should not free the struct itself. For instance:

	void fooDestroy(void *foo)
	{
		struct foo *fooS = foo;
		free(fooS->sampleArray);
	}

The `superclass` contains a pointer to the class definition of the superclass. 
When an object is deallocated, the destructor of its actual class will be 
called first, then the destructor of the superclass, and so on until no 
superclass can be found anymore.

The `size` contains the size of the struct that should be allocated. This is 
useful for functions that may need to allocate more memory for subclass 
instances.

Before an object can be used, it needs to be initialized first. This will 
initialize the reference count to 1, and it will also set the pointer to the 
given class. This is done using `COInit`, which takes a pointer to the struct 
(or to the guts, which is the same) and a pointer to the class definition. For 
example:

	struct foo stackFoo;
	COInit(&stackFoo, &fooClass);

If you are allocating an object on the heap, you _must_ use `COCreate` instead 
of allocating the object manually and releasing it. For example:

	struct foo *heapFoo = COCreate(&fooClass);

`COInit` (and `COCreate` which uses it) does not fully initialize your object.
You will need to do that yourself. For instance:

	stackFoo.sampleArray = calloc(100, sizeof (int);
	heapFoo->sampleArray = calloc(100, sizeof (int);

At this point, the `CORetain` and `CORelease` functions can be used to retain
and release objects. When the reference count reaches zero, the destructor
will be called and the object will be freed.

Example
-------

See `src/test/test.c` for an example.
