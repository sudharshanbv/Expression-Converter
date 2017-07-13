

#include <stdio.h>
#include <Infix_Stack.h>

/*main function block*/
int main()
{

	/*local variable declaration*/
	char expression[100];
	char ch;
	do
	{
		/*reading the expression from the user*/
		printf("\nEnter the expression : ");
		scanf("%s", expression);

		/*calling the infix to prefix to conversion function*/
		infix_pre_conversion(expression);

		printf("\nDo you want to continue?(y/n)\n\nEnter your choice : ");
		scanf("\n%c", &ch);
	} while (ch == 'y' || ch == 'Y');
}
