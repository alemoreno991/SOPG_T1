#include "reader.h"

#define FIFO_NAME "myfifo"

int main(void)
{
    reader_t rx;

    Reader_Create( &rx, FIFO_NAME );
    Reader_Run( &rx );
    Reader_Destroy( &rx );

	return 0;
}