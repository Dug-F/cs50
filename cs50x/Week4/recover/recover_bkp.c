#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <cs50.h>

typedef uint8_t byte;
int BLOCKSIZE = 512;
int BLOCKHEADERSIZE = 4;

// function prototypes
bool checkJpegHeader(int buffersize, byte blockbuffer[BLOCKSIZE], byte headerblocks[BLOCKHEADERSIZE]);

int main(int argc, char *argv[])
{
    byte headerblocks[] = {0xff, 0xd8, 0xff};

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
    char outfileName[9];
    int count = 0;
    bool writingOutfile = false, isJpegHeader = false;
    FILE *outfile;

    while (fread(&blockbuffer, sizeof(byte), BLOCKSIZE, infile) == BLOCKSIZE)
    {
        isJpegHeader = checkJpegHeader(BLOCKSIZE, blockbuffer, headerblocks);

        // write block if outfile currently being written
        if (writingOutfile)
        {
            fwrite(&blockbuffer, sizeof(byte), BLOCKSIZE, outfile);
            if (isJpegHeader)
            {
                fclose(outfile);
            }
        }

        if (isJpegHeader)
        {
            // compose new filename
            sprintf(outfileName, "%03i.jpg", count);
            puts(outfileName);

            // start new outfile
            outfile = fopen(outfileName, "w");
            fwrite(&blockbuffer, sizeof(byte), BLOCKSIZE, outfile);
            writingOutfile = true;

            count++;
        }
    }

    // close outfile if still in process of writing (for last image)
    if (writingOutfile)
    {
        fclose(outfile);
    }
    fclose(infile);
}

bool checkJpegHeader(int buffersize, byte blockbuffer[BLOCKSIZE], byte headerblocks[BLOCKHEADERSIZE])
{
    // validate if first bytes of buffer match a jpeg header
    if (buffersize < BLOCKHEADERSIZE)
    {
        return 0;
    }

    // first bytes are fixed
    for (int i = 0; i < BLOCKHEADERSIZE - 1; i++)
    {
        if (blockbuffer[i] != headerblocks[i])
        {
            return 0;
        }
    }

    // final byte only need to check top 3 bits
    if (blockbuffer[BLOCKHEADERSIZE - 1] & (0<<7) || blockbuffer[BLOCKHEADERSIZE -1 ] & (0<<6) || blockbuffer[BLOCKHEADERSIZE - 1] & (0<<5))
    {
        return 0;
    }

    return 1;
}