/*
@unittest clang
@uut exotic
@expected
1
2 3
@expected.
*/
#include <stdio.h>
int main(void)
{
    printf("1\n"
           "2 3\n");
}
