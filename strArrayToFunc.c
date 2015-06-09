#include <stdio.h>

void test(char *string[])
{	
	printf("%s",string[1]);
}

int main ( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        printf( "No insert filename" );
    }
    else 
    {
    	printf("%s\n",argv[1] );
        test(argv);
    }
}
