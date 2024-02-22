/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
|                    checksum on an ASCII input file
|
|     Author: Iliya Klishin
|   Language: c, c++, Java, GO, Python
|
|  To Compile: javac pa02.java
|              gcc -o pa02 pa02.c
|              g++ -o pa02 pa02.cpp
|              go build pa02.go
|              python pa02.py //Caution - expecting input parameters
|
| To Execute: java -> java pa02 inputFile.txt 8
|             or c++ -> ./pa02 inputFile.txt 8
|             or c -> ./pa02 inputFile.txt 8
|             or go -> ./pa02 inputFile.txt 8
|             or python-> python pa02.py inputFile.txt 8
|                         where inputFile.txt is an ASCII input file
|                         and the number 8 could also be 16 or 32
|                         which are the valid checksum sizes, all
|                         other values are rejected with an error message
|                         and program termination
|
|           Note: All input files are simple 8 bit ASCII input
|
|           Class: CIS3360 - Security in Computing - Spring 2022
|
| Instructor: McAlpin
| Due Date: 3 April
|
+=============================================================================*/


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


void print80lines(char* text)
{
  int len = strlen(text);
  //char let = 'A';
  for(int i = 0; i < len; i++)
  {
    if(i % 80 == 0)
    {
      printf("\n");
    }
    printf("%c",text[i]);
  }

  printf("\n");
}

uint8_t eightbit_checksum(char* arr, int checkSumSize)
{
  uint8_t checksum = 0;
  int characterCnt = strlen(arr);
  
  for(int i = 0; i < characterCnt; i++)
  {
    checksum += (uint8_t)arr[i];
  }
  print80lines(arr);
  printf("%2d bit checksum is %8lx for all %4d chars\n",checkSumSize, (unsigned long)checksum, characterCnt);
  return checksum;
}

uint16_t sixteenbit_checksum(char* arr, int checkSumSize)
{
  char n_arr[2000];
  strcpy(n_arr, arr);
  
  uint16_t checksum = 0;
  int len = strlen(n_arr);
  int count = 0;
  int numbits = 8 * len;
  //printf("%d\n", numbits);
  if(numbits % 16 != 0)
  {
    for(int j = len; numbits % 16 != 0; j++)
    {
      n_arr[j] = 'X';
      n_arr[j + 1] = '\0';
      numbits = 8 * strlen(n_arr);
    }
  }

  int characterCnt = strlen(n_arr);
  //printf("Padding with X:\n");
  //for(int j1 = 0; j1 < strlen(n_arr); j1++)
    {
     // printf("%c", n_arr[j1]);
    }
 // printf("\n");
  uint16_t first = 0;
  uint16_t s = 0;
  uint16_t pair = 0;

  for(int i = 0; i < characterCnt; i++)
  {
    count++;
    if(count % 2 != 0)
      continue;
  
    //printf("%d\n", count);
    first = (uint16_t)n_arr[i - 1];
    s = (uint16_t)n_arr[i];
    pair = (first << 8) + s;
    checksum += pair;
    
  }
  print80lines(n_arr);
  printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long)checksum, characterCnt);
  return checksum;
}


uint32_t _32bitchecksum(char* arr, int checkSumSize)
{
  char n_arr[2000];
  strcpy(n_arr, arr);
  
  uint32_t checksum = 0;
  int len = strlen(n_arr);
  int numbits = 8 * len;
  int count = 0;

  if(numbits % 32 != 0)
  {
    for(int i = len; numbits % 32 != 0; i++)
    {
      n_arr[i] = 'X';
      n_arr[i + 1] = '\0';

      numbits = strlen(n_arr) * 8;
    }
  }
  int characterCnt = strlen(n_arr);
  
  //for(int i = 0; i < characterCnt; i++)
  {
    //printf("%c", n_arr[i]);
  }
  //printf("\n");
  uint32_t f = 0, s = 0, th = 0, fth = 0, group = 0;

  for(int j = 0; j < characterCnt; j++)
  {
    count++;
    if(count % 4 != 0)
      continue;

    f = n_arr[j - 3];
    s = n_arr[j - 2];
    th = n_arr[j - 1];
    fth = n_arr[j];
    group = (f << 24) + (s << 16) + (th << 8) + fth;
    checksum += group;
  }

  print80lines(n_arr);
  printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long int)checksum, characterCnt);

  return checksum;
}

int main(int argc, char** argv) {

  FILE* m;
  FILE* input;
  input = fopen(argv[argc - 2], "r");
  
  if(strcmp(argv[2], "8") != 0 && strcmp(argv[2], "16") != 0 && strcmp(argv[2], "32") != 0)
  {
    fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
  }
  int checksumSize = atoi(argv[2]);
  //printf("%d")
  char c[2000];
  char c1;
  int i = 0;
  while(fscanf(input, "%c", &c1)!= EOF)
  {
    c[i] = c1;
    c[i+1] = '\0';
    i++;
  }

  //for(int i = 0; i < strlen(c); i++)
  
   // printf("%c", c[i]);
  
  //printf("\n");
  unsigned long int checksum = 0;
  if(checksumSize == 8)
  {
    checksum = eightbit_checksum(c, checksumSize);
  }

  if(checksumSize == 16)
  {
    checksum = sixteenbit_checksum(c, checksumSize);
  }
  if(checksumSize == 32)
  {
   checksum = _32bitchecksum(c, checksumSize);
  }
  
  return 0;
}

/*=============================================================================
| I Iliya Klishin (il351709) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/