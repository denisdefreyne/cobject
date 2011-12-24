CObject
=======

`CObject` is a really simple reference counting implementation that makes
memory management in C applications and libraries a lot easier.

Usage
-----

`CObject` gives each _object_, which is a struct allocated on the heap, a
reference count. Each object also has a destructor function pointer; this
destructor will be called when the reference count reaches zero.

To prepare an object for use with `CObject`, set its first member to a pointer
to `COGuts`, like this:

	struct foo
	{
		// Object guts
		COGuts guts;

		// ... other variables go here ...
	}

When allocating an object on the heap, make sure to initialize it first. This
will set the reference count of this new object to one. Initializing is done
using `COInitialize`, which takes a pointer to the object that should be
initialized as its only argument. For example:

	struct foo *createFoo(void)
	{
		// Allocate object on heap
		struct foo *newFoo = malloc(sizeof (struct foo));

		// Initialize object
		COInitialize(newFoo);

		// ... will be continued ...

Next, set its destructor. The destructor is a function that returns nothing
(`void`) and takes only one argument: the pointer to the object. This pointer
should be a `void` pointer to prevent compiler warnings. This destructor
should free the object's content but _not the object itself, and not its guts
either_. For example:

	void deleteFoo(void *aFoo)
	{
		// Cast
		struct foo *self = (struct foo *)aFoo;

		// Free contents
		free(self->bar);
		free(self->baz);
		free(self->quux);
	}

Setting its destructor happens using `COSetDestructor`, which takes the object
on which to set a destructor as its first argument, and the pointer to the
destructor as its second argument. For example:

		// ... continued from COInitialize example above ...

		// Set destructor
		COSetDestructor(newFoo, &deleteFoo);

		// Return new object
		return newFoo;
	}

At this point, the `CORetain` and `CORelease` functions can be used to retain
and release objects. When the reference count reaches zero, the destructor
will be called and the object will be freed.

Example
-------

See `src/test/test.c` for an example.
