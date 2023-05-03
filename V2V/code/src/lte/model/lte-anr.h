

#ifndef LTE_ANR_H
#define LTE_ANR_H

#include <ns3/object.h>
#include <ns3/lte-rrc-sap.h>
#include <ns3/lte-anr-sap.h>
#include <map>

namespace ns3 {


class LteAnrSapProvider;
class LteAnrSapUser;
class LteNeighbourRelation;

class LteAnr : public Object
{
public:
  LteAnr (uint16_t servingCellId);
  virtual ~LteAnr ();
  static TypeId GetTypeId ();
  void AddNeighbourRelation (uint16_t cellId);
  void RemoveNeighbourRelation (uint16_t cellId);
  virtual void SetLteAnrSapUser (LteAnrSapUser* s);
  virtual LteAnrSapProvider* GetLteAnrSapProvider ();
  friend class MemberLteAnrSapProvider<LteAnr>;

protected:

  virtual void DoInitialize ();
  virtual void DoDispose ();

private:

  void DoReportUeMeas (LteRrcSap::MeasResults measResults);
  void DoAddNeighbourRelation (uint16_t cellId);
  bool DoGetNoRemove (uint16_t cellId) const;
  bool DoGetNoHo (uint16_t cellId) const;
  bool DoGetNoX2 (uint16_t cellId) const;
  LteAnrSapProvider* m_anrSapProvider;
  LteAnrSapUser* m_anrSapUser;
  uint8_t m_threshold;
  struct NeighbourRelation_t
  {
    bool noRemove;
    bool noHo;
    bool noX2;
    bool detectedAsNeighbour;
  };

  //               cellId
  typedef std::map<uint16_t, NeighbourRelation_t> NeighbourRelationTable_t;

  NeighbourRelationTable_t m_neighbourRelationTable;

  // internal methods
  const NeighbourRelation_t* Find (uint16_t cellId) const;

  // The expected measurement identity
  uint8_t m_measId;

  uint16_t m_servingCellId;

}; // end of class LteAnr


} // end of namespace ns3


#endif /* LTE_ANR_H */
