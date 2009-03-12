/*
    A simple VMEBus debugger
    Copyright (C) 2008 Andreas Ehmanns <universeII@gmx.de>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "vmelib.h"

static char Version[] = "0.94 (January 2008)";
VMEBridge vme;


int allocImage(unsigned int *addr, unsigned int vdw)
{
    int vas, image;

    if ((*addr & 0xFFFF0000) == 0xFFFF0000) // A16 cycle
    {
        vas = A16;
        *addr &= 0x0000FFFF;
    } else if ((*addr & 0xFF000000) == 0xFF000000)  // A24 cycle
    {
        vas = A24;
        *addr &= 0x00FFFFFF;
    } else
        vas = A32;  // A32 cycle

    image = vme.getImage(*addr & 0xFFFF0000, 0x10000, vas, vdw, MASTER);
    vme.setOption(image, POST_WRITE_DIS);
    cout << image << endl;
    return image;
}


void menue(char *comm)
{

    int i, image, count;
    unsigned int addr, addr2, val;
    unsigned short val16;
    unsigned char val8;
    char command[80], piece[80], value[80], address[80], start[80], end[80];
    istringstream ist;

    cout << "\nVME-Linux debugger, Version " << Version
         << "\nType 'help' for a short list of commands.\n\n\n";
    do {
        ist.clear();
        if (strcmp(comm, "\0"))
            ist >> comm;
        else {
            cout << "debug: " << flush;
            cin.getline(command, 80);
            ist.str(command);
        }

        ist >> piece;
        if (ist.fail())
            cerr << "Command not understood !\n";

        if (!strcmp(piece, "wl")) {
            if (!(ist >> address) || !(ist >> value))
                cerr << "Usage: wl address value\n";
            else {
                sscanf(address, "%x", &addr);
                sscanf(value, "%x", &val);
                image = allocImage(&addr, D32);
                vme.wl(image, addr, val);
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "rl")) {
            if (!(ist >> address))
                cerr << "Usage: rl address\n";
            else {
                sscanf(address, "%x", &addr);
                image = allocImage(&addr, D32);
                if (!vme.rl(image, addr, &val))
                    cout << "    " << hex << addr << ": " << val << dec << "\n";
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "ww")) {
            if (!(ist >> address) || !(ist >> value))
                cerr << "Usage: ww address value\n";
            else {
                sscanf(address, "%x", &addr);
                sscanf(value, "%hx", &val16);
                image = allocImage(&addr, D16);
                vme.ww(image, addr, val16);
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "rw")) {
            if (!(ist >> address))
                cerr << "Usage: rw address\n";
            else {
                sscanf(address, "%x", &addr);
                image = allocImage(&addr, D16);
                if (!vme.rw(image, addr, &val16))
                    cout << "    " << hex << addr << ": " << val16 << dec <<
                        "\n";
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "wb")) {
            if (!(ist >> address) || !(ist >> value))
                cerr << "Usage: wb address value\n";
            else {
                sscanf(address, "%x", &addr);
                sscanf(value, "%hx", &val16);
                image = allocImage(&addr, D8);
                vme.wb(image, addr, val16 & 0x00FF);
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "rb")) {
            if (!(ist >> address))
                cerr << "Usage: rb address\n";
            else {
                sscanf(address, "%x", &addr);
                image = allocImage(&addr, D8);
                if (!vme.rb(image, addr, &val8))
                    cout << "    " << hex << addr << ": " << ((unsigned int)
                                                              val8)
                        << dec << "\n";
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "test")) {
            if (!(ist >> address))
                cerr << "Usage: test address\n";
            else {
                sscanf(address, "%x", &addr);
                image = allocImage(&addr, D32);
                if (vme.there(addr))
                    cout << " Address " << hex << addr << dec <<
                        " is valid!\n\n";
                else
                    cout << " Address " << hex << addr << dec <<
                        " not found!\n\n";
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "d")) {
            if (!(ist >> address))
                cerr << "Usage: d address\n" << "address: " << address << "!\n";
            else {
                sscanf(address, "%x", &addr);
                image =
                    vme.getImage(addr & 0xFFFFFF00, 0x10000, A32, D32, MASTER);
                for (i = 0; i < 8; i++) {
                    if (!vme.rl(image, addr + 4 * i, &val))
                        printf("    %08x:  %08x\n", addr + 4 * i, val);
                }
                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "mfill")) {
            if (!(ist >> start) || !(ist >> end) || !(ist >> value))
                cerr << "Usage: mfill start_address end_address value\n";
            else {
                sscanf(start, "%x", &addr);
                sscanf(end, "%x", &addr2);
                sscanf(value, "%x", &val);
                count = addr2 - (addr & 0xffffff00);
                count = (((count - 1) / 0x10000) + 1) * 0x10000;

                image =
                    vme.getImage(addr & 0xFFFFFF00, count, A32, D32, MASTER);
                count = (addr2 - addr + 1) / 4;

                for (i = 0; i < count; i++)
                    vme.wl(image, addr + 4 * i, val);

                vme.releaseImage(image);
            }
        }

        if (!strcmp(piece, "help") || !strcmp(piece, "h"))
            cout << "\n\nPossible commands:\n"
                 << "rl address - read long word at 'address'\n"
                 << "wl address value - write long word 'value' at 'address'\n"
                 << "rw address - read word at 'address'\n"
                 << "ww address value - write word 'value' at 'address'\n"
                 << "rb address - read byte at 'address'\n"
                 << "wb address value - write byte 'value' at 'address'\n"
                 << "d address - dumps data from 'address' to 'address+8'\n"
                 << "mfill start end data - fills adresses from 'start' until "
                 << "'end' with value 'data'\n"
                 << "test address - test if VMEBus address 'address' exists\n\n"
                 << "q - quit program\n\n" << flush;

    } while (strcmp(piece, "q") && (!strcmp(comm, "\0")));

}

int main(int argc, char **argv)
{
    int i;
    char comarg[80] = "\0";

    for (i = 1; i < argc; i++) {
        strcat(comarg, argv[i]);
        strcat(comarg, " ");
    }

    menue(comarg);

    return 0;
}
