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
#include <unistd.h>
#include <signal.h>
#include "writer.h"
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
#define BUFFER_SIZE 300


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

/* no entiendo como encapsular una variable que pertenezca al mismo tiempo al
 * objeto y que sea global como para poder modificarlo en el signal_handler */
static volatile sig_atomic_t signal1_flag;

/******************************************************************************
 *  Prototypes (declarations) of private functions  
 *****************************************************************************/

static void _Signal_RX( int sig );

/******************************************************************************
 *  Implementations of public functions
 *****************************************************************************/

void Writer_Create( writer_t *self, char *fifo_name )
{
    Communication_Create( &self->comm_handle, fifo_name, 0666, WRITE_ONLY );
    Protocolo_Create( &self->protocol, &self->comm_handle );

    self->sa.sa_handler = _Signal_RX;
	self->sa.sa_flags = 0; 
	sigemptyset( &self->sa.sa_mask );

	sigaction( SIGUSR1, &self->sa, NULL);
    sigaction( SIGUSR2, &self->sa, NULL);
}


void Writer_Run( writer_t *self )
{
    char outputBuffer[BUFFER_SIZE];
    signal1_flag = false;

    /* open syscalls returned without error -> other process attached to named fifo */
	printf("got a reader--type some stuff\n");

        /* Loop forever */
	while (1)
	{
        if ( SIGUSR1 == signal1_flag )
        {
            Protocolo_Encode( &self->protocol, "1\n", SIGNAL );
            signal1_flag = 0;
        }
        else if ( SIGUSR2 == signal1_flag )
        {
            Protocolo_Encode( &self->protocol, "2\n", SIGNAL );
            signal1_flag = 0;
        }
        
        

        /* Get some text from console */
		if( NULL != fgets( outputBuffer, BUFFER_SIZE, stdin ) )
        {
            Protocolo_Encode( &self->protocol, outputBuffer, DATA );
        }
	}

}

void Writer_Destroy( writer_t *self )
{
    Protocolo_Destroy( &self->protocol);
    Communication_Destroy( &self->comm_handle );
}

/******************************************************************************
 *  Implementations of private functions
 *****************************************************************************/

void _Signal_RX( int sig )
{
    signal1_flag = sig;
}