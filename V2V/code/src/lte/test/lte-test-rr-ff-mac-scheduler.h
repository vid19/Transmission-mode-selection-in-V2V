
#ifndef LENA_TEST_RR_FF_MAC_SCHEDULER_H
#define LENA_TEST_RR_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;


class LenaRrFfMacSchedulerTestCase : public TestCase
{
public:
  LenaRrFfMacSchedulerTestCase (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, bool errorModelEnabled);
  virtual ~LenaRrFfMacSchedulerTestCase ();

private:
  virtual void DoRun (void);
  static std::string BuildNameString (uint16_t nUser, uint16_t dist);
  uint16_t m_nUser;
  uint16_t m_dist;
  double m_thrRefDl;
  double m_thrRefUl;
  bool m_errorModelEnabled;

};



class LenaTestRrFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestRrFfMacSchedulerSuite ();
};

#endif /* LENA_TEST_RR_FF_MAC_SCHEDULER_H */
