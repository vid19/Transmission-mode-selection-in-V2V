

#ifndef LENA_TEST_TTA_FF_MAC_SCHEDULER_H
#define LENA_TEST_TTA_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;


class LenaTtaFfMacSchedulerTestCase : public TestCase
{
public:
  LenaTtaFfMacSchedulerTestCase (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl,bool errorModelEnabled);
  virtual ~LenaTtaFfMacSchedulerTestCase ();

private:
  static std::string BuildNameString (uint16_t nUser, uint16_t dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  uint16_t m_dist;
  double m_thrRefDl;
  double m_thrRefUl;
  bool m_errorModelEnabled;
};

class LenaTestTtaFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestTtaFfMacSchedulerSuite ();
};




#endif /* LENA_TEST_TTA_FF_MAC_SCHEDULER_H */
