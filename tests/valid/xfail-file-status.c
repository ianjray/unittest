/*
@unittest printf "1\n2 3\n" >data ; clang
@xfail
@expected data
@teardown rm data
*/
#include <stdio.h>
int main(void)
{
    printf("1\n");
    return 1;
}
