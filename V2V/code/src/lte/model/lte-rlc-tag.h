

#ifndef RLC_TAG_H
#define RLC_TAG_H

#include "ns3/packet.h"
#include "ns3/nstime.h"


namespace ns3 {

class Tag;


class RlcTag : public Tag
{
public:
  static TypeId  GetTypeId (void);
  virtual TypeId  GetInstanceTypeId (void) const;


  RlcTag ();

  RlcTag (Time senderTimestamp);

  virtual void  Serialize (TagBuffer i) const;
  virtual void  Deserialize (TagBuffer i);
  virtual uint32_t  GetSerializedSize () const;
  virtual void Print (std::ostream &os) const;

 
  Time  GetSenderTimestamp (void) const
  {
    return m_senderTimestamp;
  }

  /**
   * Set the sender timestamp
   * @param senderTimestamp time stamp of the instant when the RLC delivers the PDU to the MAC SAP provider
   */
  void  SetSenderTimestamp (Time senderTimestamp)
  {
    this->m_senderTimestamp = senderTimestamp;
  }

private:
  Time m_senderTimestamp;

};

} //namespace ns3

#endif /* RLC_TAG_H */
