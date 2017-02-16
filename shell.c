/*

Kevin O'Connor
February 2017

COS421 Operation Systems
Shell implementation

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char * argv[ ] )
{

    while( 1 )
    {

	//char * args;
	char args[ 10 ];

	printf( "%% " );
	//fgets( args, 10, stdin );
	scanf( "%s", args );

	if( strcmp( args, "exit" ) == 0 )
	{
	    printf( "Exiting program\n" );
	    return 0;
	}
	else if ( strcmp( args, "cd" ) == 0 )
	{
	    printf( "Change directory\n" );
	}
	else if ( strcmp( args, "pwd" ) == 0 )
	{
	    printf( "Print working directory\n" );
	}
	else if( strcmp( args, "version" ) == 0 )
	{
	    printf( "+----- Version 0.1.1 -----+\n+---- Kevin O\'Connor -----+\n+---- Revised 2/16/17 ----+\n" );
	}
	else
	{
	    printf( "Command not found\n" );
	}

    }

    return 0;

}
