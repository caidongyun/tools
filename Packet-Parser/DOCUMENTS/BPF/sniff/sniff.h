/*
 * sniff/sniff.h
 */

/* man perror(3) */
#include <stdio.h>

/* man packet(7) */
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>

/* man htons(3) */
#include <arpa/inet.h>

/* man netdevice(7) */
#include <sys/ioctl.h>
#include <linux/if.h>

/*  */
#include <linux/filter.h>

/* man strncpy(3) */
#include <string.h>

#include "../BPF/bpf.h"
#include "./constants.h"
