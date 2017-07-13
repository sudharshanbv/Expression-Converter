

#include <stdio.h>
#include <Infix_Stack.h>

/*main function block*/
int main()
{

/*local variable declaration*/
char expression[100];

/*reading the expression from the user*/
printf("\nEnter the expression : ");
scanf("%s", expression);

/*calling the infix to postfix conversion function*/
infix_post_conversion(expression, 1);

}
