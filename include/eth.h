#ifndef USIP_ETH_H
#define USIP_ETH_H

#include <linux/if_ether.h>
#include "headers.h"

struct usip_ethfrm {
    uint8_t dest[ETH_ALEN];      // MAC destination
    uint8_t source[ETH_ALEN];    // MAC source
    uint16_t ethertype;          // Ethertype
    uint8_t *data;              // Payload + FCS
};

int init_ethfrm(struct usip_ethfrm *frm, uint8_t *buf, int buf_len);
uint32_t check_ethfrm_fcs(struct usip_ethfrm *frm, int offset);

#endif // USIP_ETH_H
