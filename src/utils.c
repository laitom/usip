#include "utils.h"

void pprint_ipv6pkt(struct usip_ipv6pkt *pkt) {
    PPRINT_HEADR("IPv6 packet");
    PPRINT_IPV6_FIELD("Version", pkt->hdr.version);
    PPRINT_IPV6_FIELD("Traffic class", pkt->hdr.traffic_cls);
    PPRINT_IPV6_FIELD("Flow label", pkt->hdr.flow_lbl);
    PPRINT_IPV6_FIELD("Payload length", pkt->hdr.payload_len);
    PPRINT_IPV6_FIELD("Next header", pkt->hdr.next_hdr);
    PPRINT_IPV6_FIELD("Hop limit", pkt->hdr.hop_lim);
    PPRINT_IPV6_ADDRFIELD("Source", pkt->hdr.source);
    PPRINT_IPV6_ADDRFIELD("Destination", pkt->hdr.dest);
    // TODO: Print payload
}

void pprint_ethfrm(struct usip_ethfrm *frm) {
    PPRINT_HEADR("Ethernet frame");
    PPRINT_MAC("Destination", frm->dest);
    PPRINT_MAC("Source", frm->source);
    printf("  %-20s%02x %02x\n", "Ethertype", (frm->ethertype & 0xFF00) >> 8, (frm->ethertype & 0x00FF));
}
