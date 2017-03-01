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
#include "signal.h"
#include "fcntl.h"

void signal_handler( int sig )
{
	
    while( waitpid( -1, NULL, WNOHANG ) > 0 )
    {
	// Empty;
    }

}

int main( int argc, char ** argv )
{

    int bg_proc = 0;

    struct sigaction sig_action;
    memset( &sig_action, 0, sizeof( sig_action ) );
    sig_action.sa_handler = signal_handler;

    sigaction( SIGCHLD, &sig_action, NULL );

    while( 1 )
    {
	char args[ 256 ];
	int pid;
	char * const envp[ ] = { NULL };

	printf( "%% " );
	fgets( args, 256, stdin );
	
	// replace \n with \0
	args[ strlen( args ) - 1 ] = '\0';

	char * temp;
	char * argv[ 32 ];
	temp = strtok( args, " " );
	int i = 0;

    	while( temp != NULL )
    	{
	    argv[ i++ ] = temp;
    	    temp = strtok( NULL, " " );
        }

	int argv_len = i;
	argv[ i ] = NULL;
	char * infilep;
	char * outfilep;

	int input = 0;
	int output = 0;

	for( int j = 0; j < argv_len; j++ )
	{
	    if( strcmp( argv[ j ], "<" ) == 0 )
	    {
		input++;
	    }
	    else if( strcmp( argv[ j ], ">" ) == 0 )
	    {
		output++;
	    }
	    //printf( "%s\n", argv[ j ] );
	}
	
	if( strcmp( argv[ i - 1 ], "&" ) == 0 )
	{
	    bg_proc = 1;
	    argv[ i - 1 ] = NULL;
	}

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
	    if( argv[ 1 ] != NULL )
	    {
	    	chdir( argv[ 1 ] );
	    }
	    else
	    {
		chdir( getenv( "HOME" ) );
	    }
	}

	// PWD
	else if( strcmp( cmd, "pwd" ) == 0 )
	{
	    char * pwd;
	    char buffer[ 256 ];
	    pwd = getcwd( buffer, 256 );
	    printf( "%s\n", pwd );
	}

	// VERSION
	else if( strcmp( cmd, "version" ) == 0 )
	{
	    printf( "+---- Version 0.2.6.5 -----+\n+---- Kevin  O\'Connor -----+\n+---- Revised 2/28/17 ----+\n" );
	}

	// NOT BUILT-IN
	else
	{
	    if( ( pid = fork( ) ) == 0 )
	    {
		char * path = getenv( "PATH" );
    		char fullPath[ 256 ];
    		char * temp;
    		temp = strtok( path, ":" );
		
    		while( temp != NULL )
    		{
		    strcpy( fullPath, temp );
        	    strcat( fullPath, "/" );
        	    strcat( fullPath, cmd );

		    if( input )
		    {
			infilep = argv[ argv_len - 1 ];
			argv[ argv_len - 2 ] = NULL;
			argv[ argv_len - 1 ] = NULL;
			printf( "infilep: %s, argv[ argv_len - 1 ]: %s", infilep, argv[ argv_len - 1 ] );
			int file_d = open( infilep, O_RDONLY, 0600 );
			dup2( file_d, STDIN_FILENO );
			close( file_d );
		    }
		    else if( output )
		    {
			outfilep = argv[ argv_len - 1 ];
			argv[ argv_len - 2 ] = NULL;
			argv[ argv_len - 1 ] = NULL;
			int file_d = open( outfilep, O_CREAT | O_TRUNC | O_WRONLY, 0600 );
			dup2( file_d, STDOUT_FILENO );
			close( file_d );
		    }
		    
		    execve( fullPath, argv, envp );
		    //perror( "execve" );

        	    temp = strtok( NULL, ":" );
    		}

		printf( "Command not found\n" );
		exit( 0 );
	    }
	    else if( pid > 0 )
	    {
		if( bg_proc )
		{
		    sleep( 1 );
		}
		else
		{
		    waitpid( pid, NULL, 0 );
		}

		bg_proc = 0;
	    }
	    else
	    {
		printf( "Error" );
	    }
	}

    }

    return 0;
	
}
