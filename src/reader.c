/**
 * @file writer.c
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
#include "reader.h"
#include "communication.h"
#include "protocolo.h"

/******************************************************************************
 *  Inclusions of private function dependencies
 *****************************************************************************/

/******************************************************************************
 *  Definitions of private data types (order: Enums, Typedefs)
 *****************************************************************************/


/******************************************************************************
 *  Definition macros of private constants
 *****************************************************************************/
#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 300

static const char SIGNAL_FILE[] = { "Sign.txt" };
static const char LOG_FILE[] = { "Log.txt" };

static const char ERROR_OPENING_FILE[] = { "Error. Could not open file\n" };

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

void Reader_Create( reader_t *self, char *fifo_name )
{
    Communication_Create( &self->comm_handle, fifo_name, 0666, READ_ONLY );
    Protocolo_Create( &self->protocol, &self->comm_handle );

    if ( NULL == (self->sign = fopen( SIGNAL_FILE, "w" ) ) )
    {
        printf( ERROR_OPENING_FILE );
        exit(1); /* lo dejo así pero bien podría delegar el error a la funcion llamante */
    }

    if ( NULL == (self->log = fopen( LOG_FILE, "w" ) ) )
    {
        printf( ERROR_OPENING_FILE );
        exit(1); /* lo dejo así pero bien podría delegar el error a la funcion llamante */
    }

}


void Reader_Run( reader_t *self )
{
    char inputBuffer[BUFFER_SIZE];
    protocolo_mode type = DATA;

    /* open syscalls returned without error -> other process attached to named fifo */
	printf("got a writer\n");

    /* Loop forever */
	while ( -1 != type )
	{
        type = Protocolo_Decode( &self->protocol, inputBuffer, BUFFER_SIZE );

        switch( type )       
        {
            case DATA:
                fprintf( self->log, "%s", inputBuffer );
                break;
            
            case SIGNAL:
                fprintf( self->sign, "%s", inputBuffer );
                break;

            default:

                break;
        }
	}

}

void Reader_Destroy( reader_t *self )
{
    if( self->log != NULL )
    {
        fclose( self->log );
    }

    if( self->sign != NULL )
    {
        fclose( self->sign );
    }

    Protocolo_Destroy( &self->protocol);
    Communication_Destroy( &self->comm_handle );
}
