#ifndef STACK_HEADER 

    #define STACK_HEADER

    typedef struct stack {
        long top;
        long long* contents;
    } stack;

    void make_empty(stack *input_stack);
    int push(long long i, stack **input_stack);
    int pop(stack **input_stack);

#endif