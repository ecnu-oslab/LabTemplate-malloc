/* check first pointer returned is 8-byte aligned */
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "mem.h"

int main() {
    assert(Mem_Init(4096) == 0);
    void* ptr = Mem_Alloc(8, M_FIRSTFIT);
    assert(ptr != NULL);
    uintptr_t addr = (uintptr_t)ptr;
    assert(addr % 8 == 0);
    exit(0);
}
