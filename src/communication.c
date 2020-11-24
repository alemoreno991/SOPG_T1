/**
 * @file communication.c
 * @author Alejandro Moreno (ale.moreno991@gmail.com)
 * @brief Acá se hace una breve descripción del archivo
 * 
 * @version 2020-09-15 --------- Alejandro Moreno -------- v0.0
 * 
 * @copyright Copyright (c) 2020
 * 
 * @details Acá se puede hacer una descripción más detallada del archivo. 
 * Quizás, incorporando cosas más específicas.
 * 
 * @bug Aca se describen los errores, los warnings y las condiciones de 
 * finalización abnormal del programa
 * 
 * \pre Acá se explican las presuposiciones, las restricciones y limitaciones
 * 
 * @warning Aca se advierte algo que debe saber el usuario porque no tenerlo
 * en cuenta podría resultar en algo catastrófico
 * 
 * @see 
 */

/******************************************************************************
 *  Inclusions (library's order: standard C, others, user header files)
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include "communication.h"

/******************************************************************************
 *  Inclusions of private function dependencies
 *****************************************************************************/

/******************************************************************************
 *  Definitions of private data types (order: Enums, Typedefs)
 *****************************************************************************/


/******************************************************************************
 *  Definition macros of private constants
 *****************************************************************************/
static const char ERROR_MEM_ALLOC[] = { "Memory allocation error\n" };

static const char ERROR_CREATING_NODE[] = 
                                    { "Error creating named fifo: %d\n" };

static const char ERROR_OPENING_NODE[] = 
                                    { "Error opening named fifo file: %d\n" };

static const char ERROR_INVALID_MODE[] = { "Error. Invalid opening mode." };


/******************************************************************************
 *  Private function-like macros
 *****************************************************************************/

/******************************************************************************
 *  Definitions of external public global variables
 *****************************************************************************/

/******************************************************************************
 *  Definitions of public global variables
 *****************************************************************************/

/******************************************************************************
 *  Definitions of private global variables
 *****************************************************************************/

/******************************************************************************
 *  Prototypes (declarations) of private functions  
 *****************************************************************************/

/******************************************************************************
 *  Implementations of public functions
 *****************************************************************************/

/******************************************************************************
 *  Implementations of private functions
 *****************************************************************************/

bool Communication_Create( communication_t *self,
                           const char *node_name,
                           int32_t permissions,
                           comm_mode mode )
{
    bool ret = true;
    int32_t returnCode;

    self->node_name = (char *) malloc( strlen(node_name) * sizeof(char) );
    if ( NULL == self->node_name )
    {
        printf( ERROR_MEM_ALLOC );
        ret = false;
        exit(1); /* lo dejo así pero bien podría delegar el error a la funcion llamante */
    }

    /* 
     * Create named fifo. 
     * -1 means already exists so no action if already exists 
     */
    if ( (returnCode = mknod( node_name, S_IFIFO | permissions, 0) ) < -1 )
    {
        printf( ERROR_CREATING_NODE, returnCode );
        ret = false;
        exit(1); /* lo dejo así pero bien podría delegar el error a la funcion llamante */
    }

    switch( mode )
    {
        case WRITE_ONLY:
            self->fd = open( node_name, O_WRONLY);
            break;

        case READ_ONLY:
            self->fd = open( node_name, O_RDONLY);
            break;

        default:
            printf( ERROR_INVALID_MODE );
            ret = false;
            exit(1); /* lo dejo así pero bien podría delegar el error a la funcion llamante */
            break;
    }    

    /* Open named fifo. Blocks until other process opens it */
	if ( self->fd < 0 )
    {
        printf( ERROR_OPENING_NODE, self->fd );
        ret = false;
        exit(1); /* lo dejo así pero bien podría delegar el error a la funcion llamante */
    }

    return ret;
}

bool Communication_Send( communication_t *self, const char *msj )
{
    bool ret = false;
    int32_t bytesWrote = 0;

    /* Write buffer to named fifo. Strlen - 1 to avoid sending \n char */
    if ( (bytesWrote = write( self->fd, msj, strlen( msj ) - 1 ) ) == -1)
    {
        ret = false;
        perror("write");
    }
    else
    {
        ret = true;
    }

    return ret;
}

bool Communication_Receive( communication_t *self, 
                            char *buffer_rx, 
                            uint32_t buffer_size )
{
    bool ret = true;
    int32_t bytes_read;

    /* read data into local buffer */
    if ( -1 == ( bytes_read = read( self->fd, 
                                    buffer_rx, 
                                    buffer_size ) ) )
    {
        ret = false;
        perror( "read" );
    }
    
    buffer_rx[bytes_read] = '\0';

    if( 0 == bytes_read )
    {
        ret = false; /* quizas podría poner un codigo de retorno no binario */
    }

    return ret;
}

bool Communication_Destroy( communication_t *self )
{
    if( NULL != self->node_name )
    {
        free( self->node_name );
        self->node_name = NULL;
    }

    close( self->fd );

    return true;
}
