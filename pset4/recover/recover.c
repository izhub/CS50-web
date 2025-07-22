#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("file not found.\n");
        return 1;
    }

    int fr = 1, count = 0;
    FILE *img = NULL;

    while (fr != 0)
    {
        BYTE buffer[512];
        char filename[8] = "";
        fr = fread(buffer, 1, 512, file);

        //check start of new jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //if first jpg, start writing
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, fr, img);
                count++;
            }
            //if found one, close current file and open new file
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, fr, img);
                count++;
            }
        }
        //next block of current jpg, keep writing
        else
        {
            if (count > 0)
            {
                fwrite(buffer, 1, fr, img);
            }
        }
    }

    fclose(img);
    fclose(file);
    return 0;
}

/*
open memory card:
File *f = fopen(filename, "r"); //r = read

Read Files: fread( data, size, number, inptr);

making new jpeg:
filenames:  ###.jpg, starting at 000.jpg
sprintf(filename, "%0ei.jpg", 2);
File *img = fopen(filename, "w");

writing files:  fwrite( data, size, number, outptr);

jpeg?
buffer[0] == 0xff
buffer[1] == 0xd8
buffer[2] == 0xff
buffer[3] ==  0xe0 || 0xe1 || 0xe2 || ... 0xef or bitwise arithmatic - (buffer[3] && 0xf0) == 0xe0

*/