#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cs50.h>

typedef uint8_t byte;
int BLOCKSIZE = 512;
int BLOCKHEADERSIZE = 4;

int main(int argc, char *argv[])
{
    byte headerblocks[] = {0xff, 0xd8, 0xff};

    // validate input arguments
    if (argc != 2)
    {
        printf("Usage: ./recover imagefile\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    byte buffer[BLOCKSIZE];
    char filename[9];
    int n = 0, s = 0;
    bool m = false;
    FILE *img;

    while (fread(buffer, sizeof(byte), 512, file) == 512)
    {
        if (buffer[0] == 0xff  && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (m)
            {
                fclose(img);
            }

            s = true;

            sprintf(filename, "%03i.jpg", n);

            img = fopen(filename, "w");
            fwrite(buffer, sizeof(byte), 512, img);

            n++;

        }
        else
        {
            if (s == true)
            {
                fwrite(buffer, sizeof(byte), 512, img);
                m = true;
                continue;
            }
            else
            {
                continue;
            }
        }

    }
    if (m)
        {
            fclose(img);
        }

    fclose(file);
}

