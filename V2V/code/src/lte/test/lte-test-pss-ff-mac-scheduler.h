

#ifndef LENA_TEST_PSS_FF_MAC_SCHEDULER_H
#define LENA_TEST_PSS_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;


class LenaPssFfMacSchedulerTestCase1 : public TestCase
{
public:
  LenaPssFfMacSchedulerTestCase1 (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, uint16_t packetSize, uint16_t interval, bool  errorModelEnabled);
  virtual ~LenaPssFfMacSchedulerTestCase1 ();

private:
  static std::string BuildNameString (uint16_t nUser, uint16_t dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  uint16_t m_dist;
  uint16_t m_packetSize;  // byte
  uint16_t m_interval;    // ms
  double m_thrRefDl;
  double m_thrRefUl;
  bool m_errorModelEnabled;
};


class LenaPssFfMacSchedulerTestCase2 : public TestCase
{
public:
  LenaPssFfMacSchedulerTestCase2 (std::vector<uint16_t> dist, std::vector<uint32_t> estThrPssDl, std::vector<uint16_t> packetSize, uint16_t interval, bool  errorModelEnabled);
  virtual ~LenaPssFfMacSchedulerTestCase2 ();

private:
  static std::string BuildNameString (uint16_t nUser, std::vector<uint16_t> dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  std::vector<uint16_t> m_dist;
  std::vector<uint16_t> m_packetSize;  // byte
  uint16_t m_interval;    // ms
  std::vector<uint32_t> m_estThrPssDl;
  bool m_errorModelEnabled;
};


class LenaTestPssFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestPssFfMacSchedulerSuite ();
};

#endif /* LENA_TEST_PSS_FF_MAC_SCHEDULER_H */
