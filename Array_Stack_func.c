
#include <stdio.h>
#include <Array_Stack.h>

/*global variable declaration*/
static int top;

/*-----------------------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------------------------------------*/
/*peep function block*/
void *peep(int *stack)
{

	/*local variable declaration*/
	int tmp = top;

	/*check if stack is empty*/
	if (is_empty())
	{
		printf("\nStack is Empty\n");
		return NULL;
	}

	/*if stack is not empty*/
	else
	{
		printf("\n");
		while (tmp > 0)
		{
			printf("%d\t", stack[--tmp]);
		}
		printf("\n\n");
	}
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*peak function block*/
void *peak(int *stack, int *val)
{

	/*check if stack is empty*/
	if (is_empty())
	{
		printf("\nStack is Empty\n");
		return NULL;
	}

	/*if stack is not empty*/
	else
		*val = stack[top - 1];

}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*push function block*/
void push(int *stack, int size, int val)
{

	/*check if stack is full*/
	if (is_full(size))
	{
		printf("\nStack is Full\n");
	}

	else
	{
		stack[top++] = val;
	}

}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*is full function block*/
int is_full(int size)
{
	if (top == size)
		return 1;

	else
		return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*pop function block*/
void *pop(int *stack, int *val)
{

	/*check if stack is empty*/
	if (is_empty())
	{
		printf("\nStack is Empty\n");
		return NULL;
	}

	else
		*val =  stack[--top];
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*is empty function block*/
int is_empty()
{
	if (top == 0)
		return 1;

	else
		return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
