#include <stdio.h>
#include <stdlib.h>
#include "myFunctions.h"
/*
 * This is a file that will hopefully create an "All Red" plain pixel map .ppm file.
 * Using the c language. we will link this with a make file for fun
 *
 * Author : Willow McCulloch                                            Date: 10/6/2025
 */

int main(int argc,              //the number of commandline arguments
         char *argv[]){         //The vector of commandline argumnets.

        printf("======================================================\n");
        printf("   The program will generate a .ppm image for you     \n");
        printf("======================================================\n");

        /* The variable space is allocated at the start of each function. */

        int InOutFlag;
        int numRows;            // the number of rows in the image being created.
        int numCols;            // the number of cols in the image being created.
        int imageSize;          // the number of bits needed to store the iamge.
        int row, col;           // Pointers for where we are in the iamge.

        unsigned char *outImage;// Pointers for the pixels.
        unsigned char *ptr;     // Pointer
        FILE *outputFP;         // My out put file pointer


        printf("======================================================\n");
        printf("   Parsing the command line arguments                 \n");
        printf("======================================================\n");

        if(argc != 4){
                printf("Usage: AllRed OutFile numRows numCols\n");
                exit(1);
        }

        if((numRows = atoi(argv[2])) <= 0){
                printf("The given number of rows is negative!\n");
                exit(2);
        }
        if((numCols = atoi(argv[3])) <= 0){
                printf("The given number of Cols is negative!\n");
                exit(2);
        }

        printf("======================================================\n");
        printf("   Setting up the output file and image size          \n");
        printf("======================================================\n");

        imageSize = numRows*numCols*3;                  // See how big things will get
        outImage = (unsigned char *) malloc(imageSize);

        /* Open the .ppm file for the iamge. */

        if ( (outputFP = fopen(argv[1], "w")) == NULL){
                perror("Output file pointer error");
                printf("Error opening file for output!\n");
                exit(3);
        }

        printf("======================================================\n");
        printf("   Loop Across all pixels arcoss the image            \n");
        printf("======================================================\n");

        ptr = outImage;
        for( row = 0; row < numRows; row++ ){
                for(col = 0; col < numCols; col++){
                        // Call the Function
                        InOutFlag = CheckRadius(numRows, numCols, 10, row, col);
                        if(row < numRows/2){
                                *ptr            = 255;  // Red Pixel
                                *(ptr+1)        = 0;    // the green pixel
                                *(ptr+2)        = 0;    // the blue pixel
                        }
                        else {
                                *ptr            = 255;  // Red Pixel
                                *(ptr+1)        = 0;    // the green pixel
                                *(ptr+2)        = 255;  // the blue pixel
                        }
                        // Advance the pointer
                        ptr +=3;
                }
        }

        // Write the image.
        fprintf(outputFP, "P6 %d %d 255\n", numCols, numRows);
        fwrite(outImage, 1, imageSize, outputFP);

        fclose(outputFP);



        return 0;
}