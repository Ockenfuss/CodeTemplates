


#include <stdlib.h>

#ifndef STACK_H
#define STACK_H
typedef struct point_t{
    int x;
    int y;
    int z;
    float cost;
}point_t;


typedef struct stack_t{
    point_t* points;
    int capacity;
    int size;
}stack_t;

size_t dist2(const point_t p1, const point_t p2);
stack_t create_stack(int capacity);
void destroy_stack(stack_t* stack);
void free_stack(stack_t* stack);
void stack_extend(stack_t* stack);
void stack_swap(stack_t* stack, size_t i, size_t j);
size_t get_child(size_t i, size_t child);
size_t get_parent(size_t i);
void sort_down(stack_t* stack, size_t pos);
void sort_up(stack_t* stack);
void stack_push(stack_t* stack, point_t point);
point_t stack_pop(stack_t* stack);
int stack_empty(const stack_t* stack);







#endif /*STACK_H*/