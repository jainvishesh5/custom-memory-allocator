#include <stddef.h>
#include <unistd.h>
#include <string.h>

struct Block{
    size_t size;
    int is_free;
    struct Block *next;
    int padding;
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

void split_block(struct Block* block , size_t size){
    struct Block* new_block = (struct Block*)((char*)block + sizeof(struct Block) + size);
    
    new_block -> size = block->size - size - sizeof(struct Block);
    new_block-> is_free =1;
    new_block->next = block->next;

    block -> size =size;
    block->next = new_block;
    block->is_free =0;
}

void* my_malloc(size_t size){
    struct Block* block;
    if(size<=0)return NULL;

    size = (size+7) & ~7;

    if(!head){
        block = request_space(NULL, size);
        if(!block)return NULL;
        head = block;
    }

    else{
        struct Block* last = head;
        block = find_free_block(&last , size);

        if(block){ 
            if(block->size >= size + sizeof(struct Block) +16){

              split_block(block , size);
            }

        block->is_free =0;
    }
       else{
            block = request_space(last , size);
            if(!block)return NULL;
    }
}
    return (void*)(block+1);
}


void my_free(void* ptr){
    if(!ptr)return;

    struct Block* block = (struct Block*)ptr -1;
    block-> is_free =1;

    while(block->next && block->next->is_free){
        block->size += sizeof(struct Block) + block->next->size;
        block->next = block->next->next;
    }
}

void* my_calloc(size_t num , size_t size){
    size_t total_size = num*size;
    void* ptr = my_malloc(total_size);

    if(ptr) memset(ptr , 0 , total_size);
    return ptr;
}
