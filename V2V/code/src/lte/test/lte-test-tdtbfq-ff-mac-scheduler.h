
#ifndef LENA_TEST_TDTBFQ_FF_MAC_SCHEDULER_H
#define LENA_TEST_TDTBFQ_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;


class LenaTdTbfqFfMacSchedulerTestCase1 : public TestCase
{
public:
  LenaTdTbfqFfMacSchedulerTestCase1 (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, uint16_t packetSize, uint16_t interval, bool  errorModelEnabled);
  virtual ~LenaTdTbfqFfMacSchedulerTestCase1 ();

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


class LenaTdTbfqFfMacSchedulerTestCase2 : public TestCase
{
public:
  LenaTdTbfqFfMacSchedulerTestCase2 (std::vector<uint16_t> dist, std::vector<uint32_t> estThrTdTbfqDl, std::vector<uint16_t> packetSize, uint16_t interval, bool  errorModelEnabled);
  virtual ~LenaTdTbfqFfMacSchedulerTestCase2 ();

private:
  static std::string BuildNameString (uint16_t nUser, std::vector<uint16_t> dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  std::vector<uint16_t> m_dist;
  std::vector<uint16_t> m_packetSize;  // byte
  uint16_t m_interval;    // ms
  std::vector<uint32_t> m_estThrTdTbfqDl;
  bool m_errorModelEnabled;
};


class LenaTestTdTbfqFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestTdTbfqFfMacSchedulerSuite ();
};

#endif /* LENA_TEST_TDTBFQ_FF_MAC_SCHEDULER_H */
