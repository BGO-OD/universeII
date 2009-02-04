INCLUDE = -I/usr/src/linux/include/
CFLAGS = -O2 -Wall

universeII.o: universeII.c
	gcc ${INCLUDE} ${CFLAGS} -D__KERNEL__ -c universeII.c

clean:
	rm universeII.o

devices:
	mknod /dev/vme_m0  c 221 0
	mknod /dev/vme_m1  c 221 1
	mknod /dev/vme_m2  c 221 2
	mknod /dev/vme_m3  c 221 3
	mknod /dev/vme_m4  c 221 4
	mknod /dev/vme_m5  c 221 5
	mknod /dev/vme_m6  c 221 6
	mknod /dev/vme_m7  c 221 7
	mknod /dev/vme_ctl c 221 8
	mknod /dev/vme_dma c 221 9
	mknod /dev/vme_s0  c 221 10
	mknod /dev/vme_s1  c 221 11
	mknod /dev/vme_s2  c 221 12
	mknod /dev/vme_s3  c 221 13
	mknod /dev/vme_s4  c 221 14
	mknod /dev/vme_s5  c 221 15
	mknod /dev/vme_s6  c 221 16
	mknod /dev/vme_s7  c 221 17
	chown root /dev/vme*
	chgrp users /dev/vme*
	chmod 666 /dev/vme*
