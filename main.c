#include <stdio.h>
#include <string.h>
#include "allocator.h"

int main(){
    printf("---Allocator Test---\n");

    int *age = (int*)my_malloc(sizeof(int));
    if(age){
    *age = 25;
    printf("stored %d at address %p\n", *age , (void*)age);
    }

    char* name = (char*)my_malloc(10);
    if(name){
        strcpy(name , "vishesh");
        printf("stored %s at address %p\n", name , (void*)name);
    }
    return 0;
}