

#ifndef EPC_TEST_GTPU_H
#define EPC_TEST_GTPU_H

#include "ns3/epc-gtpu-header.h"

#include "ns3/test.h"


using namespace ns3;



class EpsGtpuTestSuite : public TestSuite
{
public:
  EpsGtpuTestSuite ();
};


class EpsGtpuHeaderTestCase : public TestCase
{
public:
  EpsGtpuHeaderTestCase ();
  virtual ~EpsGtpuHeaderTestCase ();

private:
  virtual void DoRun (void);
};


#endif /* EPC_TEST_GTPU_H */
