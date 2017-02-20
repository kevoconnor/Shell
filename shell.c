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

	//char * args;
	char args[ 10 ];
	int pid;
	char * const envp[ ] = { NULL };

	printf( "%% " );
	//fgets( args, 10, stdin );
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
	    printf( "+----- Version 0.1.1 -----+\n+---- Kevin O\'Connor -----+\n+---- Revised 2/16/17 ----+\n" );
	}

	// LS
	else if( strcmp( args, "ls" ) == 0 )
	{
	    const char * path_name = "/bin/ls";
	    char * const argv[ ] = { "/bin/ls", NULL, 0 };

	    if( ( pid = fork( ) ) == 0 )
	    {
		// child process
		//printf( "child process\n" );
		execve( argv[ 0 ], argv, envp );
	    }
	    else if( pid > 0 )
	    {
		// parent process
		//printf( "parent\n" );
		waitpid( pid, NULL, 0 );
	    }
	    else
	    {
		printf( "error" );
	    }
	}

	// DATE 
	else if( strcmp( args, "date" ) == 0 )
	{
	    const char * path_name = "/bin/date";
	    char * const argv[ ] = { "/bin/date", NULL, 0 };

	    if( ( pid = fork( ) ) == 0 )
	    {
		execve( argv[ 0 ], argv, envp );
	    }
	    else if( pid > 0 )
	    {
		waitpid( pid, NULL, 0 );
	    }
	    else
	    {
		printf( "error" );
	    }
	}

	// UPTIME
	else if( strcmp( args, "uptime" ) == 0 )
	{
	    const char * path_name = "/usr/bin/uptime";
	    char * const argv[ ] = { "/usr/bin/uptime", NULL, 0 };

	    if( ( pid = fork( ) ) == 0 )
	    {
		execve( argv[ 0 ], argv, envp );
	    }
	    else if( pid > 0 )
	    {
		waitpid( pid, NULL, 0 );
	    }
	    else
	    {
		printf( "error" );
	    }
	}
	else
	{
	    printf( "Command not found\n" );
	}

    }

    return 0;

}
