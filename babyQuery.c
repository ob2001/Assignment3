#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "babies.h"

#define MAXSIZE 1000

int mChop(char *line);

int mTrim(char *line);

int findName(char *name, struct pNames *nameInfo, int gender);

int main (int argc, char *argv[]){
  int i = 0;
  int j = 0;
  int k = 0;
  int l = 0;
  int flag = 0;
  int flag1 = 0;
  int flag2 = 0;
  int flag3 = 0;
  int chosenRank = 0;
  int chosenGender = 0;
  int output = 0;

  char input[50];
  char filename[100];
  char temp[MAXSIZE];
  char tempRank[50];
  char tempMName[50];
  char tempMNum[50];
  char tempFName[50];
  char tempFNum[50];
  char requestedName[50];

  struct pNames nameInfo;

  FILE *fp;

  /*Ask user for desired decade and open corresponding file*/
  while(flag != 1){
    flag = 0;
    flag1 = 0;
    flag2 = 0;
    flag3 = 0;

    i = 0;
    input[0] = '\0';
    filename[0] = '\0';
    temp[0] = '\0';
    for(i = 0; i < 50; i++){
      tempRank[i] = 0;
    }
    for(i = 0; i < 50; i++){
      tempMName[i] = '\0';
    }
    for(i = 0; i < 50; i++){
      tempMNum[i] = 0;
    }
    for(i = 0; i < 50; i++){
      tempFName[i] = '\0';
    }
    for(i = 0; i < 50; i++){
      tempFNum[i] = 0;
    }
    requestedName[0] = '\0';
    nameInfo.year = 0;
    for(i = 0; i < 200; i++){
      nameInfo.rank[i] = 0;
      nameInfo.maleName[i][0] = '\0';
      nameInfo.maleNumber[i] = 0;
      nameInfo.femaleName[i][0] = '\0';
      nameInfo.femaleNumber[i] = 0;
    }

    while(flag1 != 1){
      printf("What decade do you want to look at? [1880 to 2010]: ");
      if((fgets(input, 50, stdin) == NULL) || (atoi(input) % 10 != 0) || (atoi(input) < 1880) || (atoi(input) > 2010)){
        printf("Acceptable decades are 1880, 1890, 1900, 1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990, 2000, or 2010. No other numbers are acceptable.\n");
        flag2 = 0;
      } else {
        mChop(input);
        mTrim(input);
        strcpy(filename, input);
        strcat(filename, "Names.txt");
        if((fp = fopen(filename, "r")) == NULL){
          printf("Acceptable decades are 1880, 1890, 1900, 1910, 1920, 1930, 1940, 1950, 1960, 1970, 1980, 1990, 2000, or 2010. No other numbers are acceptable.\n");
          flag1 = 0;
        } else {
          flag1 = 1;
        }
      }
    }
    nameInfo.year = atoi(input);
    input[0] = '\0';

    /*Store information in struct for manipulation*/
    j = 0;
    while(fgets(temp, MAXSIZE, fp) != NULL){
    i = 0;
    k = 0;
    while(*(temp + i) != '\t'){
      tempRank[k] = *(temp + i);
      i++;
      k++;
    }
    nameInfo.rank[j] = atoi(tempRank);
    i++;
    k = 0;
    while(*(temp + i) != '\t'){
      tempMName[k] = *(temp + i);
      i++;
      k++;
    }
    tempMName[k] = '\0';
    strcpy(nameInfo.maleName[j], tempMName);
    i++;
    k = 0;
    while(*(temp + i) != '\t'){
      tempMNum[k] = *(temp + i);
      i++;
      k++;
    }
    removeCommas(tempMNum);
    nameInfo.maleNumber[j] = atoi(tempMNum);
    for(l = 0; l < 50; l++){
      tempMNum[l] = 0;
    }
    i++;
    k = 0;
    while(*(temp + i) != '\t'){
      tempFName[k] = *(temp + i);
      i++;
      k++;
    }
    tempFName[k] = '\0';
    strcpy(nameInfo.femaleName[j], tempFName);
    i++;
    k = 0;
    while(*(temp + i) != '\n'){
      tempFNum[k] = *(temp + i);
      i++;
      k++;
    }
    removeCommas(tempFNum);
    nameInfo.femaleNumber[j] = atoi(tempFNum);
    for(l = 0; l < 50; l++){
      tempMNum[l] = 0;
    }
    j++;
  }
    fclose(fp);

    /*Continue questions*/
    flag1 = 0;
    while(flag1 != 1){
      flag2 = 0;
      printf("Would you like to see a rank, search for a name, or see the top 10? [rank, search, top]: ");
      input[0] = '\0';
      while(flag2 != 1){
        fgets(input, 50, stdin);
        mChop(input);
        mTrim(input);
        if((input == NULL) || ((strcmp(input, "rank") != 0) && ((strcmp(input, "search")) != 0) && ((strcmp(input, "top")) != 0))){
          printf("Please type in rank, search, or top exactly as requested.\n");
          flag2 = 0;
        } else {
          if((strcmp(input, "rank")) == 0){
            flag3 = 0;
            printf("What rank do you wish to see? [1-200]: ");
            input[0] = '\0';
            while(flag3 != 1){
              fgets(input, 50, stdin);
              if(atoi(input) < 1 || atoi(input) > 200){
                printf("Only numbers between 1 and 200 are acceptable.\n");
              } else {
                chosenRank = atoi(input);
                flag3 = 1;
              }
            }
            printf("Would you like to see male (0), female (1), or both (2) names? [0-2]: ");
            input[0] = '\0';
            flag3 = 0;
            while(flag3 != 1){
              fgets(input, 50, stdin);
              if((atoi(input)) < 0 || atoi(input) > 2){
                printf("Only the numbers 0, 1, or 2 are acceptable.");
              } else {
                chosenGender = atoi(input);
                flag3 = 1;
              }
            }
            if(chosenGender == 0){
              printf("Rank %d: Male: %s (%d)\n", nameInfo.rank[chosenRank - 1], nameInfo.maleName[chosenRank - 1], nameInfo.maleNumber[chosenRank - 1]);
            } else if(chosenGender == 1){
              printf("Rank %d: Female: %s (%d)\n", nameInfo.rank[chosenRank - 1], nameInfo.femaleName[chosenRank - 1], nameInfo.femaleNumber[chosenRank - 1]);
            }
            if(chosenGender == 2){
              printf("Rank %d: Male: %s (%d) and Female: %s (%d)\n", nameInfo.rank[chosenRank - 1], nameInfo.maleName[chosenRank - 1], nameInfo.maleNumber[chosenRank - 1], nameInfo.femaleName[chosenRank - 1], nameInfo.femaleNumber[chosenRank - 1]);
            }
          } else if((strcmp(input, "search")) == 0){
            flag3 = 0;
            printf("What name do you wish to search for? [case sensitive]: ");
            input[0] = '\0';
            fgets(requestedName, 50, stdin);
            mChop(requestedName);
            mTrim(requestedName);
            printf("Do you wish to search male (0), female (1), or both (2) names? [0-2]: ");
            input[0] = '\0';
            while(flag3 != 1){
              fgets(input, 50, stdin);
              if(atoi(input) < 0 || atoi(input) > 2){
                printf("Only the numbers 0, 1, or 2 are acceptable.\n");
                flag3 = 0;
              } else {
                chosenGender = atoi(input);
                flag3 = 1;
              }
            }
            if(findName(requestedName, &nameInfo, chosenGender) != -1 && findName(requestedName, &nameInfo, chosenGender) < 200){
              output = findName(requestedName, &nameInfo, chosenGender);
              if(chosenGender == 2){
                if(strcmp(nameInfo.femaleName[output], requestedName) == 0){
                  printf("In %d, the female name %s is ranked %d with a count of %d and the male name %s is not ranked\n", nameInfo.year, requestedName, output + 1, nameInfo.femaleNumber[output], requestedName);
                } else if(strcmp(nameInfo.maleName[output], requestedName) == 0){
                  printf("In %d, the female name %s is not ranked and the male name %s is ranked %d with a count of %d\n", nameInfo.year, requestedName, requestedName, output + 1, nameInfo.maleNumber[output]);
                }
              } else if(chosenGender == 0){
                printf("In %d, the male name %s is ranked %d with a count of %d.\n", nameInfo.year, requestedName, output + 1, nameInfo.maleNumber[output]);
              } else if(chosenGender == 1){
                printf("In %d, the female name %s is ranked %d with a count of %d.\n", nameInfo.year, requestedName, output + 1, nameInfo.femaleNumber[output]);
              }
            } else {
              if(chosenGender == 0){
                printf("In %d, the male name %s is not ranked.\n", nameInfo.year, requestedName);
              } else if(chosenGender == 1){
                printf("In %d, the female name %s is not ranked.\n", nameInfo.year, requestedName);
              }
            }
          } else if((strcmp(input, "top")) == 0){
            i = 0;
            for(i = 0; i < 10; i++){
              printf("%-3d %-12s %-8d %-12s %-8d\n", nameInfo.rank[i], nameInfo.maleName[i], nameInfo.maleNumber[i], nameInfo.femaleName[i], nameInfo.femaleNumber[i]);
            }
          }
          flag2 = 1;
        }
      }
      printf("Do you want to ask another question about %d? [Y or N]:", nameInfo.year);
      flag2 = 0;
      while(flag2 != 1){
        fgets(input, 50, stdin);
        mChop(input);
        mTrim(input);
        if(strcmp(input, "Y") == 0){
          flag2 = 1;
        } else if(strcmp(input, "N") == 0){
          flag2 = 1;
          flag1 = 1;
        } else {
          printf("Only the single characters Y or N are acceptable.\n");
          flag2 = 0;
        }
      }
    }
    printf("Would you like to select another year? [Y or N]: ");
    flag1 = 0;
    input[0] = '\0';
    while(flag1 != 1){
      fgets(input, 50, stdin);
      mChop(input);
      mTrim(input);
      if(strcmp(input, "Y") == 0){
        flag1 = 1;
        flag = 0;
      } else if(strcmp(input, "N") == 0){
        flag1 = 1;
        flag = 1;
      } else {
        printf("Only the single characters Y or N are acceptable.\n");
        flag1 = 0;
      }
    }
  }

  printf("Thank you for using babyQuery.\n");
  return(0);
}
