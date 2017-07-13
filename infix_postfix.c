
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Infix_Stack.h>

/*global variable declaration*/
static int top;
int sidx;
/*-----------------------------------------------------------------------------------------------------------------------*/

/*infix to prefix conversion block*/
void infix_pre_conversion(char *expression)
{

	/*local varaible declaration*/
	char ch;
	int idx_1 = 0, idx_2;

	idx_2 = strlen(expression);

	idx_2 = idx_2 - 1;

	char expression_copy[100];

	/*initializing the array with null*/
	memset(expression_copy, '\0', sizeof(expression_copy));

	/*copying the expression in reverse order*/
	while (idx_2 >= 0)
	{
		expression_copy[idx_1] = expression[idx_2];
		++idx_1;
		--idx_2;
	}

	idx_1 = 0;

	int flag1 = 0, flag2 = 0, str, end;
	char tmp;

	/*reverse the multi digit numbers and open and close braces*/
	while (expression_copy[idx_1] != '\0')
	{
		flag2 = 0;

		if (expression_copy[idx_1] != '+' && expression_copy[idx_1] != '%' && expression_copy[idx_1]  != '-' && expression_copy[idx_1]  != '/' && expression_copy[idx_1] != '*' &&  expression_copy[idx_1] != '(' && expression_copy[idx_1]  != ')')
		{
			if (flag1 == 0)
			{
				str = idx_1;
			}

			++flag1;
		}

		else if (expression_copy[idx_1] == '(')
		{
			expression_copy[idx_1] = ')';
			++flag2;

			if (flag1 == 1)
				flag1 = 0;
		}

		else if (expression_copy[idx_1] == ')')
		{
			expression_copy[idx_1] = '(';
			++flag2;

			if (flag1 == 1)
				flag1 = 0;
		}
		else
		{
			++flag2;

			if (flag1 == 1)
				flag1 = 0;
		}

		if (flag1 > 1 && flag2 == 1)
		{

			end = idx_1 - 1;

			while (str < end)
			{

				tmp = expression_copy[str];
				expression_copy[str] = expression_copy[end];
				expression_copy[end] = tmp;

				++str;
				--end;
			}

			flag1 = 0;
		}

		++idx_1;
	}

	if (flag1 > 1)
	{

		end = idx_1 - 1;

		while (str < end)
		{

			tmp = expression_copy[str];
			expression_copy[str] = expression_copy[end];
			expression_copy[end] = tmp;

			++str;
			--end;
		}

	}

	/*calling the infix to postfix conversion function*/
	infix_post_conversion(expression_copy, 2);

}

/*-----------------------------------------------------------------------------------------------------------------------*/

/*infix to postfix conversion block*/
void infix_post_conversion(char *expression, int op)
{

	/*local variable declaration*/
	int values[100];
	char final[100];

	/*initializing the array final with null*/
	memset(final, '\0', sizeof(final));

	char *stack = malloc(50 * sizeof (char));
	char dummy;
	int tmp, idx;

	int eidx = 0, sum = 0, vidx = 0, fidx = 0;

	while (expression[eidx] != '\0')
	{

		if (expression[eidx] != '+' && expression[eidx] != '%' && expression[eidx] != '-' && expression[eidx] != '/' && expression[eidx] != '*' && expression[eidx] != '(' && expression[eidx] != ')')

		{
			sum = (sum * 10) + (expression[eidx] - 48);
			++eidx;
			continue;
		}

		if (sum != 0)
		{
			values[vidx] = sum;
			final[fidx] = vidx + 48;
			++vidx;
			sum = 0;
			++fidx;
		}


		if ((top == 0) || (expression[eidx] == '(')) 
		{
			in_push(stack, 50, expression[eidx]);
		}

		else
		{

			if (expression[eidx] == '+' || expression[eidx] == '-')
			{

				if (stack[sidx - 1] != '(' )
				{
					while ((top != 0) && (stack[top - 1] != '('))
					{
						in_pop(stack, &final[fidx]);
						++fidx;
					}
					in_push(stack, 50, expression[eidx]);
				}


				else if (stack[sidx - 1] == '(' )
				{
					in_push(stack, 50, expression[eidx]);
				}

			}


			else if (expression[eidx] == '*' || expression[eidx] == '/' || expression[eidx] == '%')
			{

				if (op == 1)
				{
					if (stack[sidx - 1] == '*' || stack[sidx - 1] == '/' || stack[sidx - 1] == '%')
					{
						while ((top != 0) && (stack[top - 1] != '(') && (stack[top - 1] != '+') && (stack[top - 1] != '-'))
						{
							in_pop(stack, &final[fidx]);
							++fidx;
						}
						in_push(stack, 50, expression[eidx]);
					}
					else if (stack[sidx - 1] == '(' || stack[sidx - 1] == '+' || stack[sidx - 1] == '-')
					{
						in_push(stack, 50, expression[eidx]);
					}
				}

				if (op == 2)
				{ 
					in_push(stack, 50, expression[eidx]);
				}

			}

			else if (expression[eidx] == ')')
			{
				while (stack[top - 1] != '(')
				{
					in_pop(stack, &final[fidx]);
					++fidx;
				}

				in_pop(stack, &dummy);
			}
		}
		++eidx;
	}


	if (sum != 0)
	{
		values[vidx] = sum;
		final[fidx] = vidx + 48;
		++vidx;
		sum = 0;
		++fidx;
	}

	while(top != 0)
	{
		in_pop(stack, &final[fidx]);
		++fidx;
	}



	if (op == 1)
		post_evaluation(values, final, stack);

	else
		pre_evaluation(values, final, stack);


}
/*--------------------------------------------------------------------------------------------------------------------*/

/*pre evaluation function block*/
void pre_evaluation(int *values, char *final, char *stack)
{

	/*local variable declaration*/
	top = 0;
	int fidx = 0, result, tmp;
	char idx_a, idx_b, ch;

	tmp = strlen(final);
	--tmp;

	while (tmp != fidx)
	{
		ch = final[fidx];
		final[fidx] = final[tmp];
		final[tmp] = ch;
		--tmp;
		++fidx;

	}
	int idx = 0;

	/*printing the expression*/
	printf("\nExpression\n\n");
	while (final[idx] != '\0')
	{

		if (final[idx] == '+' || final[idx] == '-' || final[idx] == '/' || final[idx] == '*' || final[idx] == '%' )
		{
			printf("%c", final[idx]);
		}

		else
		{
			printf("%d", values[final[idx] - 48]);
		}
		++idx;
	}
	printf("\n\n");

	fidx = strlen(final);
	--fidx;

	while (fidx >= 0)
	{

		if (final[fidx] == '+')
		{
			in_pop(stack, &idx_a);
			in_pop(stack, &idx_b);
			values[idx_a - 48] = values[idx_a - 48] + values[idx_b - 48];
			in_push(stack, 50, idx_a);
			--fidx;
		}

		else if (final[fidx] == '-')
		{
			in_pop(stack, &idx_a);
			in_pop(stack, &idx_b);
			values[idx_a - 48] = values[idx_a - 48] - values[idx_b - 48];
			in_push(stack, 50, idx_a);
			--fidx;

		}

		else if (final[fidx] == '%')
		{
			in_pop(stack, &idx_a);
			in_pop(stack, &idx_b);
			values[idx_a - 48] = values[idx_a - 48] % values[idx_b - 48];
			in_push(stack, 50, idx_a);
			--fidx;

		}

		else if (final[fidx] == '/')
		{
			in_pop(stack, &idx_a);
			in_pop(stack, &idx_b);
			values[idx_a - 48] = values[idx_a - 48] / values[idx_b - 48];
			in_push(stack, 50, idx_a);
			--fidx;

		}

		else if (final[fidx] == '*')
		{
			in_pop(stack, &idx_a);
			in_pop(stack, &idx_b);
			values[idx_a - 48] = values[idx_a - 48] * values[idx_b - 48];
			in_push(stack, 50, idx_a);
			--fidx;

		}

		else
		{
			in_push(stack, 50, final[fidx]);
			--fidx;
		}

	}

	in_pop(stack, &idx_a);
	printf("\nResult  = %d\n", values[idx_a - 48]);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------------*/
/*post evaluation function block*/
void post_evaluation(int *values, char *final, char *stack)
{

	/*local variable declaration*/
	top = 0;
	int fidx = 0, result;
	char idx_a, idx_b;


	while (final[fidx] != '\0')
	{

		/*if the character is '+'*/
		if (final[fidx] == '+')
		{
			in_pop(stack, &idx_b);
			in_pop(stack, &idx_a);
			values[idx_a - 48] = values[idx_a - 48] + values[idx_b - 48];
			in_push(stack, 50, idx_a);
			++fidx;
		}

		/*if the character is '-'*/
		else if (final[fidx] == '-')
		{
			in_pop(stack, &idx_b);
			in_pop(stack, &idx_a);
			values[idx_a - 48] = values[idx_a - 48] - values[idx_b - 48];
			in_push(stack, 50, idx_a);
			++fidx;

		}

		/*if the character is '%'*/
		else if (final[fidx] == '%')
		{
			in_pop(stack, &idx_b);
			in_pop(stack, &idx_a);
			values[idx_a - 48] = values[idx_a - 48] % values[idx_b - 48];
			in_push(stack, 50, idx_a);
			++fidx;

		}

		/*if the character is '/'*/
		else if (final[fidx] == '/')
		{
			in_pop(stack, &idx_b);
			in_pop(stack, &idx_a);
			values[idx_a - 48] = values[idx_a - 48] / values[idx_b - 48];
			in_push(stack, 50, idx_a);
			++fidx;

		}

		/*if the character is '*'*/
		else if (final[fidx] == '*')
		{
			in_pop(stack, &idx_b);
			in_pop(stack, &idx_a);
			values[idx_a - 48] = values[idx_a - 48] * values[idx_b - 48];
			in_push(stack, 50, idx_a);
			++fidx;

		}

		else
		{
			in_push(stack, 50, final[fidx]);
			++fidx;
		}

	}

	in_pop(stack, &idx_a);
	printf("\nResult  = %d\n", values[idx_a - 48]);
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*peep function block*/
void *in_peep(char *stack)
{

	/*local variable declaration*/
	int tmp = top;

	/*check if stack is empty*/
	if (in_is_empty())
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
void *in_peak(char *stack, char *val)
{

	/*check if stack is empty*/
	if (in_is_empty())
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
void in_push(char *stack, int size, char val)
{

	/*check if stack is full*/
	if (in_is_full(size))
	{
		printf("\nStack is Full\n");
	}

	else
	{
		stack[top++] = val;
		sidx = top;
	}

}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*is full function block*/
int in_is_full(int size)
{
	if (top == size)
		return 1;

	else
		return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*pop function block*/
void *in_pop(char *stack, char *val)
{

	/*check if stack is empty*/
	if (in_is_empty())
	{
		printf("\nStack is Empty\n");
		return NULL;
	}

	else
		*val =  stack[--top];
	sidx = top;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
/*is empty function block*/
int in_is_empty()
{
	if (top == 0)
		return 1;

	else
		return 0;
}

/*-----------------------------------------------------------------------------------------------------------------------*/
