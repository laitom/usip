#include "eth.h"

static int payload_len_from_ipv6pkt(uint8_t *data) {
    uint16_t payload_len = (data[4] << 8) + data[5];
    return 40+payload_len;
}

static int payload_len_from_ethertype(uint16_t ethertype, uint8_t *data) {
    switch(ethertype) {
    case ETH_P_IPV6:
	return payload_len_from_ipv6pkt(data);
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

    for (i = 0; i < ETH_ALEN; ++i) {
	frm->dest[i] = *(bbuf+i);
	frm->source[i+ETH_ALEN] = *(bbuf + (i+ETH_ALEN));
    }

    uint8_t ethertype_msb = *(bbuf + ETH_ALEN*2);
    uint8_t ethertype_lsb = *(bbuf + ETH_ALEN*2 + 1);
    frm->ethertype = ((uint16_t)ethertype_msb << 8) + ethertype_lsb;

    frm->payload_len = payload_len_from_ethertype(frm->ethertype, bbuf);

    // This shouldn't cause issues, since according to http://pubs.opengroup.org/onlinepubs/009695399/functions/malloc.html,
    // malloc(0) returns a pointer that can be safely passed to free()
    frm->payload = (uint8_t *) malloc(frm->payload_len * sizeof(uint8_t));
    for (i = 0; i < frm->payload_len; ++i)
	frm->payload[i] = bbuf[ETH_HLEN+i];

    for (i = 0; i < 4; ++i)
	frm->fcs[i] = bbuf[ETH_HLEN + frm->payload_len + i];

    return 0;
}

uint32_t check_ethfrm_fcs(struct usip_ethfrm *frm, int offset) {
    return 0;
}
