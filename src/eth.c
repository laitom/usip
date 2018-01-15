#include "eth.h"

static int payload_len_from_ipv6pkt(uint8_t *payload) {
    uint16_t payload_len = (((uint16_t) payload[4]) << 8) + payload[5];
    return 40+payload_len;
}

static int payload_len_from_ethertype(uint16_t ethertype, uint8_t *payload) {
    switch(ethertype) {
    case ETH_P_IPV6:
	return payload_len_from_ipv6pkt(payload);
	break;
    default:
	return 0;
	break;
    }
}

int init_ethfrm(struct usip_ethfrm *frm, char *buf, int buf_len) {
    int i;
    uint8_t *bbuf = (uint8_t *) buf;
    
    if (buf_len <= ETH_HLEN)
	return 1;

    // The first six octets of buf contain the destination address, the next six contain the source address
    for (i = 0; i < ETH_ALEN; ++i) {
	frm->dest[i] = *(bbuf+i);
	frm->source[i] = *(bbuf + (i+ETH_ALEN));
    }

    // Octets 13 and 14 contain the MSB and the LSB of the Ethertype
    uint8_t ethertype_msb = *(bbuf + ETH_ALEN*2);
    uint8_t ethertype_lsb = *(bbuf + ETH_ALEN*2 + 1);
    frm->ethertype = ((uint16_t)ethertype_msb << 8) + ethertype_lsb;

    // Since the Ethernet header doesn't contain length information, we have to dig inside the L3 packet to calculate it
    // so that we can allocate the right amount of memory for the payload.
    frm->payload_len = payload_len_from_ethertype(frm->ethertype, bbuf);

    // Return 1 if payload size exceeds max Ethernet frame payload size
    if (frm->payload_len > ETH_DATA_LEN)
	return 1;
    
    frm->payload = (uint8_t *) malloc(frm->payload_len * sizeof(uint8_t));

    // Octets from 15 onwards contain the payload of the Ethernet frame
    for (i = 0; i < frm->payload_len; ++i)
	frm->payload[i] = bbuf[ETH_HLEN+i];

    // The last 4 octets of the frame contain the frame check sequence
    for (i = 0; i < 4; ++i)
	frm->fcs[i] = bbuf[ETH_HLEN + frm->payload_len + i];

    return 0;
}

int check_ethfrm_fcs(struct usip_ethfrm *frm) {
    return 0;
}
