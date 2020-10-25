#include <iostream>
#include "../intrin/intrin.h"
#include <xmmintrin.h> // should have all (most) nowadays

// https://gcc.gnu.org/onlinedocs/gcc/Vector-Extensions.html
// https://stackoverflow.com/questions/1389712/getting-started-with-intel-x86-sse-simd-instructions
// http://sci.tuomastonteri.fi/programming/sse
// https://stackoverflow.com/questions/11228855/header-files-for-x86-simd-intrinsics
// https://stackoverflow.com/questions/59373900/why-is-there-no-simd-functionality-in-the-c-standard-library
//
// int is the base type defined to v4si with the size of 16 bytes
typedef int v4si __attribute__ ((vector_size (16)));

int main()
{
   //C=A+B scalar addition SISD
   //C0=A0+B0 vector addition SIMD addition
   //C1=A1+B1
   //__m256d a = {0.0, 1.0, 2.0, 3.0};    
   //_mm_adds_epu8
   v4si b, c;
   v4si a = {4, 5, 4, 5};
   c = a * 1;

   return 0;
}
