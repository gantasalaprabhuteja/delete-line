#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1000

/* Function declarations */
void deleteLine(FILE *srcFile, FILE *tempFile, const int line);
void printFile(FILE *fptr);


int main(int argc, char* argv[])
{
    FILE *srcFile;
    FILE *tempFile;


    int line = atoi(argv[1]) ;

    

    /* Try to open file */
    srcFile  = fopen(argv[2], "r");
    tempFile = fopen("delete-line.tmp", "w");


    /* Exit if file not opened successfully */
    if (srcFile == NULL || tempFile == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");

        exit(EXIT_FAILURE);
    }



    printf("\nFile contents before removing line.\n\n");
    printFile(srcFile);


    // Move src file pointer to beginning
    rewind(srcFile);

    // Delete given line from file.
    deleteLine(srcFile, tempFile, line);


    /* Close all open files */
    fclose(srcFile);
    fclose(tempFile);


    /* Delete src file and rename temp file as src */
    remove(argv[2]);
    rename("delete-line.tmp", argv[2]);


    printf("\n\n\nFile contents after removing %d line.\n\n", line);

    // Open source file and print its contents
    srcFile = fopen(argv[2], "r");
    printFile(srcFile);
    fclose(srcFile);

    return 0;
}


/**
 * Print contents of a file.
 */
void printFile(FILE *fptr)
{
    char ch;

    while((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}



/**
 * Function to delete a given line from file.
 */
void deleteLine(FILE *srcFile, FILE *tempFile, const int line)
{
    char buffer[BUFFER_SIZE];
    int count = 1;

    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
    {
        /* If current line is not the line user wanted to remove */
        if (line != count)
            fputs(buffer, tempFile);

        count++;
    }
}
