#include <stdio.h>

int main(int argc, char *argv[])
{


  int i = 0;
  while(i < argc) {
    printf("arg %d: %s\n", i, argv[i]);
    i++;
		if(i > 3)
						break;
  }
	i--;
  while(i > 0) {
		printf("arg %d: %s\n", i, argv[i]);
		i--;
	}

  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };

  int num_states = 4;
  i = 0;  // watch for this
  while(i < num_states) {
  	printf("state %d: %s\n", i, states[i]);
  	i++;
  }
	int j = 0;
	while(j < argc && j < num_states)
	{
		states[j] = argv[j];
		j++;
	}
	j = 0;
	while(j < argc && j < num_states) {
    printf("state %d: %s\n", j, states[j]);
    j++;
  }

  return 0;
}
