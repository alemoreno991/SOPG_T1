/**
 * @file protocolo.c
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
#include <string.h>
#include "protocolo.h"
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

static const char SIGNAL_HEADER[] = { "SIGN: " };
static const char DATA_HEADER[]   = { "DATA: " };

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
static void _EncodeSignal( protocolo_t *self );

static void _EncodeData( protocolo_t *self );

/******************************************************************************
 *  Implementations of public functions
 *****************************************************************************/

void Protocolo_Create( protocolo_t *self, communication_t *comm_handle )
{
    self->named_fifo = comm_handle;
}

void Protocolo_Encode( protocolo_t *self, const char *msg, protocolo_mode mode )
{
    switch( mode )
    {
        case DATA:
            _EncodeData( self );
            break;

        case SIGNAL:
            _EncodeSignal( self );
            break;

        default:

            break;
    }

    Communication_Send( self->named_fifo, msg );
}

protocolo_mode Protocolo_Decode( protocolo_t *self, char *buffer, int32_t buffer_len )
{
    protocolo_mode ret;
    
    if( Communication_Receive( self->named_fifo, buffer, buffer_len ) )
    {
        if( 0 == strncmp( DATA_HEADER, buffer, strlen(DATA_HEADER) - 1 ) )
        {
            self->rx_flag = DATA;
        }    
        else if( 0 == strncmp( SIGNAL_HEADER, buffer, strlen(SIGNAL_HEADER) - 1 ) )
        {
            self->rx_flag = SIGNAL;
        }

        ret = self->rx_flag;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

void Protocolo_Destroy( protocolo_t *self ) { }

/******************************************************************************
 *  Implementations of private functions
 *****************************************************************************/

void _EncodeSignal( protocolo_t *self )
{
    Communication_Send( self->named_fifo, SIGNAL_HEADER );
}

void _EncodeData( protocolo_t *self )
{
    Communication_Send( self->named_fifo, DATA_HEADER );
}