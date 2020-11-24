/**
 * @file protocolo.h
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
#ifndef PROTOCOLO_H
#define PROTOCOLO_H

/******************************************************************************
 *  Inclusions of public function dependencies
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "communication.h"

/******************************************************************************
 *  Definition macros of public constants
 *****************************************************************************/

/******************************************************************************
 *  Public function-like macros
 *****************************************************************************/

/******************************************************************************
 *  Definitions of public data types
 *****************************************************************************/

typedef enum {
    SIGNAL,
    DATA
} protocolo_mode;

typedef struct {
    communication_t *named_fifo;
    protocolo_mode  rx_flag;
} protocolo_t;


/******************************************************************************
 *  Prototypes (declarations) of public functions
 *****************************************************************************/

void Protocolo_Create( protocolo_t *self, communication_t *comm_handle );

void Protocolo_Encode( protocolo_t *self, const char *msg, protocolo_mode mode );

protocolo_mode Protocolo_Decode( protocolo_t *self, char *buffer, int32_t buffer_len );

void Protocolo_Destroy( protocolo_t *self );

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* PROTOCOLO_H */