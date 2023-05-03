

#ifndef LTE_RLC_SDU_STATUS_TAG_H
#define LTE_RLC_SDU_STATUS_TAG_H

#include "ns3/tag.h"

namespace ns3 {


class LteRlcSduStatusTag : public Tag
{
public:
  LteRlcSduStatusTag ();

  void SetStatus (uint8_t status);
  uint8_t GetStatus (void) const;

  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (TagBuffer i) const;
  virtual void Deserialize (TagBuffer i);
  virtual void Print (std::ostream &os) const;

  typedef enum { FULL_SDU       = 1,
                 FIRST_SEGMENT  = 2,
                 MIDDLE_SEGMENT = 3,
                 LAST_SEGMENT   = 4,
                 ANY_SEGMENT    = 5 } SduStatus_t;

private:
  uint8_t m_sduStatus;
};


}; // namespace ns3

#endif // LTE_RLC_SDU_STATUS_TAG_H
