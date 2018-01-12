#include "headers.h"
#include "tap.h"

static int tap_fd;

static int tap_alloc(char *dev) {
    struct ifreq ifr;
    int fd;

    if ((fd = open("/dev/net/tap", O_RDWR)) < 0) {
        perror("open");
	exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;

    if (*dev)
	strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if (ioctl(fd, TUNSETIFF, (void *) &ifr) < 0) {
        perror("ioctl TUNSETIFF");
	close(fd);
	return -1;
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}

static int run_fcmd(char *cmd, ...) {
    char buf[CMDBUFLEN];
    va_list vl;

    va_start(vl, cmd);
    vsnprintf(buf, CMDBUFLEN, cmd, vl);
    va_end(vl);

    printf("%s\n", buf);
    return system(buf);
}

void tap_init(char *dev) {
    tap_fd = tap_alloc(dev);

    if (run_fcmd("ip link set dev %s up", dev))
	perror("ip link");
    
    if (run_fcmd("ip route add dev %s 10.0.0.0/24", dev))
	perror("ip route");
}

int tap_read(char *buf, int len) {
    return read(tap_fd, buf, len);
}

int tap_write(char *buf, int len) {
    return write(tap_fd, buf, len);
}
