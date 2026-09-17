/*
@unittest printf "1\n2 3\n" >data ; clang
@expected data
@teardown rm data
*/
#include <stdio.h>
int main(void)
{
    printf("1\n"
           "2 3\n");
}
