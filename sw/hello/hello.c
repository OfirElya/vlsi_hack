#include <stdio.h>
#include "csr.h"

unsigned int mcycle_l, mcycle_l_after;
unsigned int mcycle_h, mcycle_h_after;
int main(void)
{
    mcycle_l = csr_read(0xc00);
    mcycle_h = csr_read(0xc80);
    printf("Hello, SCR!\n");
    
    unsigned int cycles_before = (mcycle_h << 16) | mcycle_l;

    const unsigned int BASE = 0xF1000000;
    unsigned int* go = BASE;
    unsigned int *a = BASE + 8;
    unsigned int *b = BASE + 12;
    unsigned int *c = BASE + 16;
    unsigned int *count = BASE + 4;


    printf("a=%p\nb=%p\nc=%p\ncount=%p\n", a,b,c, count);



    *a = 0x00000405;
    *b = 0x00000201;
    *go = 1;
    printf("wrote value to a\n");
    printf("wrote value to b\n");
    printf("wrote value 1 to go\n");
    
    unsigned int a0 =  a[0] & 0x000000FF;
    unsigned int a1 =  (a[0] & 0x0000FF00) >> 8;
    
    unsigned int b0 =  b[0] & 0x000000FF;
    unsigned int b1 =  (b[0] & 0x0000FF00) >> 8;

    unsigned int c0 =  c[0] & 0x000000FF;
    unsigned int c1 =  (c[0] & 0x0000FF00) >> 8;
    unsigned int count_value = (*(unsigned int*)count) & 0x0000FFFF;


    printf("read values:\n");
    printf("a=%x\n", *a);
   // printf("a[1]=%u\n", a1);

    printf("b=%x\n", *b);
    //printf("b[1]=%u\n", b1);

    printf("c=%x\n", *c);
    //printf("c[1]=%u\n", c1);
    printf("count value=%u\n", count_value);

    
    mcycle_l_after = csr_read(0xc00);
    mcycle_h_after = csr_read(0xc80);
    unsigned int cycles_after = (mcycle_h_after << 16) | mcycle_l_after;

    printf("cycles_before = %u\ncycles_after = %u\nDiff = %u", cycles_before, cycles_after, (cycles_after-cycles_before));

    return 0;
}
