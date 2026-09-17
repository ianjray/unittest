/*
@unittest clang
@args "1
@expected
	arg 0 './args-unterminated'
	arg 1 '1'
@expected.
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("\targ %d '%s'\n", i, argv[i]);
    }
}
