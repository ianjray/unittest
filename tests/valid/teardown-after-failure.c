/*
@unittest rm -f teardown-after-failure.flag ; clang
@teardown touch teardown-after-failure.flag
*/
int main(void)
{
    return 1;
}
