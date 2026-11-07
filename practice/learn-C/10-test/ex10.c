#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;
  for(i = 0; i < argc; i++) 
	{
    printf("arg %d: %s\n", i, argv[i]);
		if(argc > 5)
						break;
  }
  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };
  int num_states = 4;
  for(i = 0; i < num_states; i++)
 	{
    printf("state %d: %s\n", i, states[i]);
  }
	char *house = argv[1];
	argv[1] = states[1];
	states[1] = house;
	printf("argv[1]:%s, states[1]:%s\n",argv[1],states[1]);
	return 0;
}
