/*
@unittest echo '#define FOO "foo"' >>foo.h ; clang -I.
@expected
	FOO 'foo'
@expected.
@teardown rm foo.h
*/
#include <stdio.h>
#include "foo.h"
int main(void)
{
    printf("\tFOO '%s'\n", FOO);
}
