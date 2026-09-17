/*
@unittest clang
@args 3 "2 .5" \" 1\\ $HOME
@expected
	arg 0 './argsN'
	arg 1 '3'
	arg 2 '2 .5'
	arg 3 '"'
	arg 4 '1\'
	arg 5 '$HOME'
@expected.
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("\targ %d '%s'\n", i, argv[i]);
    }
}
