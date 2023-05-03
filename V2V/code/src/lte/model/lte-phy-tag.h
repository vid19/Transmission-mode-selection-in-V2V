#ifndef LTE_PHY_TAG_H
#define LTE_PHY_TAG_H

#include "ns3/tag.h"

namespace ns3 {
class LtePhyTag : public Tag
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  LtePhyTag ();
  LtePhyTag (uint16_t cellId);
  virtual ~LtePhyTag ();
  virtual void Serialize (TagBuffer i) const;
  virtual void Deserialize (TagBuffer i);
  virtual uint32_t GetSerializedSize () const;
  virtual void Print (std::ostream &os) const;

  uint16_t GetCellId () const;

private:
  uint16_t m_cellId;

};
} 
#endif 
