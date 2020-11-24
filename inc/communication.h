/**
 * @file communication.h
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
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/******************************************************************************
 *  Inclusions of public function dependencies
 *****************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/******************************************************************************
 *  Definition macros of public constants
 *****************************************************************************/
#define BUFFER_SIZE 300

/******************************************************************************
 *  Public function-like macros
 *****************************************************************************/

/******************************************************************************
 *  Definitions of public data types
 *****************************************************************************/

typedef enum {
    WRITE_ONLY,
    READ_ONLY
} comm_mode;

typedef struct {
    int32_t fd;
    char *node_name;

    bool rx_pending;

} communication_t;

/******************************************************************************
 *  Prototypes (declarations) of public functions
 *****************************************************************************/

bool Communication_Create( communication_t *self,
                           const char *node_name,
                           int32_t permissions,
                           comm_mode mode );

bool Communication_Send( communication_t *self, const char *msj );

bool Communication_Receive( communication_t *self, 
                            char *buffer_rx, 
                            uint32_t buffer_size );

bool Communication_Destroy( communication_t *self );

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* COMMUNICATION_H */