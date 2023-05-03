
#ifndef LENA_TEST_FDMT_FF_MAC_SCHEDULER_H
#define LENA_TEST_FDMT_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;


class LenaFdMtFfMacSchedulerTestCase : public TestCase
{
public:
  LenaFdMtFfMacSchedulerTestCase (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl,bool errorModelEnabled);
  virtual ~LenaFdMtFfMacSchedulerTestCase ();

private:
  static std::string BuildNameString (uint16_t nUser, uint16_t dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  uint16_t m_dist;
  double m_thrRefDl;
  double m_thrRefUl;
  bool m_errorModelEnabled;
};

class LenaTestFdMtFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestFdMtFfMacSchedulerSuite ();
};




#endif /* LENA_TEST_FDMT_FF_MAC_SCHEDULER_H */
