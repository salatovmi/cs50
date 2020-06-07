#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please enter only file name!\n");
        return 1;
    }

    FILE *rec = fopen(argv[1], "r");
    if (rec == NULL)
    {
        printf("File doesn't exist or couldn't be opened\n");
        return 1;
    }

    BYTE jpeg[3] = {0xff, 0xd8, 0xff};
    int jp = 14;

    fseek(rec, 0, SEEK_END);
    long size = ftell(rec);
    fseek(rec, 0, SEEK_SET);

    int name = 0;
    char filename[8];
    sprintf(filename, "%03i.jpg", name);
    FILE *img = NULL;

    while (!feof(rec))
    {
        int sss;
        if (size - ftell(rec) >= 512)
        {
            sss = 512;
        }
        else 
        {
            sss = size - ftell(rec);
            BYTE buffer[sss];
            size_t read = fread(buffer, sizeof(BYTE), sss, rec);
            fwrite(buffer, sizeof(BYTE), read, img);
            break;
        }
        BYTE buffer[sss];
        fread(buffer, sizeof(BYTE), sss, rec);
        BYTE fourth = buffer[3] >> 4;
        bool new_file = buffer[0] == jpeg[0] && buffer[1] == jpeg[1] && buffer[2] == jpeg[2] && fourth == 14;
        if (new_file && img == NULL)
        {
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), sss, img);
            name++;
        }
        else if (new_file && img != NULL)
        {
            fclose(img);
            sprintf(filename, "%03i.jpg", name);
            img = fopen(filename, "w");
            fwrite(buffer, sizeof(BYTE), sss, img);
            name++;
        }
        else if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), sss, img);
        }
    }
    fclose(img);
    fclose(rec);
}