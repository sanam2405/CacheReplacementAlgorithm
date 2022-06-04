/*

Team 18
1. Shubham Paul             002011001071(A2)
2. Dibyabrata Panja         002011001028(A1)
3. Manas Pratim Biswas      002011001025(A1)
4. Md Bosirullah Mondal     002011001030(A1)

/*

In this assignment, we have implemented the FIFO and the LRU Cache Replacement algorithm.

We have implemented FIFO using the concept of a circular queue using a 1-D array where we 
are inserting with the help of a pointer (currentInsertionIdx) whenever there is a miss. 

We have implemented LRU using a 1-D array by shifting all the elements  behing by one place 
and then pushing the current reference at the front of the array whenever there is a miss.
In case of a hit, we do the same shifting process and then push the current reference at the
front of the array, because it is the most recently used irrespective of a miss or hit.

In both FIFO and LRU, we are cheking if the current reference is present or not by perfoming 
a LINEAR SEARCH in O(n) time

Suppose M = cacheSize and N = totalReferences,

FIFO
Time Complexity : O(M*N)
Space Complexity : O(M)

LRU
Time Complexity : O(M*N)
Space Complexity : O(M)

*/

/*

    Compilation Command :  gcc 18_1.c
    Execution Command : ./18_1.exe [cacheSize mainMemorySize Algorithm References........]

*/

/*

Sample Input 1 : 8 32 L 1 2 3 4 5 6 1 7 8 9 10 1 6 5 9 11
Sample Output 1 : The Hit Ratio for LRU is : 5/16 = 0.31

Sample Input 2 : 8 32 F 1 2 3 4 5 6 1 7 8 9 10 1 6 5 9 11
Sample Output 2 : The Hit Ratio for FIFO is : 4/16 = 0.25

Sample Input 3 : 16 32 F 1 2 3 2 4 5 1 3 2 6 7 4 3 5 1 4
Sample Output 3: Size of cache should be less than 1/4th of the size of main memory!

Sample Input 4 : 8 32 L 1 2 3 2 4 5 0 3 -2 6 7 4 3 5 1 4
Sample Output 4: The references are not valid!

*/

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global Variable Declaration
int totalReferences;  // number of references
int cacheSize;        // size of the cache
int mainMemorySize;   // size of the main memory
char algorithm;       // choice of the algorithm
int *references;      // array to store references
int hits;             // number of hits
double cacheHitRatio; // stores the final cacheHitRatio



void FIFO()
{
    int* cacheBlock = (int*) malloc(cacheSize*sizeof(int));
    int currentInsertionIdx = 0;
    hits = 0;
    

    for(int i = 0; i < cacheSize; i++)
    {
        cacheBlock[i] = -1;
    }

    for(int i = 0; i < totalReferences; i++)
    {
        int ref = references[i];
        bool found = false;
        for(int j = 0; j < cacheSize; j++)
        {
            if(cacheBlock[j] == ref)
            {
                hits++;
                found = true;
                break;
            }
        }

        if(!found)
        {
            
            cacheBlock[currentInsertionIdx] = ref;
            currentInsertionIdx++;
            currentInsertionIdx%=cacheSize;
            
        }
    }

    cacheHitRatio = ((double) hits) / totalReferences;
    printf("The Hit Ratio for FIFO is : %d/%d = %.2f\n", hits, totalReferences, cacheHitRatio);
    free(cacheBlock);
}

void LRU()
{
    int* cacheBlock = (int*) malloc(cacheSize*sizeof(int));
    hits = 0;
    
    for(int i = 0; i < cacheSize; i++)
    {
        cacheBlock[i] = -1;
    }

    for(int i = 0; i < totalReferences; i++)
    {
        int ref = references[i];
        bool found = false;
        int foundIdx = -1;
        for(int j = 0; j < cacheSize; j++)
        {
            if(cacheBlock[j] == ref)
            {
                hits++;
                found = true;
                foundIdx = j;
                break;
            }
        }

        if(!found)
        {
            
            for(int i = cacheSize-1; i > 0; i--)
            {
                cacheBlock[i] = cacheBlock[i-1];
            }

            cacheBlock[0] = ref;
        }

        else
        {
            for(int i = foundIdx; i > 0; i--)
            {
                cacheBlock[i] = cacheBlock[i-1];
            }

            cacheBlock[0] = ref;
        }
    }

    cacheHitRatio = ((double) hits) / totalReferences;
    printf("The Hit Ratio for LRU is : %d/%d = %.2f\n", hits, totalReferences, cacheHitRatio);
    free(cacheBlock);
}
int main(int argc, char *argv[])
{
    if(argc < 5)
    {
    	printf("Sufficient number of arguments are not provided!");
    	return 0;
    }
    
    totalReferences = argc - 4;
    cacheSize = atoi(argv[1]); 
    mainMemorySize = atoi(argv[2]);
    algorithm = (char)argv[3][0];   // We are taking the first character of the string - i.e. the character array

    
    references = (int*)malloc(totalReferences * sizeof(int));
    for (int i = 0; i < totalReferences; i++)
    {
        references[i] = atoi(argv[i + 4]);
    }

    if (mainMemorySize != 32 && mainMemorySize != 64 && mainMemorySize != 128)  // cross-checking the correctness of the size of the main memory 
    {
        printf("Size of main memory should be should be 32/64/128!");
        return 0;
    }

    if (cacheSize > mainMemorySize / 4 || cacheSize < 1)        // cross-checking the correctness of the size of the cache memory 
    {
        printf("Size of cache should be less than 1/4th of the size of main memory!");
        return 0;
    }

    for (int i = 0; i < totalReferences; i++)   
    {
        if (references[i] >= mainMemorySize || references[i] < 0)   // cross-checking the correctness of the references 
        {
            printf("The references are not valid!");
            return 0;
        }
    }

    switch (algorithm)   // switch-casing the choice of the algorithm FIFO or LRU
    {
    case 'F':
        FIFO();
        break;
    case 'L':
        LRU();
        break;
    default:
        printf("The type of cache replacement should be either F or L!");
    }

    return 0;
}
