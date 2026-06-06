#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// Rotate a single byte to left
uint32_t rotateLeft(uint32_t hex) {
	return ((hex >> 24) | (hex << 8));
}

// Rotate a single byte to right
uint32_t rotateRight(uint32_t hex) {
    return ((hex <<24) | (hex >>8));
}

// Convert the string into lower case
void convertTosmaller(char *mode) {
    int i = 0;
    while(mode[i] != '\0')
    {
        if(mode[i] >= 'A' && mode[i] <= 'Z')
            mode[i] = mode[i] + 32;

        i++;
    }
}

int main()
{
    uint32_t hex = 0x0;
    char shiftMode[8] = {0};
    int isRight = 0;
    printf("Enter your hex value:");
    scanf("%x", &hex);
    while(1) {
        printf("Enter shift mode to rotate 0x%x byte: {Right or Left}:", hex);
        memset(shiftMode, 0, sizeof(shiftMode));
        scanf("%8s", shiftMode);
        convertTosmaller(shiftMode);
        if(strcmp(shiftMode, "right") == 0)
            isRight = 1;
        else if (strcmp(shiftMode, "left") == 0)
            isRight = 0;
        else
            isRight = -1;

        switch(isRight) {
            case 1:
            {
                hex = rotateRight(hex);
                printf("RightShift ==> 0x%x\n", hex);
                break;
            }
            case 0:
            {
                hex = rotateLeft(hex);
                printf("LeftShift ==> 0x%x\n", hex);
                break;
            }
            default:
                printf("\nExit the program!\n");
                exit(0);
        }
    }
    return 0;
}
