#include <unistd.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    printf("pierwszy komunikat\n");
    execl("./potomny.x","potomny.x",NULL);
    printf("drugi komunikat");
    return 0;
}