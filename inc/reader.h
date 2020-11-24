/**
 * @file reader.h
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
#ifndef READER_H
#define READER_H

/******************************************************************************
 *  Inclusions of public function dependencies
 *****************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
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

    FILE *sign, *log;

} reader_t;

/******************************************************************************
 *  Prototypes (declarations) of public functions
 *****************************************************************************/

void Reader_Create( reader_t *self, char *fifo_name );

void Reader_Run( reader_t *self );

void Reader_Destroy( reader_t *self );


/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* READER_H */