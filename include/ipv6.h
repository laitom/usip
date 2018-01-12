/*
 * Useful resources:
 *
 * IPv6 Specification
 *     https://tools.ietf.org/html/rfc2460
 * IPv6 Flow Label Specification
 *     https://tools.ietf.org/html/rfc6437
 */

#ifndef USIP_IPV6_H
#define USIP_IPV6_H

#include "headers.h"
#include "eth.h"

struct usip_ipv6hdr {
    uint8_t  version;
    uint8_t  traffic_cls;
    uint32_t flow_lbl;
    uint16_t payload_len;
    uint8_t  next_hdr;
    uint8_t  hop_lim;
    uint16_t source[8];
    uint16_t dest[8];
};

struct usip_ipv6pkt {
    struct usip_ipv6hdr hdr;
    uint8_t *payload;
};

void init_ipv6pkt(struct usip_ipv6pkt *pkt, struct usip_ethfrm *frm);

#endif // USIP_IPV6_h
