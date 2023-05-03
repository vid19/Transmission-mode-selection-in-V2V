
#ifndef EPS_BEARER_TAG_H
#define EPS_BEARER_TAG_H

#include "ns3/tag.h"

namespace ns3 {

class Tag;


class EpsBearerTag : public Tag
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;

  EpsBearerTag ();

  EpsBearerTag (uint16_t  rnti, uint8_t bid);
  
  void SetRnti (uint16_t rnti);

  void SetBid (uint8_t bid);

  virtual void Serialize (TagBuffer i) const;
  virtual void Deserialize (TagBuffer i);
  virtual uint32_t GetSerializedSize () const;
  virtual void Print (std::ostream &os) const;

  uint16_t GetRnti (void) const;
  uint8_t GetBid (void) const;

private:
  uint16_t m_rnti;
  uint8_t m_bid;

};



} // namespace ns3

#endif /* EPS_BEARER_TAG_H */
