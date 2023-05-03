
#ifndef PDCP_TAG_H
#define PDCP_TAG_H

#include "ns3/packet.h"
#include "ns3/nstime.h"


namespace ns3 {

class Tag;


class PdcpTag : public Tag
{
public:
  static TypeId  GetTypeId (void);
  virtual TypeId  GetInstanceTypeId (void) const;


  PdcpTag ();

  PdcpTag (Time senderTimestamp);

  virtual void  Serialize (TagBuffer i) const;
  virtual void  Deserialize (TagBuffer i);
  virtual uint32_t  GetSerializedSize () const;
  virtual void Print (std::ostream &os) const;


  Time  GetSenderTimestamp (void) const;

 void  SetSenderTimestamp (Time senderTimestamp);

private:
  Time m_senderTimestamp;

};
} 
#endif /* PDCP_TAG_H */
