#include <stdio.h>
int main(void){
    printf("\033c");
    printf("\033[%d;%dH", 11,9);
    printf("\033[33mHello\033[m\n");
}