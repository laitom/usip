#ifndef USIP_TAP_H
#define USIP_TAP_H

#define CMDBUFLEN 100

void tap_init(char *dev);
int tap_read(char *buf, int len);
int tap_write(char *buf, int len);

#endif // USIP_TAP_H
