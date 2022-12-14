/* use largest free space for allocation */
#include <assert.h>
#include <stdlib.h>

#include "mem.h"

int main() {
    assert(Mem_Init(4096) == 0);
    void* ptr[6];

    ptr[0] = Mem_Alloc(400, M_WORSTFIT);
    assert(ptr[0] != NULL);

    ptr[1] = Mem_Alloc(400, M_WORSTFIT);
    assert(ptr[1] != NULL);

    ptr[2] = Mem_Alloc(1000, M_WORSTFIT);
    assert(ptr[2] != NULL);

    ptr[3] = Mem_Alloc(1000, M_WORSTFIT);
    assert(ptr[3] != NULL);

    ptr[4] = Mem_Alloc(400, M_WORSTFIT);
    assert(ptr[4] != NULL);

    ptr[5] = Mem_Alloc(400, M_WORSTFIT);
    assert(ptr[5] != NULL);

    assert(Mem_Free(ptr[0]) == 0);
    ptr[0] = NULL;

    assert(Mem_Free(ptr[2]) == 0);
    ptr[2] = NULL;

    assert(Mem_Free(ptr[4]) == 0);
    ptr[4] = NULL;

    ptr[0] = Mem_Alloc(360, M_WORSTFIT);
    assert(ptr[0] != NULL);

    ptr[2] = Mem_Alloc(960, M_WORSTFIT);
    assert(ptr[2] == NULL);
    assert(m_error == E_NO_SPACE);

    exit(0);
}
