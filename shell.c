/*

Kevin O'Connor
February 2017

COS421 Operation Systems
Shell implementation

*/

#include <stdio.h>
#include <unistd.h>

int main( int argc, char * argv[ ] )
{

    while( 1 )
    {

	char args[ 100 ];
	
	printf( "\n%% " );
	fgets( args, 100, stdin );
	
	/*
	switch( argv[ 1 ] )
	{

	    // case ls

	    // case pwd

  	    // case cat

	} 
	printf( "\n>" );
	*/
    }

    //printf( "Shell prompt \n" );

    return 0;

}
