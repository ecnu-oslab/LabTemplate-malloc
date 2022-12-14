/* a few aligned allocations and frees */
#include <assert.h>
#include <stdlib.h>

#include "mem.h"

int main() {
    assert(Mem_Init(4096) == 0);
    void* ptr[4];

    ptr[0] = Mem_Alloc(8, M_FIRSTFIT);
    ptr[1] = Mem_Alloc(16, M_FIRSTFIT);
    assert(Mem_Free(ptr[0]) == 0);
    assert(Mem_Free(ptr[1]) == 0);

    ptr[2] = Mem_Alloc(32, M_FIRSTFIT);
    ptr[3] = Mem_Alloc(8, M_FIRSTFIT);
    assert(Mem_Free(ptr[2]) == 0);
    assert(Mem_Free(ptr[3]) == 0);

    exit(0);
}
