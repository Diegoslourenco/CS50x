#include <stdio.h>
#include <stdlib.h>

#define BYTES 512

int main(int argc, char *argv[])
{
    // Ensure put 2 arguments
    if (argc != 2)
    {
        printf("Insert only the file's name!");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    // Defining the variables
    unsigned char buffer[BYTES];
    char fileName[8];
    int fileNameCount = 0;
    FILE *image = NULL;

    // Reading 512 bytes until the end of the card

    while (fread(buffer, BYTES, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (fileNameCount != 0)
            {

                fclose(image);
            }

            sprintf(fileName, "%03i.jpg", fileNameCount);
            image = fopen(fileName, "w");
            fwrite(buffer, BYTES, 1, image);
            fileNameCount++;
        }
        else if (fileNameCount != 0)
        {
            fwrite(buffer, BYTES, 1, image);
        }
    }

    fclose(file);
    fclose(image);
    return 0;
}