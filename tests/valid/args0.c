/*
@unittest	clang	 	 
@expected
	arg 0 './args0'
@expected.
*/
#include <stdio.h>
int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("\targ %d '%s'\n", i, argv[i]);
    }
}
