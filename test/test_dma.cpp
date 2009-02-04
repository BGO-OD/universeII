#include <iostream>
#include "vmelib.h"

using namespace std;

int main()
{
    int i, offset;
    unsigned int base, *ptr;
    VMEBridge vme;

    base = vme.requestDMA();
    if (!base) {
        cerr << "Can't allocate DMA !\n";
        return 0;
    }

    vme.setOption(DMA, BLT_ON);

    offset = vme.DMAread(0xA2000000, 4096, A32, D32);
    if (offset < 0) {
        vme.releaseDMA();
        return 0;
    }

    ptr = (unsigned int *) (base + offset);

    for (i = 0; i < 10; i++)
        cout << i << ": " << hex << *ptr++ << dec << "!\n";

    vme.releaseDMA();

    return 0;
}
