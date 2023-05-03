

#ifndef LENA_TEST_PF_FF_MAC_SCHEDULER_H
#define LENA_TEST_PF_FF_MAC_SCHEDULER_H

#include "ns3/simulator.h"
#include "ns3/test.h"


using namespace ns3;



class LenaPfFfMacSchedulerTestCase1 : public TestCase
{
public:
  LenaPfFfMacSchedulerTestCase1 (uint16_t nUser, uint16_t dist, double thrRefDl, double thrRefUl, bool errorModelEnabled);
  virtual ~LenaPfFfMacSchedulerTestCase1 ();

private:
  static std::string BuildNameString (uint16_t nUser, uint16_t dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  uint16_t m_dist;
  double m_thrRefDl;
  double m_thrRefUl;
  bool m_errorModelEnabled;
};


class LenaPfFfMacSchedulerTestCase2 : public TestCase
{
public:
  LenaPfFfMacSchedulerTestCase2 (std::vector<uint16_t> dist, std::vector<uint32_t> estThrPfDl, std::vector<uint32_t> estThrPfUl, bool errorModelEnabled);
  virtual ~LenaPfFfMacSchedulerTestCase2 ();

private:
  static std::string BuildNameString (uint16_t nUser, std::vector<uint16_t> dist);
  virtual void DoRun (void);
  uint16_t m_nUser;
  std::vector<uint16_t> m_dist;
  std::vector<uint32_t> m_estThrPfDl;
  std::vector<uint32_t> m_estThrPfUl;
  bool m_errorModelEnabled;
};




class LenaTestPfFfMacSchedulerSuite : public TestSuite
{
public:
  LenaTestPfFfMacSchedulerSuite ();
};

#endif /* LENA_TEST_PF_FF_MAC_SCHEDULER_H */
