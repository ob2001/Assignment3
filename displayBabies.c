#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "babies.h"

int main ( int argc, char *argv[] ) {

   FILE *f1;
   int i = 0;
   int j = 0;
   struct pNames popNames;
   char maleSNumber[20];
   char femaleSNumber[20];
   char string[100];

   if ( argc != 2 ) {
      printf ( "Usage: displayBabies <decade filename>\n" );
      return ( -1 );
   }
   if ( (f1 = fopen(argv[1], "r")) != NULL ) {
      while ( fgets(string, 100, f1) != NULL ) {
         sscanf (string, "%d %s %s %s %s", &popNames.rank[i], popNames.maleName[i], maleSNumber, popNames.femaleName[i], femaleSNumber);
/* printf ( "%d %s %s %s %s\n",popNames.rank[i],popNames.maleName[i],maleSNumber,popNames.femaleName[i],femaleSNumber ); */
         removeCommas ( maleSNumber );
         removeCommas ( femaleSNumber );
         popNames.maleNumber[i] = atoi ( maleSNumber );
         popNames.femaleNumber[i] = atoi ( femaleSNumber );
         i++;
      }
   } else {
      printf ( "Cannot open %s\n", argv[1] );
      return ( -2 );
   }

   for ( j=0; j<i; j++ ) {
      printf ( "%d %s %d %s %d\n", popNames.rank[j], popNames.maleName[j], popNames.maleNumber[j], 
                                                     popNames.femaleName[j], popNames.femaleNumber[j] );
   }

   return (0);

}
         
