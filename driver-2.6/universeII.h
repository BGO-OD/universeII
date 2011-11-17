/*
    Linux driver for Tundra universeII PCI to VME bridge, kernel 2.4.x and 2.6.x
    Copyright (C) 2006 Andreas Ehmanns <universeII@gmx.de>
 
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

#ifndef UNIVERSEII_H
#define UNIVERSEII_H


// structure to handle image related paramters

typedef struct {
    unsigned int phys_start;    // Start addr of PCI image
    unsigned int phys_end;      // End addr of PCI image
    unsigned int size;          // Size of image
    void __iomem *vBase;        // Virtual image base PCI address
    int okToWrite;              // Indicates that image is ready to be used
    int opened;                 // Indicated different states during open process
    void __iomem *slaveBuf;     // Slave buffer address in kernel space
    dma_addr_t buffer;          // Slave buffer address in PCI address space
} image_desc_t;


// structure to driver statistics

typedef struct {
    unsigned long reads;
    unsigned long writes;
    unsigned long ioctls;
    unsigned long irqs;
    unsigned long berrs;
    unsigned long dmaErrors;
    unsigned long timeouts;
} driver_stats_t;


// structure for VMEBus irq handling

typedef struct {
    int ok;
    void __iomem *vmeAddrSt;
    u32 vmeValSt;
    void __iomem *vmeAddrCl;
    u32 vmeValCl;
    wait_queue_head_t irqWait;
    struct timer_list virqTimer;
} irq_device_t;


// data structure of the DMA command packets

typedef struct {
    u32 dctl;                 // DMA transfer control register
    u32 dtbc;                 // DMA transfer byte count
    u32 dla;                  // DMA PCI bus address
    u32 reserved1;
    u32 dva;                  // DMA VMEBus address
    u32 reserved2;
    u32 dcpp;                 // DMA command packet pointer
    u32 reserved3;
} DMA_cmd_packet_t;


// structure for handling of VME bus errors

typedef struct {
    unsigned char valid;
    unsigned char AM;
    u32 address;
    unsigned char merr;
} vme_Berr_t;


// structure for one command packet list

struct cpl
{
    DMA_cmd_packet_t *dcp;      // Pointer to array of command packets
    dma_addr_t start;           // Start address for DMA in PCI address space
    unsigned int packets;       // Number of packets in the list
};


#define PCI_VENDOR_ID_TUNDRA            0x10e3
#define PCI_DEVICE_ID_TUNDRA_CA91C042   0x0000


#define CONFIG_REG_SPACE 0xA0000000

#define PCI_ID          0x0000
#define PCI_CSR         0x0004
#define PCI_CLASS       0x0008
#define PCI_MISC0       0x000C
#define PCI_BS          0x0010
#define PCI_MISC1       0x003C

// Master images 0 .. 7

#define LSI0_CTL        0x0100
#define LSI0_BS         0x0104
#define LSI0_BD         0x0108
#define LSI0_TO         0x010C

#define LSI1_CTL	0x0114
#define LSI1_BS		0x0118
#define LSI1_BD		0x011C
#define LSI1_TO		0x0120

#define LSI2_CTL	0x0128
#define LSI2_BS		0x012C
#define LSI2_BD		0x0130
#define LSI2_TO		0x0134

#define LSI3_CTL	0x013C
#define LSI3_BS		0x0140
#define LSI3_BD		0x0144
#define LSI3_TO		0x0148

#define LSI4_CTL	0x01A0
#define LSI4_BS		0x01A4
#define LSI4_BD		0x01A8
#define LSI4_TO		0x01AC

#define LSI5_CTL	0x01B4
#define LSI5_BS		0x01B8
#define LSI5_BD		0x01BC
#define LSI5_TO		0x01C0

#define LSI6_CTL	0x01C8
#define LSI6_BS		0x01CC
#define LSI6_BD		0x01D0
#define LSI6_TO		0x01D4

#define LSI7_CTL	0x01DC
#define LSI7_BS		0x01E0
#define LSI7_BD		0x01E4
#define LSI7_TO		0x01E8


// Slave images 0 .. 7

#define VSI0_CTL        0x0F00
#define VSI0_BS         0x0F04
#define VSI0_BD         0x0F08
#define VSI0_TO         0x0F0C

#define VSI1_CTL        0x0F14
#define VSI1_BS         0x0F18
#define VSI1_BD         0x0F1C
#define VSI1_TO         0x0F20

#define VSI2_CTL        0x0F28
#define VSI2_BS         0x0F2C
#define VSI2_BD         0x0F30
#define VSI2_TO         0x0F34

#define VSI3_CTL        0x0F3C
#define VSI3_BS         0x0F40
#define VSI3_BD         0x0F44
#define VSI3_TO         0x0F48

#define VSI4_CTL        0x0F90
#define VSI4_BS         0x0F94
#define VSI4_BD         0x0F98
#define VSI4_TO         0x0F9C

#define VSI5_CTL        0x0FA4
#define VSI5_BS         0x0FA8
#define VSI5_BD         0x0FAC
#define VSI5_TO         0x0FB0

#define VSI6_CTL        0x0FB8
#define VSI6_BS         0x0FBC
#define VSI6_BD         0x0FC0
#define VSI6_TO         0x0FC4

#define VSI7_CTL        0x0FCC
#define VSI7_BS         0x0FD0
#define VSI7_BD         0x0FD4
#define VSI7_TO         0x0FD8


#define SCYC_CTL	0x0170
#define SCYC_ADDR       0x0174
#define SCYC_EN		0x0178
#define SCYC_CMP	0x017C
#define SCYC_SWP	0x0180
#define LMISC		0x0184
#define SLSI		0x0188
#define L_CMDERR	0x018C
#define LAERR		0x0190

#define DCTL		0x0200
#define DTBC		0x0204
#define DLA	        0x0208
#define DVA	        0x0210
#define DCPP		0x0218
#define DGCS		0x0220
#define D_LLUE		0x0224

#define LINT_EN		0x0300
#define LINT_STAT	0x0304
#define LINT_MAP0	0x0308
#define LINT_MAP1	0x030C
#define LINT_MAP2	0x0340
#define VINT_EN		0x0310
#define VINT_STAT	0x0314
#define VINT_MAP0	0x0318
#define VINT_MAP1	0x031C
#define STATID		0x0320
#define V1_STATID	0x0324
#define V2_STATID	0x0328
#define V3_STATID	0x032C
#define V4_STATID	0x0330
#define V5_STATID	0x0334
#define V6_STATID	0x0338
#define V7_STATID	0x033C

#define MAILBOX0        0x0348
#define MAILBOX1        0x034C
#define MAILBOX2        0x0350
#define MAILBOX3        0x0354

#define MAST_CTL	0x0400
#define MISC_CTL	0x0404
#define MISC_STAT	0x0408
#define USER_AM		0x040C

#define VRAI_CTL	0x0F70
#define VRAI_BS		0x0F74
#define VCSR_CTL	0x0F80
#define VCSR_TO		0x0F84
#define V_AMERR		0x0F88
#define VAERR		0x0F8C

#define VCSR_CLR	0x0FF4
#define VCSR_SET	0x0FF8
#define VCSR_BS		0x0FFC

#endif
