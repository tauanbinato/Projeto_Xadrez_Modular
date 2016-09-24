// Gera um banner informando qual o construto está sendo compilado

#include <stdio.h>
#include <string.h>

#define  PARM_STRING_1  "/c"
#define  PARM_STRING_2  "/C"


int main( int argc, char *argv[] )
{
   if ( argc >= 2 )
   {
      if ( ( memcmp( argv[ 1 ] , PARM_STRING_1 , strlen( PARM_STRING_1 )) == 0 )
        || ( memcmp( argv[ 1 ] , PARM_STRING_2 , strlen( PARM_STRING_2 )) == 0 ))
      {
         printf( "\n\n#################### Compilacao do construto: %s\n\n" , argv[ 1 ] + 2 ) ;
         return 0 ;
      } /* if */

      printf( "\n\n>>> CompileBanner - parametro desconhecido: %s\n" , argv[ 1 ] ) ;
	} else
   {
      printf( "\n\n>>> CompileBanner - Faltou o parametro nome do construto\n") ;
	} /* if */

   printf( "\n\nModo de usar:" ) ;
   printf( "\n\n   CompileBanner %s<nome construto>" , PARM_STRING_1 ) ;
   printf( "\n\n      <nome construto> nome do construto (.mak) a ser compilado.\n" ) ;

	return 4;
} /* Fim: CompileBanner */
