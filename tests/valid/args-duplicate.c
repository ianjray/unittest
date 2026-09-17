/*
@unittest clang
@args a
The last directive wins:
@args 42
@expected
	arg 0 './args-duplicate'
	arg 1 '42'
@expected.
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("\targ %d '%s'\n", i, argv[i]);
    }
}
