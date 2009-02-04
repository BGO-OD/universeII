#include <iostream>
#include "vmelib.h"

using namespace std;

int main()
{
    VMEBridge vme;

    vme.setupMBX(2);
    cout << "Waiting for mailbox 2 ..." << flush;

    cout << "back with message " << hex << vme.waitMBX(2, 10) << dec << endl;

    vme.releaseMBX(2);

    return 0;
}
