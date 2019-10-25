#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Stack.h"


stack_t create_stack(int capacity)
{
    stack_t stack_t;
    stack_t.capacity=capacity;
    stack_t.size=0;
    stack_t.points=malloc(stack_t.capacity*sizeof(point_t));
    return stack_t;
}

size_t dist2(const point_t p1, const point_t p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z);
}

void destroy_stack(stack_t* stack)
{
    free(stack->points);
}

void free_stack(stack_t* stack)
{
    free(stack->points);
}

void stack_extend(stack_t* stack)
{
    assert(stack->capacity==stack->size);
    point_t* new_points=malloc(stack->capacity*2*sizeof(point_t));
    for (size_t i = 0; i < stack->size; i++)
    {
        new_points[i]=stack->points[i];
    }
    free(stack->points);
    stack->points=new_points;
    stack->capacity*=2;
}

void stack_swap(stack_t* stack, size_t i, size_t j)
{
    point_t dummy=stack->points[i];
    stack->points[i]=stack->points[j];
    stack->points[j]=dummy;
}
size_t get_child(size_t i, size_t child)
{
    return 2*i+1+child;//child: 0 or 1
}

size_t get_parent(size_t i)
{
    return (size_t)((i-1)/2);
}


void sort_down(stack_t* stack, size_t pos)
{
    size_t child=get_child(pos,0);
    size_t min_child;
    while(child<stack->size)
    {
        min_child=child;
        if((child+1)<stack->size)//if second child exists
        {
            if(stack->points[child+1].cost<stack->points[child].cost)//if second child is cheaper
            {
                min_child++;
            }
        }
        if(stack->points[min_child].cost<stack->points[pos].cost)
        {
            stack_swap(stack, pos,min_child);
        }
        else
        {
            break;
        }
        pos=min_child;
        child=get_child(pos,0);
    }
}

void sort_up(stack_t* stack)
{
    size_t pos=stack->size-1;
    size_t parent;
    while(pos!=0)
    {
        parent=get_parent(pos);
        if(stack->points[pos].cost<stack->points[parent].cost)
        {
            stack_swap(stack, parent, pos);
            pos=parent;
        }
        else
        {
            break;
        }
    }
}

void stack_push(stack_t* stack, point_t point)
{
    if(stack->size==stack->capacity)
    {
        stack_extend(stack);
    }
    stack->points[stack->size]=point;
    stack->size++;
    sort_up(stack);
}


point_t stack_pop(stack_t* stack)
{
    point_t p= stack->points[0];
    stack->points[0]=stack->points[stack->size-1];
    stack->size--;
    sort_down(stack, 0);
    return p;
}

int stack_empty(const stack_t* stack)
{
    return stack->size==0;
}


// int main()
// {
//     stack_t stack=create_stack(2);
//     point_t p = {10, 20, 30,4.0};
//     point_t p1 = {10, 20, 30,3.0};
//     point_t p2 = {10, 20, 30,1.0};
//     stack_push(&stack, p);
//     stack_push(&stack, p1);
//     stack_push(&stack, p2);
//     point_t p_return=stack_pop(&stack);
//     printf("%.4f\n", p_return.cost);
//     p_return=stack_pop(&stack);
//     printf("%.4f\n", p_return.cost);
//     p_return=stack_pop(&stack);
//     printf("%.4f\n", p_return.cost);
//     destroy_stack(&stack);
// }