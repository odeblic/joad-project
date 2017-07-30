#include <stdio.h>

void * addr_function;
void * addr_nothing;
void * addr_array;
void * addr_value;
void * addr_ptr;

void stack_explore()
{
    puts("***  stack_explore  ***");

    void * ptr;
    addr_ptr = &ptr;

    /*
    printf("size = %d\n", addr_array - addr_ptr);
    printf("size = %d\n", addr_ptr - addr_array);
    */

    for(ptr = addr_ptr - 16; ptr < addr_array + 64; ++ptr)
    {
        if(ptr == addr_array)
        {
            printf("[%p] : %X (array)\n", ptr, *(unsigned char*)ptr);
        }
        else if(ptr == addr_value)
        {
            printf("[%p] : %X (value)\n", ptr, *(unsigned char*)ptr);
        }
        else if(ptr == addr_ptr)
        {
            printf("[%p] : %X (ptr)\n", ptr, *(unsigned char*)ptr);
        }
        /*
        else if(*(unsigned int*)ptr == *(unsigned int*)addr_function)
        {
          printf("[%p] : %X (function)\n", ptr, *(unsigned char*)ptr);
        }
        else if(*(unsigned int*)ptr == *(unsigned int*)addr_nothing)
        {
          printf("[%p] : %X (nothing)\n", ptr, *(unsigned char*)ptr);
        }
        */
        else
        {
            printf("[%p] : %X\n", ptr, *(unsigned char*)ptr);
        }
    }
}

void function()
{
    puts("***  function  ***");

    unsigned char array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    addr_array = &array;

    stack_explore();
}

void nothing()
{
    puts("***  nothing  ***");
};

int main(int argc, char **argv)
{
    puts("***  main  ***");

    addr_function = &function;
    addr_nothing = &nothing;

    unsigned int value = 0x00ABCDEF;
    addr_value = &value;

    printf("[%p] : ? (function)\n", addr_function);
    printf("[%p] : ? (nothing)\n", addr_nothing);

    printf("[%p] : 0x%X (value)\n", addr_value, value);

    function();
    nothing();

    printf("[%p] : 0x%X (value)\n", addr_value, value);

    return 0;
}
