#ifndef __JSB_SUBLIMECLIENT_H
#define __JSB_SUBLIMECLIENT_H

#ifdef __cplusplus
extern "C" {
#endif


void sublimeclient_send( const char *message );

void sublimeclient_connect( void );

#ifdef __cplusplus
}
#endif

#endif