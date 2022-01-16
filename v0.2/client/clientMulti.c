#pragma once
#include        <sys/types.h>   /* basic system data types */
#include        <sys/socket.h>  /* basic socket definitions */
#include        <netinet/in.h>  /* sockaddr_in{} and other Internet defns */
#include        <arpa/inet.h>   /* inet(3) functions */
#include        <errno.h>
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include 		<sys/ioctl.h>
#include 		<unistd.h>
#include 		<net/if.h>
#include		<netdb.h>
#include		<sys/utsname.h>
#include		<linux/un.h>
#include		<time.h>

#define SA      struct sockaddr

unsigned int
_if_nametoindex(const char *ifname)
{
	int s;
	struct ifreq ifr;
	unsigned int ni;

	s = socket(AF_INET, SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (s != -1) {

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, ifname, sizeof(ifr.ifr_name));
	
	if (ioctl(s, SIOCGIFINDEX, &ifr) != -1) {
			close(s);
			return (ifr.ifr_ifindex);
	}
		close(s);
		return -1;
	}
	return 1;
}

// #include <net/if.h>
// unsigned int if_nametoindex(const char *ifname);
// char *if_indextoname(unsigned int ifindex, char *ifname);

int snd_udp_socket(const char *serv, int port, SA **saptr, socklen_t *lenp)
{
	int sockfd, n;
	struct addrinfo	hints, *res, *ressave;
	struct sockaddr_in6 *pservaddrv6;
	struct sockaddr_in *pservaddrv4;

	*saptr = (SA *) malloc( sizeof(struct sockaddr_in6));
	
	pservaddrv6 = (struct sockaddr_in6*)*saptr;

	bzero(pservaddrv6, sizeof(struct sockaddr_in6));

	if (inet_pton(AF_INET6, serv, &pservaddrv6->sin6_addr) <= 0){
	
		free(*saptr);
		*saptr = (SA *) malloc( sizeof(struct sockaddr_in));
		pservaddrv4 = (struct sockaddr_in*)*saptr;
		bzero(pservaddrv4, sizeof(struct sockaddr_in));

		if (inet_pton(AF_INET, serv, &pservaddrv4->sin_addr) <= 0){
			fprintf(stderr,"AF_INET inet_pton error for %s : %s \n", serv, strerror(errno));
			return -1;
		}else{
			pservaddrv4->sin_family = AF_INET;
			pservaddrv4->sin_port   = htons(port);
			*lenp =  sizeof(struct sockaddr_in);
			if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
				fprintf(stderr,"AF_INET socket error : %s\n", strerror(errno));
				return -1;
			}
		}

	}else{
		pservaddrv6 = (struct sockaddr_in6*)*saptr;
		pservaddrv6->sin6_family = AF_INET6;
		pservaddrv6->sin6_port   = htons(port);	/* daytime server */
		*lenp =  sizeof(struct sockaddr_in6);

		if ( (sockfd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0){
			fprintf(stderr,"AF_INET6 socket error : %s\n", strerror(errno));
			return -1;
		}

	}

	return(sockfd);
}
/* end send_udp_socket */

int family_to_level(int family)
{
	switch (family) {
	case AF_INET:
		return IPPROTO_IP;
#ifdef	IPV6
	case AF_INET6:
		return IPPROTO_IPV6;
#endif
	default:
		return -1;
	}
}

int mcast_join(int sockfd, const SA *grp, socklen_t grplen,
		   const char *ifname, u_int ifindex)
{
	struct group_req req;
	if (ifindex > 0) {
		req.gr_interface = ifindex;
	} else if (ifname != NULL) {
		if ( (req.gr_interface = if_nametoindex(ifname)) == 0) {
			errno = ENXIO;	/* if name not found */
			return(-1);
		}
	} else
		req.gr_interface = 0;
	if (grplen > sizeof(req.gr_group)) {
		errno = EINVAL;
		return -1;
	}
	memcpy(&req.gr_group, grp, grplen);
	return (setsockopt(sockfd, family_to_level(grp->sa_family),
			MCAST_JOIN_GROUP, &req, sizeof(req)));
}
/* end mcast_join */

int mcast_join_org(int sockfd, const SA *grp, socklen_t grplen,
		   const char *ifname, u_int ifindex)
{
#ifdef MCAST_JOIN_GROUP
	struct group_req req;
	if (ifindex > 0) {
		req.gr_interface = ifindex;
	} else if (ifname != NULL) {
		if ( (req.gr_interface = if_nametoindex(ifname)) == 0) {
			errno = ENXIO;	/* if name not found */
			return(-1);
		}
	} else
		req.gr_interface = 0;
	if (grplen > sizeof(req.gr_group)) {
		errno = EINVAL;
		return -1;
	}
	memcpy(&req.gr_group, grp, grplen);
	return (setsockopt(sockfd, family_to_level(grp->sa_family),
			MCAST_JOIN_GROUP, &req, sizeof(req)));
#else
/* end mcast_join1 */

/* include mcast_join2 */
	switch (grp->sa_family) {
	case AF_INET: {
		struct ip_mreq		mreq;
		struct ifreq		ifreq;

		memcpy(&mreq.imr_multiaddr,
			   &((const struct sockaddr_in *) grp)->sin_addr,
			   sizeof(struct in_addr));

		if (ifindex > 0) {
			if (if_indextoname(ifindex, ifreq.ifr_name) == NULL) {
				errno = ENXIO;	/* i/f index not found */
				return(-1);
			}
			goto doioctl;
		} else if (ifname != NULL) {
			strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
doioctl:
			if (ioctl(sockfd, SIOCGIFADDR, &ifreq) < 0)
				return(-1);
			memcpy(&mreq.imr_interface,
				   &((struct sockaddr_in *) &ifreq.ifr_addr)->sin_addr,
				   sizeof(struct in_addr));
		} else
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);

		return(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
						  &mreq, sizeof(mreq)));
	}
/* end mcast_join2 */

/* include mcast_join3 */
#ifdef	IPV6
#ifndef	IPV6_JOIN_GROUP		/* APIv0 compatibility */
#define	IPV6_JOIN_GROUP		IPV6_ADD_MEMBERSHIP
#endif
	case AF_INET6: {
		struct ipv6_mreq	mreq6;

		memcpy(&mreq6.ipv6mr_multiaddr,
			   &((const struct sockaddr_in6 *) grp)->sin6_addr,
			   sizeof(struct in6_addr));

		if (ifindex > 0) {
			mreq6.ipv6mr_interface = ifindex;
		} else if (ifname != NULL) {
			if ( (mreq6.ipv6mr_interface = if_nametoindex(ifname)) == 0) {
				errno = ENXIO;	/* i/f name not found */
				return(-1);
			}
		} else
			mreq6.ipv6mr_interface = 0;

		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_JOIN_GROUP,
						  &mreq6, sizeof(mreq6)));
	}
#endif

	default:
		errno = EAFNOSUPPORT;
		return(-1);
	}
#endif
}
/* end mcast_join3_org */

int sockfd_to_family(int sockfd)
{
	struct sockaddr_storage ss;
	socklen_t	len;

	len = sizeof(ss);
	if (getsockname(sockfd, (SA *) &ss, &len) < 0)
		return(-1);
	return(ss.ss_family);
}

int mcast_set_loop(int sockfd, int onoff)
{
	switch (sockfd_to_family(sockfd)) {
	case AF_INET: {
		u_char		flag;

		flag = onoff;
		return(setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP,
						  &flag, sizeof(flag)));
	}

#ifdef	IPV6
	case AF_INET6: {
		u_int		flag;

		flag = onoff;
		return(setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP,
						  &flag, sizeof(flag)));
	}
#endif

	default:
		errno = EAFNOSUPPORT;
		return(-1);
	}
}
/* end mcast_set_loop */


void	recv_all(int, socklen_t, time_t time, int randm);
void	send_all(int, SA *, socklen_t, int action, time_t time, int randm);

#define	SENDRATE	5		/* send one datagram every five seconds */

void send_all(int sendfd, SA *sadest, socklen_t salen, int action, time_t time, int randm)
{
	char		line[MAXLINE];		/* hostname and process ID */
	struct utsname	myname;

	if (uname(&myname) < 0)
		perror("uname error");
	
	//---------------------------------------------------------
	if(!action){
		snprintf(line, sizeof(line), "SEARCH^%jd^%d^%s", time, randm, myname.nodename);
	}
	//---------------------------------------------------------

	if(sendto(sendfd, line, strlen(line), 0, sadest, salen) < 0 )
		 fprintf(stderr,"sendto() error : %s\n", strerror(errno));
}

void recv_all(int recvfd, socklen_t salen, time_t time, int randm)
{
	int					n;
	char				line[MAXLINE+1];
	socklen_t			len;
	struct sockaddr		*safrom;
	char str[128];
	struct sockaddr_in6*	 cliaddr;
	struct sockaddr_in*	 cliaddrv4;
	char			addr_str[INET6_ADDRSTRLEN+1];

	safrom = (SA *) malloc(salen);

	for ( ; ; ) {
		len = salen;
		if( (n = recvfrom(recvfd, line, MAXLINE, 0, safrom, &len)) < 0 )
		  perror("recvfrom() error");

		line[n] = 0;	/* null terminate */
		
		if( safrom->sa_family == AF_INET6 ){
		      cliaddr = (struct sockaddr_in6*) safrom;
		      inet_ntop(AF_INET6, (struct sockaddr  *) &cliaddr->sin6_addr,  addr_str, sizeof(addr_str));
		}
		else{
		      cliaddrv4 = (struct sockaddr_in*) safrom;
		      inet_ntop(AF_INET, (struct sockaddr  *) &cliaddrv4->sin_addr,  addr_str, sizeof(addr_str));
		}
		
		char* token;
		long val1;
		int val2;
		token = strtok(line,"^");
		if(strcmp(token,"GAME")==0){
			token = strtok(NULL, "^");
			val1 = atoi(token);
			token = strtok(NULL, "^");
			val2 = atoi(token);
			token = strtok(NULL, "^");// nazwa
			if((val1 == time) && val2 == randm){
				printf("%s\t%s\n", addr_str, token);
			}
		}
		fflush(stdout);
		
	}
}



int main(int argc, char **argv) {
	
	srand(time(NULL));
	time_t id_time = time(NULL);
	int id_rand = rand();
	
	if (argc != 1){
		fprintf(stderr, "%s Type no arguments\n", argv[0]);
		return 1;
	}
	
	char buff1[addr_size];
	char buff2[port_size];
	char buff3[if_size];
	
	int def_interface = 0;
	
	system("clear");
	printf("----------------------------CLIENT----------------------------\n\n");
	printf("----------------------Witaj w grze ryzyko----------------------\n\n");
	printf("Czy chcesz znalezc gre pod adresem domyslnym? (Y/n)");
	while(1) {
		char character = getc(stdin);
		fgets(buff1, sizeof(buff1), stdin);// better getch()
		if((character == 'Y') || (character == 'y')){
			strncpy (buff1, "224.0.0.90", sizeof(buff1) );
			strncpy (buff2, "3456", sizeof(buff2) );
			//strncpy (buff3, "eth1", sizeof(buff3) );
			strncpy (buff3, "enp0s3", sizeof(buff3) );
			break;
		}
		else if((character == 'N') || (character == 'n')){
			printf("\nPodaj adres multicast do wyszukiwania gier (domyslnie 224.0.0.90): ");
			fgets(buff1, sizeof(buff1), stdin);
			printf("Podaj port (domyslnie: 3456): ");
			fgets(buff2, sizeof(buff2), stdin);
			printf("Podaj nazwe interfejsu (domyslnie: eth1): ");
			fgets(buff3, sizeof(buff3), stdin);
			printf("Poszukiwanie dostepnych gier po adresach IPv4...\n");
	
			buff1[strlen(buff1) - 1] = 0;	// necessary to use inet_pton
			buff2[strlen(buff2) - 1] = 0;	//
			buff3[strlen(buff3) - 1] = 0;	//
			break;
		}
		printf("Podaj poprawna litere");
	}
	
	int sendfd, recvfd;
	const int on = 1;
	socklen_t salen;
	struct sockaddr	*sasend, *sarecv;
	struct sockaddr_in6 *ipv6addr;
	struct sockaddr_in *ipv4addr;

	// SENT SOCKET
	sendfd = snd_udp_socket(buff1, atoi(buff2), &sasend, &salen);

	// RECV SOCKET
	if ( (recvfd = socket(sasend->sa_family, SOCK_DGRAM, 0)) < 0){
		fprintf(stderr,"socket error : %s\n", strerror(errno));
		return 1;
	}
	
	
	if (setsockopt(recvfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0){
		fprintf(stderr,"setsockopt error : %s\n", strerror(errno));
		return 1;
	}

	sarecv = (SA *) malloc(salen);
	memcpy(sarecv, sasend, salen);

	setsockopt(sendfd, SOL_SOCKET, SO_BINDTODEVICE, buff3, strlen(buff3));
	
	if(sarecv->sa_family == AF_INET6){
	  ipv6addr = (struct sockaddr_in6 *) sarecv;
	  ipv6addr->sin6_addr =  in6addr_any;

	  int32_t ifindex;
      ifindex = if_nametoindex(buff3);
      if(setsockopt(sendfd, IPPROTO_IPV6, IPV6_MULTICAST_IF, 
	  				&ifindex, sizeof(ifindex)) < 0){
	  		perror("setting local interface");
			exit(1);};
	  }

	if(sarecv->sa_family == AF_INET){
	  ipv4addr = (struct sockaddr_in *) sarecv;
	  ipv4addr->sin_addr.s_addr =  htonl(INADDR_ANY);

      char int_addr[INET_ADDRSTRLEN + 1];                                                           //wziete z funkcji recv_all
	  struct in_addr        localInterface;
      inet_ntop(AF_INET, (struct sockaddr  *) &ipv4addr->sin_addr,  int_addr, sizeof(int_addr));  //wydobycie adresu interfejsu
	  localInterface.s_addr = inet_addr(int_addr);                                                 //tu zmieniamy na adres maszyny
	  if (setsockopt(sendfd, IPPROTO_IP, IP_MULTICAST_IF,
						(char *)&localInterface,
						sizeof(localInterface)) < 0) {
			perror("setting local interface");
			exit(1);
	  }
	}
	
	if( bind(recvfd, sarecv, salen) < 0 ){
	    fprintf(stderr,"bind error : %s\n", strerror(errno));
	    return 1;
	}
	
	if( mcast_join(recvfd, sasend, salen, buff3, 0) < 0 ){
		fprintf(stderr,"mcast_join() error : %s\n", strerror(errno));
		return 1;
	}
	  
	mcast_set_loop(sendfd, 1);

	if (fork() == 0)
		recv_all(recvfd, salen, id_time, id_rand);
	else{
		system("clear");
		printf("Dane klienta: czas: %jd\trandom id: %d\n", id_time, id_rand);
		printf("Wpisz 'refresh' aby odwiezyc\n");
		printf("Wpisz 'connect '<IP>' aby polaczyc sie z serwerem\n");
		printf("-----------------------------------------------------------------\n");
		printf("                         Dostepne gry:                         \n");		
		send_all(sendfd, sasend, salen, 0, id_time, id_rand);
	
		while(1){
			bzero(buff1, sizeof(buff1));
			fgets(buff1, addr_size, stdin);
			buff1[strcspn(buff1, "\n")] = '\0';// usuwanie "entera"
			if(!strcmp(buff1, "refresh")) {
				system("clear");
				printf("Dane klienta: czas: %jd\trandom id: %d\n", id_time, id_rand);
				printf("Wpisz 'refresh' aby odwiezyc\n");
				printf("Wpisz 'connect '<IP>' aby polaczyc sie z serwerem\n");
				printf("-----------------------------------------------------------------\n");
				printf("                         Dostepne gry:                         \n");		
				send_all(sendfd, sasend, salen, 0, id_time, id_rand);	/* parent -> sends */
			}
			else{
				char* token;
				token = strtok(buff1," ");
				if(!strcmp(token,"connect")){
					token = strtok(NULL, " ");
					if(token != NULL) {
						strcpy(buff1, token);
						char command[60];
						strcpy(command, "./clientTCP ");
						strcat(command, buff1);
						system(command);
						exit(0);
					}
					else printf("Wpisz adres postaci 'connect '<IP>'");
				}
			}
			fflush(stdin);
		}
	}
}
