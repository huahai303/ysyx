#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inttypes.h>

enum state
{
		first,
		second,
		third
};

void type_mem()
{
		printf("类型大小\n");
		printf("int:	%zu Byte\n",sizeof(int));
		printf("double:	%zu Byte\n",sizeof(double));
		printf("float:	%zu Byte\n",sizeof(float));
		printf("char:	%zu Byte\n",sizeof(char));
		printf("long:	%zu Byte\n",sizeof(long));
		printf("short:	%zu Byte\n",sizeof(short));
		printf("long long:	%zu Byte\n",sizeof(long long));
		printf("int8_t:		%zu Byte\n",sizeof(int8_t));
		printf("int32_t:	%zu Byte\n",sizeof(int32_t));
		int *p = NULL;
		printf("int *:		%zu Byte\n",sizeof(p));
		printf("intptr_t:	%zu Byte\n",sizeof(intptr_t));
		printf("ptrdiff_t:	%zu Byte\n",sizeof(ptrdiff_t));

}

void un_signed()
{
		printf("溢出和回绕\n");
		signed char s = 127;
	 	printf("signed s = %d\n",s);
		s = s + 1;
		printf("signed s + 1 = %d\n",s);
		unsigned char a = 255;
		printf("unsigned a = %d\n",a);
		a = a  + 1;
		printf("unsigned a + 1 = %d\n", a);
}

void int_max()
{
		printf("INT_MAX\n");
		int8_t a = INT8_MAX;
		printf("INT8_MAX =	%d\n",a);
		a = a + 1;
		printf("INT8_MAX+1 =	%d\n",a);
		uint8_t b = UINT8_MAX;
		printf("UINT8_MAX =	%d\n",b);
		b = b + 1;
		printf("UINT8_MAX+1 =	%d\n",b);
}

void int_type()
{
		printf("int_type\n");
		int_least8_t a = 100;
		int_least16_t b = 30000;

		printf("a = %"PRIdLEAST8"\n",a);
		printf("b = %"PRIdLEAST16"\n",b);

		printf("int_least8_t:	%zu Bytes\n",sizeof(int_least8_t));
		printf("int_least16_t:	%zu Bytes\n",sizeof(int_least16_t));

		printf("INT_LEAST8_MAX =	%"PRIdLEAST8"\n",INT_LEAST8_MAX);
		printf("UINT_LEAST16_MAX =	%"PRIdLEAST16"\n",UINT_LEAST16_MAX);

		printf("int_fast16_t:	%zu Bytes\n",sizeof(int_fast16_t));

		printf("INTPTR_MAX =  %"PRIdPTR"\n",INTPTR_MAX);
		printf("INTMAX_MAX =  %"PRIdMAX"\n",INTMAX_MAX);
		printf("UINTMAX_MAX =  %"PRIuMAX"\n",UINTMAX_MAX);
		printf("INTMAX_MIN =  %"PRIdMAX"\n",INTMAX_MIN);
}

void enum_use(int i)
{
		enum state status = i;
		switch(status)
		{
				case first:	
						printf("first 1\n");
						break;
				case second:
						printf("second 2\n");
						break;
				case third:
						printf("third 3\n");
						break;
				default:
						printf("it is default\n");
						break;
		}
}

void calculate(int x, int y)
{
		printf("x = %x、y = %x\n",x,y);
		printf("x+y =	%d\n",x+y);
		printf("-x =	%d\n",-x);
		printf("++x =	%d\n",++x);
		printf("x++ =	%d\n",x++);
		printf("x ? y : 0 =	%d\n",x ? y : 0);
		printf("x*y =	%d\n",x*y);
		printf("x/y =	%d\n",x/y);
		printf("--x = %d\n",--x);
		printf("x-- = %d\n",x--);

		printf("x != y:	%d\n",x != y);
		printf("x > y:	%d\n",x > y);
		printf("x & y = %x\n",x&y);
		printf("x << y = %x\n",x<<y);
		printf("x ^ y =	%x\n",x^y);
		printf("x | y =	%x\n",x|y);
		printf("~x =	%x\n",~x);

		printf("!1 = %d\n",!1);
		printf("1 && 0 = %d\n",1&&0);
		printf("1 || 0 = %d\n",1||0);

}

void cycle()
{
		int i = 0;
		do
		{
				i++;
				if(i == 2)  continue;
				printf("i = %d\n",i);
		}while(i < 5);
}

int main()
{
		type_mem();
		printf("\n");
		un_signed();
		printf("\n");
		printf("enum的使用\n");
		for(int i = 0; i < 4; i++)
				enum_use(i);
		printf("\n");
		int_max();
		printf("\n");
		int_type();
		printf("\n");
		calculate(10,2);
		printf("\n");
		cycle();
		return 0;
}
