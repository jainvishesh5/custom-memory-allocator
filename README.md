# Custom Memory Allocator in C

A simple implementation of a custom dynamic memory allocator written in C. This project recreates the core functionality of `malloc()`, `free()`, and `calloc()` using low-level system calls and manual heap management.

## Features

- Custom `malloc` implementation (`my_malloc`)
- Custom `free` implementation (`my_free`)
- Custom `calloc` implementation (`my_calloc`)
- Memory block metadata management
- Free block reuse
- Block splitting to reduce memory waste
- Adjacent free block coalescing
- 8-byte memory alignment
- Heap expansion using `sbrk()`



## Project Structure
.
├── allocator.c     # Memory allocator implementation
├── allocator.h     # Function declarations
└── main.c          # Test program


## How It Works

### Memory Block Layout

Each allocation is preceded by a metadata header:

c
struct Block {
    size_t size;
    int is_free;
    struct Block* next;
};

The allocator maintains a linked list of blocks:

+---------+---------+---------+
| Block 1 | Block 2 | Block 3 |
+---------+---------+---------+


Each block stores:

- Allocation size
- Free/used status
- Pointer to the next block


## Allocation Strategy

### 1. Find Free Block

Before requesting more memory from the operating system, the allocator searches existing free blocks:

c
find_free_block()


If a suitable block is found, it is reused.


### 2. Heap Expansion

If no free block is large enough, the heap is extended using:

c
sbrk(size + sizeof(Block))


### 3. Block Splitting

When a free block is significantly larger than the requested size, it is split:

Before:

+-----------------------+
| 100-byte free block   |
+-----------------------+

Request:

malloc(40)

After:

+----------+------------+
| 40 bytes | Free block |
+----------+------------+

This reduces internal fragmentation.

### 4. Memory Reuse

Freed blocks are marked as available:

c
my_free(ptr);

Future allocations can reuse these blocks without expanding the heap.

### 5. Coalescing

When adjacent blocks become free, they are merged:

Before:

[ Free 32 ] -> [ Free 64 ]

After:

[ Free 96 ]

This reduces external fragmentation.

## Alignment

All allocations are aligned to 8-byte boundaries:

c
size = (size + 7) & ~7;

This ensures compatibility with most data types and improves performance.

## Building

Compile using GCC:

bash
gcc allocator.c main.c -o allocator

Run:

bash
./allocator


## Example Output

---Allocator Test---
stored 25 at address 0x55...
[Alignment: OK]

stored vishesh at address 0x55...
[Alignment: OK]

stored 30 at address 0x55...

Memory reuse successful, both pointers are the same

allocated array of 5 integers at address 0x55...
arr[0] = 0
arr[1] = 0
arr[2] = 0
arr[3] = 0
arr[4] = 0

## API

### my_malloc

c
void* my_malloc(size_t size);

Allocates a memory block of the requested size.


### my_free

c
void my_free(void* ptr);

Marks a block as free and attempts to merge adjacent free blocks.

### my_calloc

c
void* my_calloc(size_t num, size_t size);

Allocates memory and initializes it to zero.

## Concepts Demonstrated

- Heap management
- Memory allocation internals
- Linked lists
- Block splitting
- Block coalescing
- Memory alignment
- System calls (`sbrk`)
- Dynamic memory management

## Limitations

This allocator is intended for educational purposes and lacks many features of production allocators:

- No thread safety
- No `realloc()` support
- No best-fit or segregated free lists
- No protection against invalid frees
- No heap shrinking

## Future Improvements

- Implement `realloc()`
- Add thread safety using mutexes
- Support heap contraction
- Implement best-fit allocation
- Add memory statistics
- Detect double-free errors
- Improve fragmentation handling


## Learning Outcomes

This project demonstrates the fundamental mechanisms behind dynamic memory allocation and provides hands-on experience with:

- Operating system memory management
- Low-level C programming
- Data structures
- Performance optimization techniques used by real allocators

## Author

**Vishesh Jain**

Custom memory allocator built as a systems programming project to understand how `malloc()` works internally.
