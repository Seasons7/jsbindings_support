#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>

static int sublimeclient_sockfd = 0;
static unsigned char sublimeclient_is_connected = 0;

static void err_func(const char *msg);

static void err_func(const char *msg)
{
    perror(msg);
    // exit(EXIT_FAILURE); // Not use
}

void sublimeclient_send( const char *message ) {

    int len = strlen(message);
    if( len <= 0 ) 
        return;

    if( sublimeclient_is_connected == 0 )
        return;

    const char* cr = "\n";
    send(sublimeclient_sockfd, message, len, 0 );
    send(sublimeclient_sockfd, cr, strlen(cr), 0 );
}

void sublimeclient_connect( void ) {
    
    struct sockaddr_in serv;
    unsigned short port;

    sublimeclient_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sublimeclient_sockfd < 0) {
        err_func("socket");
        return;
    }

    struct hostent* host = NULL;
    host = gethostbyname("localhost");
    if ( host == NULL ) {
        err_func("host err");
        return;
    }
    
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    port = (unsigned short)strtol("12345" , NULL , 10);
    serv.sin_port = htons(port);
    serv.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
    
    if(connect(sublimeclient_sockfd, (struct sockaddr *)&serv, sizeof(struct sockaddr_in)) < 0) {

        err_func("connect");

    }else {

        printf("==== SublimeServer Connected!! ====");
        sublimeclient_is_connected = 1;
    }
}


