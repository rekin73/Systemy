#include <stdio.h>
#include "kopiuj.h"
int main(int argc, char* argv[]){
if(argc!=3){
    if(argv[1]==NULL)
        printf("brak pliku do skopiowania");
        else if(argv[2]==NULL)
            printf("brak pliku docelowego");
            else 
                printf("za duzo argumentow");
    /*błędne argumenty*/
    printf("usage: %s [source_file_name] [copy_file_name]",argv[0]);
}
else{
    
    kopiuj(argv[1],argv[2]);
}
}