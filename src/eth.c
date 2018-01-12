#include "eth.h"

void init_ethfrm(struct usip_ethfrm *frm) {
    // This is only necessary because we are casting the buffer data directly to a usip_ethfrm struct
    frm->ethertype = htons(frm->ethertype);
}

uint32_t check_ethfrm_fcs(struct usip_ethfrm *frm, int offset) {
    return ((uint32_t)frm->data[offset] << 24)
	+ ((uint32_t)frm->data[offset+1] << 16)
	+ ((uint32_t)frm->data[offset+2] << 8)
	+ (uint32_t)frm->data[offset+3];
}
