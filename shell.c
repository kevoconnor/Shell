/*

Kevin O'Connor
February 2017

COS421 Operation Systems
Shell implementation

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char * argv[ ] )
{

    while( 1 )
    {

	char args[ 100 ];
	int pid;
	char * const envp[ ] = { NULL };

	printf( "%% " );
	scanf( "%s", args );

	// EXIT
	if( strcmp( args, "exit" ) == 0 )
	{
	    printf( "Exiting program\n" );
	    return 0;
	}

	// CD
	else if ( strcmp( args, "cd" ) == 0 )
	{
	    chdir( "/Users/kevinoconnor/Desktop/School/COS421/shell/" );
	}

	// PWD
	else if ( strcmp( args, "pwd" ) == 0 )
	{
	    char * pwd;
	    char buffer[ 100 ];
	    pwd = getcwd( buffer, 100 );
	    printf( "%s\n", pwd );
	}

	// VERSION
	else if( strcmp( args, "version" ) == 0 )
	{
	    printf( "+----- Version 0.1.1 -----+\n+---- Kevin O\'Connor -----+\n+---- Revised 2/20/17 ----+\n" );
	}

	// NOT BUILT-IN
	else
	{
	    const char * path_name = args;
	    char * const argv[ ] = { args, NULL, 0 };

	    // TODO split args by space using strtok( )

	    if( ( pid = fork( ) ) == 0 )
	    {
		execve( argv[ 0 ], argv, envp );
		printf( "Command not found\n" );
	    }
	    else if( pid > 0 )
	    {
		waitpid( pid, NULL, 0 );
	    }
	    else
	    {
		printf( "Error" );
	    }
	}

    }

    return 0;

}
