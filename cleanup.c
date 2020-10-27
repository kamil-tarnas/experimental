#include <stdio.h>
#include <stdlib.h>

void destructor(void** arg_pp)
{
   free(*arg_pp);
   printf("Cleaning 0x%x\n", *arg_pp);
}

int main(void)
{
   int* thePointer_p __attribute__ ((__cleanup__(destructor))) = malloc(sizeof(*thePointer_p));
   return 0;
}
