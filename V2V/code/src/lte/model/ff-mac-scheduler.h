

#ifndef FF_MAC_SCHEDULER_H
#define FF_MAC_SCHEDULER_H

#include <ns3/object.h>


namespace ns3 {



class FfMacCschedSapUser;
class FfMacSchedSapUser;
class FfMacCschedSapProvider;
class FfMacSchedSapProvider;
class LteFfrSapProvider;
class LteFfrSapUser;

class FfMacScheduler : public Object
{
public:
  
  enum UlCqiFilter_t
  {
    SRS_UL_CQI,
    PUSCH_UL_CQI,
    ALL_UL_CQI
  };

  FfMacScheduler ();

  virtual ~FfMacScheduler ();

  // inherited from Object
  virtual void DoDispose (void);
  static TypeId GetTypeId (void);

  virtual void SetFfMacCschedSapUser (FfMacCschedSapUser* s) = 0;

  virtual void SetFfMacSchedSapUser (FfMacSchedSapUser* s) = 0;

  virtual FfMacCschedSapProvider* GetFfMacCschedSapProvider () = 0;

  virtual FfMacSchedSapProvider* GetFfMacSchedSapProvider () = 0;

  
  virtual void SetLteFfrSapProvider (LteFfrSapProvider* s) = 0;

  /**
   *
   * \return the User part of the LteFfrSap provided by the FfrAlgorithm
   */
  virtual LteFfrSapUser* GetLteFfrSapUser () = 0;
  
protected:
    
  UlCqiFilter_t m_ulCqiFilter;

};

}  // namespace ns3

#endif /* FF_MAC_SCHEDULER_H */
