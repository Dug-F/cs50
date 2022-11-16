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
    // validate input arguments
    if (argc != 2)
    {
        printf("Usage: ./recover imagefile\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    byte blockbuffer[BLOCKSIZE];
    char outfileName[8];
    int count = 0;
    FILE *outfile = NULL;

    while (fread(&blockbuffer, sizeof(byte), BLOCKSIZE, infile) == BLOCKSIZE)
    {
        // if jpg header block
        if (blockbuffer[0] == 0xff && blockbuffer[1] == 0xd8 && blockbuffer[2] == 0xff && (blockbuffer[3] & 0xf0) == 0xe0)
        {
            // close any existing image file
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            // compose new filename
            sprintf(outfileName, "%03i.jpg", count);
            // start new outfile
            outfile = fopen(outfileName, "w");
            fwrite(&blockbuffer, sizeof(byte), BLOCKSIZE, outfile);
            count ++;
        }
        else if (outfile != NULL)
        {
            // write any non-header blocks
            fwrite(&blockbuffer, sizeof(byte), BLOCKSIZE, outfile);
        }
    }

    // close last image file if any image files have been written
    if (outfile != NULL)
    {
        fclose(outfile);
    }
    fclose(infile);
}
