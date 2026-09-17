/*
@unittest clang
@args 3
@expected
	arg 0 './args1'
	arg 1 '3'
@expected.
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("\targ %d '%s'\n", i, argv[i]);
    }
}
