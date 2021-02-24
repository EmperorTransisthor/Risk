#ifndef SERWERMULTICAST_H
#define SERWERMULTICAST_H

#define MAXLINE 1024
#define SA      struct sockaddr
#define IPV6 1

unsigned int _if_nametoindex(const char *ifname);
int snd_udp_socket(const char *serv, int port, SA **saptr, socklen_t *lenp);
int family_to_level(int family);
int mcast_join(int sockfd, const SA *grp, socklen_t grplen,
		   const char *ifname, u_int ifindex);
int mcast_join_org(int sockfd, const SA *grp, socklen_t grplen,
		   const char *ifname, u_int ifindex);
int sockfd_to_family(int sockfd);
int mcast_set_loop(int sockfd, int onoff);
void	recv_all(int, socklen_t, int* readytosend, long* time, int* randm);
void	send_all(int, SA *, socklen_t, time_t time, int randm, char* buff);
int ServMULTICAST(int* multicast_pid);

#endif // SERWERMULTICAST_H