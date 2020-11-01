// Generate assembly and link the executable and analyze the binary output (nm, objdump)

#include<stdio.h>

int incrementAndAdd(int* a, int* b)
{
   *a++;
   *b++;
   return *a + *b;
}

int incrementAndAddRestrict(int* restrict a, int* restrict b)
{
   *a++;
   *b++;
   return *a + *b;
}

int add5AndAdd(int*, int*);
int add5AndAddRestrict(int* restrict, int* restrict);

int add5AndAdd(int* a, int* b)
{
   *a +=5;
   *b +=5;
   return *a + *b;
}

int add5AndAddRestrict(int* restrict a, int* restrict b)
{
   *a +=5;
   *b +=5;
   return *a + *b;
}

int overwrite(int* a, int* b)
{
   *a = 5;
   *b = 6;
   return *a + *b;
}

int overwriteRestrict(int* restrict a, int* restrict b)
{
   *a = 5;
   *b = 6;
   return *a + *b;
}

int overwriteTheSame(int* a, int* b)
{
   *a = 5;
   *b = 5;
   return *a + *b;
}

void multiplyArrays(int* restrict dst, int* restrict src1, int* restrict src2, size_t size)
{
   for (int i = 0; i < size; i++)
   {
      dst[i] = src1[i] * src2[i];
   }
}

int main(void)
{

   int a1[10] = {[0 ... 9] = 1};
   int a2[10] = {[0 ... 9] = 2};
   int a3[10] = {0};

   int size = sizeof(a1);

   multiplyArrays(a3, a1, a1, size);

   return 0;
}
