/*
@unittest clang
@xfail
@expected
1
2_3
@expected.
*/
#include <stdio.h>
int main(void)
{
    printf("1\n"
           "2 3\n");
}
