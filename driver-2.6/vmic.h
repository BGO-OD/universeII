/*
    Some defines for VMIC CPUs used by universeII.c
    Copyright (C) 2002 Andreas Ehmanns <ehmanns@iskp.uni-bonn.de>
 
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

// Use only together with VMIC CPU !!!

#define VMIC_VEND_ID                0x114a
#define VMIC_FPGA_DEVICE_ID1        0x0004
#define VMIC_FPGA_DEVICE_ID2        0x0005
#define VMIC_FPGA_DEVICE_ID3        0x0006
#define VMIC_FPGA_BASE_ADDR_REG     0x10

#define FPGA_COMM_OFFSET            0x00
#define FPGA_VBAR_OFFSET            0x04
#define FPGA_VBAMR_OFFSET           0x08


#define MEC_BE        0x0001    // master endian conversion big endian
#define MEC_LE        0x0000    // master endian conversion little endian

#define SEC_BE        0x0002    // slave endian conversion big endian
#define SEC_LE        0x0000    // slave endian conversion little endian

#define BERR_LATCH_EN 0x0004    // bus error latch enable

#define BTO_EN        0x0008    // bus timeout timer enable
#define BTO_16        0x0000    // bus timeout 16 us
#define BTO_64        0x0010    // bus timeout 64 us
#define BTO_256       0x0020    // bus timeout 256 us
#define BTO_1MS       0x0030    // bus timeout 1 ms

#define BERR_INT_EN   0x0040    // bus error interrupt enable

#define BERR_STAT_CLR 0x0080    // bus error status/clear R/W1C

#define WD_SYSFAIL    0x0100    // watchdog to VME sysfail enable

#define BYPASS_EN     0x0400    // bypass enable - MEC/SEC must be set to LE

#define VME_EN        0x0800    // vmebus enable
