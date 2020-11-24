#include "writer.h"

#define FIFO_NAME "myfifo"

int main(void)
{
    writer_t tx;

    Writer_Create( &tx, FIFO_NAME );
    Writer_Run( &tx );
    Writer_Destroy( &tx );

	return 0;
}
