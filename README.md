# usip

To run (requires sudo):

```$ mknod /dev/net/tap c 10 200
$ chmod 0666 /dev/net/tap
$ make
$ ./usip
```