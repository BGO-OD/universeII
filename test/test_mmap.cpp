#include <iostream>
#include "vmelib.h"

using namespace std;

int main()
{
    int image, i;
    unsigned int *ptr;

    VMEBridge vme;

    image = vme.getImage(0xA2000000, 0x10000, A32, D32, MASTER);
    if (image < 0) {
        cerr << "Can't allocate master image !\n";
        return 0;
    }

    ptr = (unsigned int *) vme.getPciBaseAddr(image);
    for (i = 0; i < 1024; i++)
        cout << "i: " << hex << *ptr++ << dec << "!\n";

}
