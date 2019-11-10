#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int removeCommas(char *line){
  int i = 0;
  int j = 0;
  int numCommas = 0;

  while(*(line + i) != '\0'){
    if(*(line + i) == ','){
      numCommas++;
      j = 0;
      while(*(line + i + j + 1) != '\0'){
        *(line + i + j) = *(line + i + j + 1);
        j++;
      }
      *(line + i + j) = '\0';
    }
    i++;
  }
  return(numCommas);
}
