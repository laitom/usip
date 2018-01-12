#include "headers.h"
#include "tap.h"
#include "eth.h"
#include "ipv6.h"
#include "utils.h"

#define BUFLEN (ETH_FRAME_LEN+ETH_FCS_LEN)

static void handle_frame(struct usip_ethfrm *frm) {
    struct usip_ipv6pkt *pkt;
    
    switch(frm->ethertype) {
    case ETH_P_IP:
	printf("IPv4 packet\n");
	break;
    case ETH_P_ARP:
	printf("ARP packet\n");
	break;
    case ETH_P_IPV6:
	pkt = (struct usip_ipv6pkt *) malloc(sizeof(struct usip_ipv6pkt));
	init_ipv6pkt(pkt, frm);
	pprint_ipv6pkt(pkt);

	uint32_t crc = check_ethfrm_fcs(frm, LEN_IPV6PKT(pkt));
	printf("crc: %08x\n", crc);
	
	FREE_IPV6PKT(pkt);
	break;
    default:
	printf("Unrecognized packet\n");
	break;
    }
}

int main(int argc, char *argv[]) {
    char buf[BUFLEN];
    char *dev = (char *) calloc(10, sizeof(char));

    memset(&buf, 0, sizeof(buf));
    tap_init(dev);

    while (1) {
	if (tap_read(buf, BUFLEN) < 0)
	    perror("read");

	printf("\n");

	struct usip_ethfrm *frm = (struct usip_ethfrm *) buf;
	init_ethfrm(frm);
	
	handle_frame(frm);
	//pprint_ethfrm(frm);

	sleep(5);
    }
}
