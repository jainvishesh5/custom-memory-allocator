#include <stddef.h>
#include <unistd.h>

struct Block{
    size_t size;
    int is_free;
    struct Block *next;
};

struct Block* head = NULL;

struct Block* request_space(struct Block* last , size_t size){
    
    void* request = sbrk(size + sizeof(struct Block));

    if (request == (void*) -1) return NULL;

    struct Block* block = (struct Block*)request;

    if (last) last->next =block;

    block ->size =size;
    block->next =NULL;
    block -> is_free =0;
    return block;
}

struct Block* find_free_block(struct Block** last,  size_t size){
    struct Block* current = head;
    while(current && !(current -> is_free && current->size >=size)){
        *last = current;
        current = current->next;
    }
    return current;
}

void* my_malloc(size_t size){
    struct Block* block;
    if(size<=0)return NULL;

    if(!head){
        block = request_space(NULL, size);
        if(!block)return NULL;
        head = block;
    }

    else{
        struct Block* last = head;
        block = find_free_block(&last , size);
        if(!block){
            block = request_space(last , size);
            if(!block)return NULL;
        } else{
            block -> is_free = 0;
        }
    }
    return (void*)(block+1);
}

void my_free(void* ptr){
    if(!ptr)return;

    struct Block* block = (struct Block*)ptr -1;
    block-> is_free =1;
}


