#include<stdio.h>

int main(int argc, char *argv[])
{
	char **cur_argc = argv;
	int i = 0;
	for(i = 1; i < argc; i++)
	{
		printf("%d:%s\n",i,*(cur_argc + i));
	}
	printf("%d\n",*&i);
	return 0;
}
