#ifndef USIP_UTILS_H
#define USIP_UTILS_H

#include "headers.h"
#include "eth.h"
#include "ipv6.h"

#define FREE_ETHFRM(frm) ({ free((frm)->payload); free((frm)); })
#define FREE_IPV6PKT(pkt) ({ free((pkt)->payload); free((pkt)); })
#define LEN_IPV6PKT(pkt) ((uint32_t) (40+(pkt->hdr.payload_len)))

#define PPRINT_HEADR(s) (printf("%s\n", (s)))
#define PPRINT_IPV6_FIELD(s, u) (printf("  %-20s%u\n", (s), (u)))
#define PPRINT_IPV6_ADDRFIELD(s, a)				\
    ({								\
	printf("  %-20s%02x", (s), (a[0]));			\
	for (int i = 1; i < 8; ++i) printf(":%02x", (a[i]));	\
	printf("\n");						\
    })
#define PPRINT_MAC(s, a)					\
    ({								\
	printf("  %-20s%02x ", (s), (a[0]));			\
	for (int i = 0; i < sizeof((a))/sizeof((a[0])); ++i)	\
	    printf("%02x ", (a[i]));				\
	printf("\n");						\
    })

void pprint_ethfrm(struct usip_ethfrm *frm);
void pprint_ipv6pkt(struct usip_ipv6pkt *pkt);
void print_ethfrm_hexdmp(struct usip_ethfrm *frm);

#endif // USIP_UTILS_H
