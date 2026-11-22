# include <stdio.h>

void a_double(int a)
{
		a = a * 2;
		printf("in the function a = %d\n",a);
}

void b_double(int *b)
{
		*b = (*b) * 2;
}

int abc(int a)
{
		a = a + 1;
		a = abc(a);
		return a;
}

int main()
{
		int a = 2;
		a_double(a);
		printf("a = %d\n",a);

		int b = 4;
		b_double(&b);
		printf("b = %d\n",b);
		int c = abc(1);
		printf("%d\n",c);
		//int *c;
		//*c = 12;

		//int arr[2] = {1,2};
		//arr[3] = 4;
		return 0;
}
