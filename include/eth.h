#ifndef USIP_ETH_H
#define USIP_ETH_H

#include <linux/if_ether.h>
#include "headers.h"

struct usip_ethfrm {
    uint8_t dest[ETH_ALEN];      // MAC destination
    uint8_t source[ETH_ALEN];    // MAC source
    uint16_t ethertype;          // Ethertype
    uint8_t *payload;            // Payload
    uint8_t fcs[4];              // FCS

    int payload_len;
};

int init_ethfrm(struct usip_ethfrm *frm, char *buf, int buf_len);
int check_ethfrm_fcs(struct usip_ethfrm *frm);

#endif // USIP_ETH_H
