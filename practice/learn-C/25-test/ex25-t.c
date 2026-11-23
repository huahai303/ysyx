#include <stdio.h>
#include <stdarg.h>

void my_print(const char *format, ...)
{
		va_list argp;
		va_start(argp, format);
		while(*format != '\0')
		{
				if(*format == '%')
				{
						format++;
						switch(*format)
						{
								case 'd':
												{
														int i = va_arg(argp, int);
														printf("%d",i);
														break;
												}
								case 'c':
												{
														int c = va_arg(argp, int);
														putchar(c);
														break;
												}
								case 's':
												{
														char *s = va_arg(argp, char *);
														fputs(s, stdout);
														break;
												}
								case 'f':
												{
														double d = va_arg(argp, double);
														printf("%f",d);
														break;
												}
								case '%':
												{
														putchar('%');
														break;
												}
								default:
												{
														putchar('%');
														putchar(*format);
														break;
												}
						}
				}
				else
						putchar(*format);
				format++;
		}
		va_end(argp);
}

int main() {
    int age = 25;
    char grade = 'A';
    char *name = "Alice";
    double score = 98.5;

    printf("--- 使用系统原生 printf ---\n");
    printf("Name: %s, Age: %d, Grade: %c, Score: %f\n", name, age, grade, score);

    printf("\n--- 使用我们自定义的 my_printf ---\n");
    my_print("Name: %s, Age: %d, Grade: %c, Score: %f\n", name, age, grade, score);
    
    my_print("进度: %d%% 完成！\n", 100); // 测试百分号

    return 0;
}
