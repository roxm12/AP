#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/netfilter_ipv4.h>
#include <libnetfilter_queue/libnetfilter_queue.h>

#define IFNAMSIZ 16
#define IS_UDP (packet->payload[9] == 17)
#define IS_TCP (packet->payload[9] == 6)
#define BUFSIZE 2048
#define PAYLOADSIZE 2048
#define SRC_ADDR(payload)(*(in_addr_t *)((payload)+12))
#define DST_ADDR(payload)(*(in_addr_t *)((payload)+12))

struct queued_pkt{
	uint32_t packet_id;
	char indev[IFNAMSIZ];
	char physindev[IFNAMSIZ];
	char outdev[IFNAMSIZ];
	char physoutdev[IFNAMSIZ];
	u_int32_t mark;
	time_t timestamp;
	char *payload;
	int payload_len;
};

char *ip2str(in_addr_t ip)
{
	static char buf[2][sizeof("255.255.255.255")];
	static short int index = 0;
	sprintf(buf[index], "%d.%d.%d.%d",
						(ip) & 0xff,
						(ip >> 8) & 0xff,
						(ip >> 16) & 0xff,
						(ip >> 24) & 0xff);
	if(index)
	{
		index=0;
		return buf[1];
	}
	else return buf[index++];
}

int look_for_tcp_flags(unsigned char *dgram, unsigned int datalen)
{
	struct iphdr *iphdrs;
	struct tcphdr *tcphdrs;
	iphdrs = (struct iphdr *)dgram;
	printf("datalen: %d\n", datalen);
	printf("iphdr: %d\n", sizeof(struct iphdr));
	printf("tcphdr: %d\n", sizeof(struct tcphdr));
	if(datalen < sizeof(struct iphdr) + sizeof(struct tcphdr))
	{
		return 0;
	}
	printf("ip version: %d\n", iphdrs->version);
	printf("ip ihl: %d\n", iphdrs->ihl);
	printf("saddr: %s\n", ip2str(iphdrs->saddr));
	printf("daddr: %s\n", ip2str(iphdrs->daddr));
	tcphdrs = (struct tcphdr *)(dgram + 4 * iphdrs->ihl);
	printf("tcp sport: %u\n", htons(tcphdrs->source));
	printf("tcp dport: %u\n", htons(tcphdrs->dest));
	printf("tcp syn: %u\n", tcphdrs->syn);
	printf("tcp ack: %u\n", tcphdrs->ack);
	printf("tcp fin: %u\n", tcphdrs->fin);
	return 1;
}

static int work_do(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data)
{
	int id=0, status =0 ;
	struct queued_pkt q_pkt;
	struct nfqnl_msg_packet_hdr *ph;
	struct iphdr *iph = NULL;
	struct timeval timestamp;
	char *payload;
	int ret;
#ifdef HAVE_NFQ_INDEV_NAME
	struct nlif_handle *nlif_handle = (struct nlif_handle *)data;
#endif
	q_pkt.payload_len = nfq_get_payload(nfa, &(q_pkt.payload));
	q_pkt.mark = nfq_get_nfmark(nfa);

#ifdef HAVE_NFQ_INDEV_NAME
	if(!get_interface_inform ation(nlif_handle, &q_pkt, nfa))
	{
		log_are_printf(DEBUG_AREA_PACKET, DEBUG_LEVEL_INFO,
				"Can not get interfaces inform ation for message");
		return 0;
	}
#else
	snprintf(q_pkt.indev, sizeof(q_pkt.indev),"*");
	snprintf(q_pkt.physindev, sizeof(q_pkt.physindev), "*");
	snprintf(q_pkt.outdev, sizeof(q_pkt.outdev), "*");
	snprintf(q_pkt.physoutdev, sizeof(q_pkt.physoutdev), "*");
#endif
	ret = nfq_get_timestamp(nfa, &timestamp);
	if(ret == 0)
		q_pkt.timestamp = timestamp.tv_sec;
	else
		q_pkt.timestamp = time(NULL);
	ph=nfq_get_msg_packet_hdr(nfa);
	if(ph)
	{
		id = ntohl(ph->packet_id);
		nfq_get_payload(nfa, &payload);
		switch(ph->hook)
		{
			case NF_IP_LOCAL_IN:
				printf("\n\nLOCAL_IN\n");
				break;
			case NF_IP_LOCAL_OUT:
				printf("\n\nLOCAL_OUT\n");
				break;
			case NF_IP_FORWARD:
				break;
		}
		
		look_for_tcp_flags((unsigned char*)q_pkt.payload, q_pkt.payload_len);
		nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
	}
}

int netlink_init(int q_num)
{
	struct nfq_handle *h;
	struct nfq_q_handle *qh;
	struct nfnl_handle *nh;
	int fd, rv;
	char buf[BUFSIZE];
	h = nfq_open();
	if(!h)
	{
		fprintf(stderr, "Error During nfq_open()\n");
		exit(-1);
	}
	if(nfq_unbind_pf(h,AF_INET)<0)
	{
		fprintf(stderr, "Error During nfq_bind_pf()\n");
		exit(-1);
	}
	
	qh = nfq_create_queue(h,q_num, &work_do, NULL);
	if(!qh)
	{
		fprintf(stderr, "Error During nfq_creqte_queue()\n");
		exit(-1);
	}
	if(nfq_set_mode(qh, NFQNL_COPY_PACKET, PAYLOADSIZE) < 0)
	{
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(-1);
	}
	fprintf(stderr, "NFQUEUE : binding from queue\n");
	nh = nfq_nfnlh(h);
	fd = nfnl_fd(nh);
	while((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0)
	{
		nfq_handle_packet(h, buf, rv);
	}
	fprintf(stderr, "NFQUEUE : unbinding from queue\n");
	nfq_destroy_queue(qh);
	nfq_close(h);
	return 0;
}

int main(int argc, char **argv)
{
	int q_num = 0;
	if(argc < 2)
	{
		fprintf(stderr, "Option error\n");
		q_num = 0;
	}
	else
		q_num = atoi(argv[1]);

	return netlink_init(q_num);
}
