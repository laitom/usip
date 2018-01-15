#include "eth.h"

int init_ethfrm(struct usip_ethfrm *frm, uint8_t *buf, int buf_len) {
    if (buf_len <= ETH_HLEN)
	return 1;

    for (int i = 0; i < ETH_ALEN; ++i) {
	frm->dest[i] = *(buf+i);
	frm->source[i+ETH_ALEN] = *(buf + (i+ETH_ALEN));
    }

    uint8_t ethertype_msb = *(buf + ETH_ALEN*2);
    uint8_t ethertype_lsb = *(buf + ETH_ALEN*2 + 1);
    frm->ethertype = ((uint16_t)ethertype_msb << 8) + ethertype_lsb;

    int data_len = buf_len-ETH_HLEN;
    frm->data = (uint8_t *) malloc(data_len*(sizeof(uint8_t)));

    if (frm->data == NULL)
	return 1;

    for (int i = 0; i < data_len; ++i)
	frm->data[i] = buf[ETH_HLEN+i];

    return 0;
}

uint32_t check_ethfrm_fcs(struct usip_ethfrm *frm, int offset) {
    return ((uint32_t)frm->data[offset] << 24)
	+ ((uint32_t)frm->data[offset+1] << 16)
	+ ((uint32_t)frm->data[offset+2] << 8)
	+ (uint32_t)frm->data[offset+3];
}
