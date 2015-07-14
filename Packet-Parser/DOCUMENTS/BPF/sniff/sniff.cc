// sniff/sniff.cc
// Written by, Sohail Qayum Malik[sqm@hackers.pk]

#include "sniff.hh"

int sniff(const int argc, char const*const* argv, \
		    const int common_argc, char const*const* common_argv) {
   
   int count = 0, ret = 0, sockfd;
   char packet[IFNAMSIZ];

   /* struct sock_filter *bpf_code = NULL; */
   char *bpf_code = NULL;
   struct sock_fprog filter;

   struct sockaddr_ll sall;
   struct ifreq interface;

#ifdef	EXT3GREP_INIT_H
   args arg(argc, argv, COMMANDS, sniff_init);
#else
   args arg(argc, argv, COMMANDS);
#endif 
   
   args::iterator iter(arg.begin());

   sall.sll_family = AF_PACKET;
   sall.sll_protocol = htons(ETH_P_ALL);

   cmd bpf_cmd;
#ifdef	SNIFF_DEBUG   
   bool promiscuous = false;
   bool protocol = false;
#endif   

   if ( iter[DEVICE] ) {

#ifdef	SNIFF_DEBUG
      std::cout<<"DEVICE->";
#endif

      if ( iter++ ) {

         /* Get device name here */
#ifdef	 SNIFF_DEBUG	 
	 std::cout<<*iter<<"->";
#endif	 
	 strcpy(bpf_cmd.device, (*iter).c_str());

      }
      else {
         /* No device name is not given take necessary measures */
#ifdef	 SNIFF_DEBUG	 
	 std::cout<<"Setting device to default("<<DEFAULT_DEVICE<<")->";
#endif	 

	 strcpy(bpf_cmd.device, DEFAULT_DEVICE);
      }
      
      if ( iter[IN] ) {

         if ( iter++ ) {
       
            if ( (*iter).compare("promiscuous") == 0 ) {
#ifdef	 SNIFF_DEBUG
               std::cout<<"in promiscuous->";
#endif
	       bpf_cmd.flags = bpf_cmd.flags || PROMISCUOUS(-1);
 	    }
	    else {
	      /* Deal with the idea of handling half of a command */
	    }
         }
	 else {
	 }
      }

      if ( iter[FOR] ) {

         while ( iter++ ) {

#ifdef	SNIFF_DEBUG
	    /*std::cout<<*iter<<"->";*/
#endif	    

	    if ( (*iter).compare(ARP) == 0 ) {

#ifdef	SNIFF_DEBUG
               std::cout<<ARP<<"->"<<PROTO_ARP(~0)<<"->";    
#endif

	       bpf_cmd.flags = bpf_cmd.flags | PROTO_ARP(-1);
	    }
	    else if ( (*iter).compare(IP) == 0 ) {

#ifdef	SNIFF_DEBUG
               std::cout<<IP<<"->"<<PROTO_IP(~0)<<"->";
#endif
	       
	       bpf_cmd.flags = bpf_cmd.flags | PROTO_IP(~0); 
	    }
	 }
      }

#ifdef	SNIFF_DEBUG
      std::cout<<std::endl;
      allocate(&bpf_cmd, NULL, 0);
#endif      
   }

   sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
   if (sockfd >= 0) {

      strncpy(interface.ifr_name, bpf_cmd.device, IFNAMSIZ);

      memset(&interface, sizeof(interface), 0);

      if (ioctl(sockfd, SIOCGIFINDEX, &interface) >= 0) {

         /* This should be last statement of this enclosing pair of parenthesis */
#ifdef	EXT3GREP_INIT_H
        ret = arg.init();
#endif

      } 
      else {

         perror("ioctl SIOCGIFINDEX");
	 close(sockfd);
	 ret = -1;
      }
   }
   else {

      perror("socket");
      ret = -1;
   }

   return ret;	 
}	
