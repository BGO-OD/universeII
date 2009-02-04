#include <iostream>
#include "vmelib.h"

using namespace std;


int main()
{
  int image,i;
  unsigned int dummy32;
  VMEBridge vme;

  image = vme.getImage(0xA2000000, 0x10000, A32, D32, MASTER);
  if (image < 0)
  {
    cerr << "Can't allocate master image !\n";
    return 0;
  }

  for (i = 0; i < 16; i++)
  {
    vme.rl(image, 0xA2000000 + i*4, &dummy32);
    cout << i << ": " << hex << dummy32 << dec << "!\n";
  }

}
