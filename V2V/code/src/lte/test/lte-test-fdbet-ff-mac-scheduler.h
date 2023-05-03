

#ifndef LENA_TEST_FDBET_FF_MAC_SCHEDULER_H
#define LENA_TEST_FDBET_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;


class LenaFdBetFfMacSchedulerTestCase1 : public TestCase
{
public:
  LenaFdBetFfMacSchedulerTestCase1 (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl,bool errorModelEnabled);
  virtual ~LenaFdBetFfMacSchedulerTestCase1 ();

private:
  static std::string BuildNameString (uint16_t nUser, uint16_t dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  uint16_t m_dist;
  double m_thrRefDl;
  double m_thrRefUl;
  bool m_errorModelEnabled;
};


class LenaFdBetFfMacSchedulerTestCase2 : public TestCase
{
public:
  LenaFdBetFfMacSchedulerTestCase2 (std::vector<uint16_t> dist, std::vector<uint32_t> m_achievableRateDl, std::vector<uint32_t> estThrFdBetUl, bool m_errorModelEnabled);
  virtual ~LenaFdBetFfMacSchedulerTestCase2 ();

private:
  static std::string BuildNameString (uint16_t nUser, std::vector<uint16_t> dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  std::vector<uint16_t> m_dist;
  std::vector<uint32_t> m_achievableRateDl;
  std::vector<uint32_t> m_estThrFdBetUl;
  bool m_errorModelEnabled;
};




class LenaTestFdBetFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestFdBetFfMacSchedulerSuite ();
};

#endif /* LENA_TEST_FDBET_FF_MAC_SCHEDULER_H */
