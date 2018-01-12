#include "ipv6.h"

void init_ipv6pkt(struct usip_ipv6pkt *pkt, struct usip_ethfrm *frm) {
    // first 4 bits
    pkt->hdr.version = (frm->data[0] & 0xF0) >> 4;
    
    // next 8 bits
    pkt->hdr.traffic_cls = ((frm->data[0] & 0xF) << 4) + ((frm->data[1] & 0xF0) >> 4);
    
    // next 20 bits
    pkt->hdr.flow_lbl = (((uint32_t)frm->data[1] & 0xF) << 16) + ((uint32_t)frm->data[2] << 8) + frm->data[3];

    // octets 5-6
    pkt->hdr.payload_len = ((uint16_t)frm->data[4] << 8) + frm->data[5];

    // octet 7
    pkt->hdr.next_hdr = frm->data[6];

    // octet 8
    pkt->hdr.hop_lim = frm->data[7];

    // octets 9-24
    for (int i = 0, o = 8; i < 8; ++i, o += 2)
	pkt->hdr.source[i] = ((uint16_t)frm->data[o] << 8) + frm->data[o+1];

    // octets 25-40
    for (int i = 0, o = 24; i < 8; ++i, o += 2)
	pkt->hdr.dest[i] = ((uint16_t)frm->data[o] << 8) + frm->data[o+1];

    // octets 41-(41+payload_len)
    pkt->payload = malloc(pkt->hdr.payload_len);
    for (int i = 0, o = 40; i < pkt->hdr.payload_len; ++i, ++o)
	pkt->payload[i] = frm->data[o];
}
