#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "../port/error.h"
#include "interp.h"

#include "pc64.root.h"

ulong ndevs = 29;
extern Dev rootdevtab;
extern Dev consdevtab;
extern Dev archdevtab;
extern Dev envdevtab;
extern Dev mntdevtab;
extern Dev pipedevtab;
extern Dev progdevtab;
extern Dev rtcdevtab;
extern Dev srvdevtab;
extern Dev dupdevtab;
extern Dev ssldevtab;
extern Dev capdevtab;
extern Dev drawdevtab;
extern Dev pointerdevtab;
extern Dev vgadevtab;
extern Dev ipdevtab;
extern Dev etherdevtab;
extern Dev audiodevtab;
extern Dev uartdevtab;
extern Dev sddevtab;
extern Dev tinyfsdevtab;
Dev* devtab[29]={
	&rootdevtab,
	&consdevtab,
	&archdevtab,
	&envdevtab,
	&mntdevtab,
	&pipedevtab,
	&progdevtab,
	&rtcdevtab,
	&srvdevtab,
	&dupdevtab,
	&ssldevtab,
	&capdevtab,
	&drawdevtab,
	&pointerdevtab,
	&vgadevtab,
	&ipdevtab,
	&etherdevtab,
	&audiodevtab,
	&uartdevtab,
	&sddevtab,
	&tinyfsdevtab,
	nil,
};

extern void ether2114xlink(void);
extern void ethervirtiolink(void);
void links(void){
	ether2114xlink();
	ethervirtiolink();
}

extern void sysmodinit(void);
extern void drawmodinit(void);
extern void tkmodinit(void);
extern void keyringmodinit(void);
extern void mathmodinit(void);
void modinit(void){
	sysmodinit();
	drawmodinit();
	tkmodinit();
	keyringmodinit();
	mathmodinit();
}

extern PCArch archgeneric;
extern PCArch archmp;
PCArch* knownarch[] = {
	&archgeneric,
	&archmp,
	nil,
};

#include "../port/sd.h"
extern SDifc sdvirtioifc;
SDifc* sdifc[] = {
	&sdvirtioifc,
	nil,
};

extern PhysUart i8250physuart;
PhysUart* physuart[] = {
	&i8250physuart,
	nil,
};

#include <draw.h>
#include <memdraw.h>
#include "screen.h"
extern VGAdev vgavesadev;
VGAdev* vgadev[] = {
	&vgavesadev,
	nil,
};

extern VGAcur vgasoftcur;
VGAcur* vgacur[] = {
	&vgasoftcur,
	nil,
};

#include "../ip/ip.h"
extern void tcpinit(Fs*);
extern void udpinit(Fs*);
extern void ipifcinit(Fs*);
extern void icmpinit(Fs*);
extern void icmp6init(Fs*);
extern void ipmuxinit(Fs*);
void (*ipprotoinit[])(Fs*) = {
	tcpinit,
	udpinit,
	ipifcinit,
	icmpinit,
	icmp6init,
	ipmuxinit,
	nil,
};

	int kernel_pool_pcnt = 10;
	int main_pool_pcnt = 40;
	int heap_pool_pcnt = 20;
	int image_pool_pcnt = 40;
	int cflag=0;
	int swcursor=0;
	int consoleprint=1;
char* conffile = "pc64";
ulong kerndate = KERNDATE;
