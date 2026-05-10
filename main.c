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
    my_free(age);
    my_free(name);
    int* new_age = (int*)my_malloc(sizeof(int));
    if(new_age){
        *new_age = 30;
        printf("stored %d at address %p\n", *new_age , (void*)new_age);
    }

    if(age == new_age){
        printf("Memory reuse successful, both pointers are the same: %p\n", (void*)age);
    } else{
        printf("Memory reuse failed, pointers are different: %p and %p\n", (void*)age, (void*)new_age);
    }

    return 0;
}