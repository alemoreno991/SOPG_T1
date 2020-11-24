/**
 * @file writer.h
 * @author Alejandro M (ale.moreno991@gmail.com)
 * @brief Descripción breve 
 * 
 * @version 2020-09-15 --------- Alejandro Moreno -------- v0.0
 *      - Descripción del cambio 1
 *      - Descripción del cambio 2
 *      - Descripción del cambio 3
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*=====[Avoid multiple inclusion - begin]====================================*/
#ifndef WRITER_H
#define WRITER_H

/******************************************************************************
 *  Inclusions of public function dependencies
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include "communication.h"
#include "protocolo.h"

/******************************************************************************
 *  Definition macros of public constants
 *****************************************************************************/

/******************************************************************************
 *  Public function-like macros
 *****************************************************************************/

/******************************************************************************
 *  Definitions of public data types
 *****************************************************************************/

typedef struct {
    communication_t comm_handle;
    protocolo_t protocol;

    struct sigaction sa;
} writer_t;


/******************************************************************************
 *  Prototypes (declarations) of public functions
 *****************************************************************************/

void Writer_Create( writer_t *self, char *fifo_name );

void Writer_Run( writer_t *self );

void Writer_Destroy( writer_t *self );

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* WRITER_H */