/*

Kevin O'Connor
February 2017

COS421 Operation Systems
Shell implementation

*/

#include "stdio.h" 
#include "unistd.h"
#include "stdlib.h"
#include "string.h"

int main( int argc, char ** argv )
{

    while( 1 )
    {
	char args[ 100 ];
	int pid;
	char * const envp[ ] = { NULL };

	printf( "%% " );
	fgets( args, 100, stdin );
	
	// replace \n with \0
	args[ strlen( args ) - 1 ] = '\0';

	char * temp;
	char * argv[ 10 ];
	temp = strtok( args," " );
	int i = 0;

    	while( temp != NULL )
    	{
	    argv[ i++ ] = temp;
    	    temp = strtok( NULL, " " );
        }

	argv[ i ] = NULL;
	
	char * cmd = argv[ 0 ];
	
	// EXIT
	if( strcmp( cmd, "exit" ) == 0 )
	{
	    printf( "Exiting program\n" );
	    exit( 0 );
	}

	// CD
	else if( strcmp( cmd, "cd" ) == 0 )
	{
	    chdir( argv[ 1 ] );
	}

	// PWD
	else if( strcmp( cmd, "pwd" ) == 0 )
	{
	    char * pwd;
	    char buffer[ 100 ];
	    pwd = getcwd( buffer, 100 );
	    printf( "%s\n", pwd );
	}

	// VERSION
	else if( strcmp( cmd, "version" ) == 0 )
	{
	    printf( "+---- Version 0.2.4.0 -----+\n+---- Kevin  O\'Connor -----+\n+---- Revised 2/23/17 ----+\n" );
	}

	// NOT BUILT-IN
	else
	{
	    if( ( pid = fork( ) ) == 0 )
	    {
		char * path = getenv( "PATH" );
    		char fullPath[ 100 ];
    		char * temp;
    		temp = strtok( path,":" );
		
    		while( temp != NULL )
    		{
		    strcpy( fullPath, temp );
        	    strcat( fullPath, "/" );
        	    strcat( fullPath, cmd );
		    
		    execve( fullPath, argv, envp );
		    //perror( "execve" );

        	    temp = strtok( NULL, ":" );
    		}

		printf( "Command not found\n" );
		exit( 0 );
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
