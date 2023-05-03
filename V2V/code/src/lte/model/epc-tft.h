


#ifndef EPC_TFT_H
#define EPC_TFT_H


#include <ns3/simple-ref-count.h>
#include <ns3/ipv4-address.h>

#include <list>

namespace ns3 {


class EpcTft : public SimpleRefCount<EpcTft>
{

public:


  static Ptr<EpcTft> Default ();
 
  enum Direction {DOWNLINK = 1,
		  UPLINK = 2,
		  BIDIRECTIONAL = 3};
  

  struct PacketFilter
  {
    PacketFilter ();


    bool Matches (Direction d,
		  Ipv4Address ra, 
		  Ipv4Address la, 
		  uint16_t rp,
		  uint16_t lp,
		  uint8_t tos);

 

    uint8_t precedence;  

    Direction direction; 

    Ipv4Address remoteAddress;    
    Ipv4Mask remoteMask; 
    Ipv4Address localAddress; 
    Ipv4Mask localMask;  
  
    uint16_t remotePortStart; 
    uint16_t remotePortEnd;   
    uint16_t localPortStart;  
    uint16_t localPortEnd;    
  
    uint8_t typeOfService;    
    uint8_t typeOfServiceMask;
  };
  
  EpcTft ();

  uint8_t Add (PacketFilter f);


    bool Matches (Direction direction,
		  Ipv4Address remoteAddress, 
		  Ipv4Address localAddress, 
		  uint16_t remotePort,
		  uint16_t localPort,
		  uint8_t typeOfService);


private:

  std::list<PacketFilter> m_filters;
  uint8_t m_numFilters;
  
};


std::ostream& operator<< (std::ostream& os, EpcTft::Direction& d);


} // namespace ns3
  
#endif /* EPC_TFT_H */ 


