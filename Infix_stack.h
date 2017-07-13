

#ifndef ARRAY_STACK
#define ARRAY_STACK

void post_evaluation(int *values, char *final, char *stack);

void pre_evaluation(int *values, char *final, char *stack);

void infix_post_conversion(char *expression, int op);

void infix_pre_conversion(char *expression);

void in_push(char *stack, int size, char val);

int in_is_full(int size);

void *in_pop(char *stack, char *val);

void *in_peak(char *stack, char *val);

void *in_peep(char *stack);


int in_is_empty();

#endif
