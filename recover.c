#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>
#include <ctype.h>

bool checkUsage(int inputStringLength, string inputStringVector[]);

bool endOfIputFile = false;
int elementSize = 512;
int numberOfElementsToRead = 1;
unsigned char processingBuffer[512];
int numberOfElementsSuccessfullyRead= -1;
///////////string recovered_img = "000.jpg";
char recovered_img[7];

// image output file name count
int image_count = -1;

int main(int argc, char *argv[])
{

// check for validity of the input
    if (!checkUsage(argc, argv))
    {
        //is the input is not valid
        printf("Usage: ./recover filename \n");
        exit(1);
    }
    else
    {
        // if the input is valid
        // open the input file
        FILE *f = fopen(argv[1], "r");
        FILE *outptr;
        int r1;
        
        while (!endOfIputFile)
        {
            //endOfIputFile = true;
            
            numberOfElementsSuccessfullyRead = fread(processingBuffer, elementSize, 1, f);
            if (numberOfElementsSuccessfullyRead > 0)
            {
                if ((processingBuffer[0] == 0xff) && (processingBuffer[1] == 0xd8) && (processingBuffer[2] == 0xff) 
                    && ((processingBuffer[3] & 0xf0) == 0xe0))
                {
                  
                    if (image_count > -1)
                    {
                        fclose(outptr);  
                    }
                   
                    image_count++;
                    sprintf(recovered_img, "%03i.jpg", image_count);
                    printf("%s", recovered_img);
                    outptr = fopen(recovered_img, "w");
                    r1 = fwrite(processingBuffer, 512, 1, outptr);
                }
                else
                {
                    if (image_count > -1)
                    { 
                        r1 = fwrite(processingBuffer, 512, 1, outptr);
                    }
                   
                }
      
            }
            else
            {
                endOfIputFile = true;
            }
            

        }  // end of  while
            
        
        
        fclose(f);
        
        
        
        
    }

}



// analyze user input for validity
bool checkUsage(int inputStringLength, string inputStringVector[])
{
    int j = 0;

    // did user type in the required number of arguments
    if (inputStringLength != 2)
    {
        return false;
    }


    // the user's input is valid
    return true;
}