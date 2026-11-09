#include <stdio.h>

int main(int argc, char *argv[])
{
    /*if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }*/

    int i = 0;
		int j = 0;
    char letter;
		for(j = 1; j < argc; j++)
		{
    	for(i = 0, letter = argv[j][0]; argv[j][i] != '\0'; i++, letter = argv[j][i]) {
        //char letter = argv[1][i];
        if(letter >= 'A' && letter <= 'Z')
								letter = letter + 'a' - 'A';
				switch(letter) {
            case 'a':									//if(letter == 'a')
                printf("%d: 'A'\n", i);
                break;

            case 'e':									//else if(letter == 'e')
                printf("%d: 'E'\n", i);
                break;

            case 'i':									//else if(letter =='i')
                printf("%d: 'I'\n", i);
                break;

            case 'o':									//o
                printf("%d: 'O'\n", i);
                break;

            case 'u':									//u
                printf("%d: 'U'\n", i);
                break;

            case 'y':									//else if(letter == 'y' && i > 2)
                if(i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }
                break;

            default:									//else
                printf("%d: %c is not a vowel\n", i, letter);
				}
			}
		}

    return 0;
}
