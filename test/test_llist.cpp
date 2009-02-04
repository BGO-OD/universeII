#include <iostream>
#include "vmelib.h"

using namespace std;

int main()
{
    int image, i, list;
    unsigned int base, *ptr, packets[5];
    VMEBridge vme;

    image = vme.getImage(0xA2000000, 0x10000, A32, D32, MASTER);
    if (image < 0) {
        cerr << "Can't allocate master image !\n";
        return 0;
    }

    list = vme.newCmdPktList();
    cout << "List number is " << list << "!\n";

    packets[0] = vme.addCmdPkt(list, 0, 0xA2000000, 16, A32, D32);
    packets[1] = vme.addCmdPkt(list, 0, 0xA2000100, 32, A32, D32);
    packets[2] = vme.addCmdPkt(list, 0, 0xA2000300, 4, A32, D32);
    packets[3] = vme.addCmdPkt(list, 0, 0xA2000404, 16, A32, D32);
    packets[4] = vme.addCmdPkt(list, 0, 0xA2000508, 16, A32, D32);

    base = vme.requestDMA();
    if (base == 0)
        return 0;

    cout << "Executing list ..." << flush;
    if (!vme.execCmdPktList(list)) {
        cout << "done !\n";

        ptr = (unsigned int *) (base + packets[0]);
        for (i = 0; i < 4; i++)
            cout << i << " = " << hex << *ptr++ << dec << "!\n";
    }

    vme.releaseDMA();
    vme.delCmdPktList(list);

    return 0;
}
