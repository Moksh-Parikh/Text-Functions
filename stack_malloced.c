#include <stdio.h>
#include <stdlib.h>

#include "malloced_stack_variables.h"

#define DEBUG   0

// Always empty the stack at the end of a program using make_empty()
// empty the stack
void make_empty(stack *input_stack) {
    input_stack->top = 0;
    free(input_stack->contents);
}


// Always empty the stack at the end of a program using make_empty()
// put a value at the top of the stack
int push(long long i, stack **input_stack) {
    #if DEBUG
    printf("Size from function: %d\n", sizeof((*input_stack)->contents));
    
    printf("Old pointer->%p\n", (*input_stack)->contents);
    
    #endif

    if ((*input_stack)->top < 0) {  // ensure top is valid
        fprintf(stderr, "Error in push(): Top is less than zero\nTop is %d\n", (*input_stack)->top);
        
        return -1;
    }
    else {
        if ((*input_stack)->top) {

            #if DEBUG
            
            printf("First val: %lld\n", (*input_stack)->contents[0]);

            #endif
            
            (*input_stack)->contents = (long long*) realloc((*input_stack)->contents, ((sizeof(long long) * (*input_stack)->top) + sizeof(long long)));
            
            if ((*input_stack)->contents == NULL) {
                fprintf(stderr, "Error in push(): realloc() failed to return a value\n");
            
                return -1;
            }

            #if DEBUG

            printf("New pointer->%p\n", (*input_stack)->contents);

            #endif

            (*input_stack)->contents[(*input_stack)->top++] = i;
        }
        else if (!((*input_stack)->top)) {
            (*input_stack)->contents = (long long*) malloc(sizeof(long long));

            if ((*input_stack)->contents == NULL) {
                fprintf(stderr, "Error in push(): malloc() failed to return a value\n");

                return -1;
            }

            #if DEBUG
            
            printf("New pointer->%p\n", (*input_stack)->contents);

            #endif

            (*input_stack)->contents[(*input_stack)->top++] = i;
        }
        else {
            fprintf(stderr, "Error in push(): IDFK bro\n");
        }

        return (*input_stack)->top;
    }
}


// Always empty the stack at the end of a program using make_empty()
// take a value from the top of the stack
int pop(stack **input_stack) { // pointer to the stack variable

    (*input_stack)->top = ((*input_stack)->top - 1) < 0 ? -1 : (*input_stack)->top - 1;

    if ((*input_stack)->top >= 0) {
        
        (*input_stack)->contents = (long long*) realloc((*input_stack)->contents, (((*input_stack)->top+1) * sizeof(long long)));
        
        if ((*input_stack)->contents == NULL) {
            fprintf(stderr, "Error in pop(): realloc() failed to return a value\n");

            return -1;
        }
        
        return (*input_stack)->contents[(*input_stack)->top];
    }
    else {
        fprintf(stderr, "Error in pop(): Top is less than zero\nTop is %d\n", (*input_stack)->top);
        
        return -1;
    }
}
