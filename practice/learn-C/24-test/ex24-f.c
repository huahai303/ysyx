#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(const char *filename, char *buffer, size_t max_size)
{
		if(buffer == NULL || max_size == 0)
				return -1;
		FILE *fp = fopen(filename,"r");
		if(fp == NULL)
		{
				perror("fail to open file");
				return -1;
		}
		size_t i = 0;
		char ch;
		while(i < max_size - 1 && fscanf(fp, "%c", &ch) == 1)
		{
				buffer[i] = ch;
				i++;
		}
		buffer[i] = '\0';
		fclose(fp);
		return i;
}

int main()
{
		const char *test_file = "test_data.txt";

		FILE *fp = fopen(test_file,"w");
		if(fp != NULL)
		{
				fprintf(fp,"hello world.\nhello C.\n");
				fclose(fp);
				printf("test file: %s\n",test_file);
		}
		else
		{
				printf("can not create test file\n");
				return 1;
		}
		char buffer[10];
		int count = read_file(test_file,buffer,sizeof(buffer));
		if(count >= 0)
		{
				printf("there are %d characters\n",count);
				printf("%s\n",buffer);
		}
		else
				printf("can not read file");
		return 0;
}
