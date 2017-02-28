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
	char _args[ 256 ];
	int pid;
	char * const envp[ ] = { NULL };

	printf( "%% " );
	fgets( _args, 256, stdin );
	
	int arg_len = strlen( _args );
	//printf( "arg_len: %d\n", arg_len );

	// search for input/output redirection
	char args[ 256 ];
	int input = 0;
	int output = 0;
	int indices[ 10 ];
	int idx = 0;	

	// replace \n with \0 because of fgets formatting
	_args[ arg_len - 1 ] = '\0';

	for( int i = 0; i < arg_len; i++ )
	{
	    if( _args[ i ] == '<' )
	    {
		input++;
		indices[ idx ] = i;
		idx++;
	    }
	    else if( _args[ i ] == '>' )
	    {
		output++;
	    }
	}

	if( input || output )
	{
	    int chevron = indices[ 0 ];

	    char cat_file[ arg_len - ( chevron + 1 ) ];
	    int cat_idx = 0;
	
	    for( int i = 0; i < chevron - 1; i++ )
	    {
		args[ i ] = _args[ i ];
		//printf( "%c", _args[ i ] );
	    }

	    for( int j = chevron + 2; j < arg_len; j++ )
	    {
		cat_file[ cat_idx ] = _args[ j ];
		printf( "%c", cat_file[ cat_idx ] );
		cat_idx++;
	    }
	    printf( "\n" );
	}
	else
	{
	    //printf( "strlen( _args ): %d\n", strlen( _args ) );
	    for( int k = 0; k < arg_len; k++ )
	    {
	    	args[ k ] = _args[ k ];
	    }
	}

	/*printf( "strlen( args ): %d\n", strlen( args ) );
	for( int l = 0; l < strlen( args ); l++ )
	{
	    printf( "args[ l ]: %c\n", args[ l ] );
	}*/

	char * temp;
	char * argv[ 32 ];
	temp = strtok( args, " " );
	int i = 0;

	// separate args into argument vector
    	while( temp != NULL )
    	{
	    argv[ i++ ] = temp;
    	    temp = strtok( NULL, " " );
        }

	argv[ i ] = NULL;
	
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
	    printf( "+---- Version 0.2.5.2 -----+\n+---- Kevin  O\'Connor -----+\n+---- Revised 2/28/17 ----+\n" );
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
