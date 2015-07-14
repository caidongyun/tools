/*
 * BPF/bpf.h, Written by, Sohail Qayum Malik[sqm@hackers.pk]
 */

/* For printf(), should be removed when done */
#include<stdio.h>

/* man malloc(3) */
#include <stdlib.h>

#include <linux/if_ether.h>
#include <linux/filter.h>

#ifndef	BPF_HEADER
#define	BPF_HEADER

#define  ARP			"arp"
#define	 ARP_REQUEST		"request"
#define	 ARP_REPLY		"reply"
#define	 ARP_REQUEST_REPLY 	"request,reply"
#define	 ARP_REPLY_REQUEST	"reply,request"

#define	 IP			"ip"


#define	 PROMISCUOUS(x) (x & 0x01) 
#define	 PROTO_IP(x)	(x & 0x02)
#define	 PROTO_ARP(x)	(x & 0x04)

#define	MAX_LEN_OF_DEVICE_NAME	256

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {

   char device[MAX_LEN_OF_DEVICE_NAME];
   unsigned int flags;
}cmd;

int bpf(struct sock_filter **, unsigned short int, unsigned int);
/* 
 * ----------------------------
 * Very cmd specific allocation
 * -------------------------------
 * cmd, reference to pointer to an instance of cmd(the type)
 * dev, pointer to name of the device(the name is null terminated)
 * len, if the name of the device is null terminated then it should be zero other the length of the name of the device 
 * Returns 0 on error, otherwise it returns the total number of bytes allocated
 **/
size_t allocate(cmd*, char*, size_t);

#ifdef __cplusplus
}
#endif

/* jt = Jump if true to displacement starting from the very next instruction  
 *      Displacement it self is 0 origined */
/* jf = Jump if false to displacement starting from the very next instruction
 *      Displacement it self is 0 origined */

#define	 ldbA(ptr, index, offset, jtt, jff) \
			      (ptr + index)->code = BPF_LD | BPF_ABS | BPF_B;\
			      (ptr + index)->jt   = jtt;\
			      (ptr + index)->jf   = jff;\
			      (ptr + index)->k    = offset;

#define	 ldhA(ptr, index, offset, jtt, jff) \
	                      (ptr + index)->code = BPF_LD | BPF_ABS | BPF_H;\
                              (ptr + index)->jt  = jtt;\
			      (ptr + index)->jf  = jff;\
			      (ptr + index)->k   = offset;

#define	 ldA(ptr, index, offset, jtt, jff) \
	                      (ptr + index)->code = BPF_LD | BPF_ABS | BPF_W;\
                              (ptr + index)->jt  = jtt;\
                              (ptr + index)->jf  = jff;\
                              (ptr + index)->k   = offset;

#define	 jeqK(ptr, index, data, jtt, jff) \
			      (ptr + index)->code   = BPF_JMP | BPF_JEQ | \
                                                                 BPF_K;\
			      (ptr + index)->jt     = jtt;\
			      (ptr + index)->jf     = jff;\
			      (ptr + index)->k      = data;


/* data = The return instruction terminate the program and indicate how many bytes of the packet to accept. If the amount is 0, the packet will be rejected entirely. The actual amount accepted will be minimum of the length of the packet and the amount indicated by the filter */
#define	 retK(ptr, index, data, jtt, jff) \
	                      (ptr + index)->code = BPF_RET | BPF_K;\
			      (ptr + index)->jt   = jtt;\
			      (ptr + index)->jf   = jff;\
			      (ptr + index)->k    = data;

#endif			      









