#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>
#include <pcre.h>

int main()
{
  char errbuf[PCAP_ERRBUF_SIZE];
  const u_char * pkt_data;
  struct pcap_pkthdr * pkt_hdr;
  pcap_t * pcap;
/*
  char * dev = pcap_lookupdev(errbuf);
  if(!dev) {
    printf("Could not init interface: %s\n", errbuf);
    return 0;
  }
*/
  pcap = pcap_open_live("any", 1<<16, 1, 1<<30, errbuf);
  if(!pcap) {
    printf("Could not init interface: %s\n", errbuf);
    return 0;
  }
  printf("Blocking status: %u\n", pcap_getnonblock(pcap, errbuf));

  while((pkt_data = pcap_next(pcap, pkt_hdr))) {
    //printf("%d.%d\n", pkt_hdr->ts.tv_sec, pkt_hdr->ts.tv_usec);
    printf("%.*s", pkt_hdr->caplen, pkt_data);
  }

  return 1;
}
