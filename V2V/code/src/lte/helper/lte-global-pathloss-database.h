


#ifndef LTE_GLOBAL_PATHLOSS_DATABASE_H
#define LTE_GLOBAL_PATHLOSS_DATABASE_H

#include <ns3/log.h>
#include <ns3/ptr.h>
#include <string>
#include <map>

namespace ns3 {

class SpectrumPhy;



class LteGlobalPathlossDatabase
{
public:

  virtual ~LteGlobalPathlossDatabase (void);

  virtual void UpdatePathloss (std::string context, Ptr<SpectrumPhy> txPhy, Ptr<SpectrumPhy> rxPhy, double lossDb) = 0;

  
  double GetPathloss (uint16_t cellId, uint64_t imsi);

  
  void Print ();

protected:
  
  std::map<uint16_t, std::map<uint64_t, double> > m_pathlossMap;
};

class DownlinkLteGlobalPathlossDatabase : public LteGlobalPathlossDatabase
{
public:
  // inherited from LteGlobalPathlossDatabase
  virtual void UpdatePathloss (std::string context, Ptr<SpectrumPhy> txPhy, Ptr<SpectrumPhy> rxPhy, double lossDb);
};

class UplinkLteGlobalPathlossDatabase : public LteGlobalPathlossDatabase
{
public:
  // inherited from LteGlobalPathlossDatabase
  virtual void UpdatePathloss (std::string context, Ptr<SpectrumPhy> txPhy, Ptr<SpectrumPhy> rxPhy, double lossDb);
};


} // namespace ns3




#endif // LTE_GLOBAL_PATHLOSS_DATABASE_H
