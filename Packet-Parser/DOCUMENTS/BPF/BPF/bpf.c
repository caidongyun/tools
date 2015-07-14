/*
 * BPF/bpf.c, Written by, Sohail Qayum Malik[sqm@hackers.pk]
 */

#include "bpf.h"

/*
 @bpf,
 @type,
 @size, 
*/
int bpf(struct sock_filter **bpf, unsigned short int type, \
		                               unsigned int size) {

   int index = 0;

   *bpf = malloc(sizeof(struct sock_filter)*4);	
   if (*bpf == NULL)
      return 0;

   ldhA(*bpf, index, 12, 0, 0);
   index++;

   switch (type) {

      case ETH_P_IP:
	     	    
         jeqK(*bpf, index, ETH_P_IP, 1, 0);
	 index++;
	 retK(*bpf, index, 0, 0, 0);
         index++; 
      break;

      case ETH_P_ARP:

         jeqK(*bpf, index, ETH_P_ARP, 1, 0);
	 index++;
	 retK(*bpf, index, 0, 0, 0);
	 index++;         
      break;
   }

   retK(*bpf, index, size, 0, 0); 
   index++;

   return index;	
}

size_t allocate(cmd* ptr, char* dev, size_t len) {

   size_t ret = 0;

   printf("-----> cmd->device = %s\n", ptr->device);

   printf("---- %d ----\n", ptr->flags);       

   printf("--%d--\n", PROTO_ARP(ptr->flags));

   if ( PROMISCUOUS(ptr->flags) ) {

      printf("Promiscuous\n");
   }

   if ( PROTO_ARP(ptr->flags) ) {

      printf("PROTO_ARP\n");
   }

   if ( PROTO_IP(ptr->flags) ) {

      printf("PROTO_IP\n");
   }

   return ret;
}
