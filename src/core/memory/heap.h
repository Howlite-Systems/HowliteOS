#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct heap_segment heap_segment_t;
struct heap_segment
{
    size_t length;
    heap_segment_t* next;
    heap_segment_t* last;
    bool free;
};

void segment_combine_forward(heap_segment_t seg);
void segment_combine_backward(heap_segment_t seg);
heap_segment_t* segment_split(heap_segment_t seg, size_t len);

void heap_init(void* heap_adr, size_t page_count);
void heap_expand(size_t len);

void* malloc(size_t size);
void free(void* address);