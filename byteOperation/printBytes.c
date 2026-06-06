#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void printBytes(uint32_t hex)
{
    // Accessing hex address through byte by byte.
    unsigned char *ptr = (unsigned char *) &hex;
    for(int i=0; i<4; i++)
    {
        printf("Byte[%d] = 0x%x \n", i, ptr[i]);
    }
}

int main(int argc, char **argv)
{
    if(argc < 2) {
        printf("Invalid cmd line. Error!!\n");
        return -1;
    }
    uint32_t hex = 0;

    sscanf(argv[1], "%x", &hex);
    printBytes(hex);

    return 0;
}

# gcc printBytes.c -o bin
# ./bin <hex value>
# Example: ./bin 0x12345678
# Byte[0] = 0x78
# Byte[1] = 0x56
# Byte[2] = 0x34
# Byte[3] = 0x12
#
