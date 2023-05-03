
#ifndef LTE_TEST_UE_MEASUREMENTS_H
#define LTE_TEST_UE_MEASUREMENTS_H

#include <ns3/test.h>
#include <ns3/lte-rrc-sap.h>
#include <ns3/nstime.h>
#include <list>
#include <set>
#include <vector>

namespace ns3 {

class MobilityModel;

}

using namespace ns3;



class LteUeMeasurementsTestSuite : public TestSuite
{
public:
  LteUeMeasurementsTestSuite ();
};


class LteUeMeasurementsTestCase : public TestCase
{
public:
  LteUeMeasurementsTestCase (std::string name, double d1, double d2, double rsrpDbmUe1, double rsrpDbmUe2, double rsrqDbUe1, double rsrqDbUe2);
  virtual ~LteUeMeasurementsTestCase ();

  void ReportUeMeasurements (uint16_t rnti, uint16_t cellId, double rsrp, double rsrq, bool servingCell);

  void RecvMeasurementReport (uint64_t imsi, uint16_t cellId, uint16_t rnti, LteRrcSap::MeasurementReport meas);

private:
  virtual void DoRun (void);

  double m_d1;
  double m_d2;
  double m_rsrpDbmUeServingCell;
  double m_rsrpDbmUeNeighborCell;
  double m_rsrqDbUeServingCell;
  double m_rsrqDbUeNeighborCell;

};



// ===== LTE-UE-MEASUREMENTS-PIECEWISE-1 TEST SUITE ======================== //


/**
 * \brief Test suite for generating calls to UE measurements test case
 *        ns3::LteUeMeasurementsPiecewiseTestCase1.
 */
class LteUeMeasurementsPiecewiseTestSuite1 : public TestSuite
{
public:
  LteUeMeasurementsPiecewiseTestSuite1 ();
};


/**
 * \brief Testing UE measurements in LTE with simulation of 1 eNodeB and 1 UE in
 *        piecewise configuration and 120 ms report interval.
 */
class LteUeMeasurementsPiecewiseTestCase1 : public TestCase
{
public:
  LteUeMeasurementsPiecewiseTestCase1 (std::string name,
                                       LteRrcSap::ReportConfigEutra config,
                                       std::vector<Time> expectedTime,
                                       std::vector<uint8_t> expectedRsrp);

  virtual ~LteUeMeasurementsPiecewiseTestCase1 ();

  /**
   * \brief Triggers when eNodeB receives measurement report from UE, then
   *        perform verification on it.
   *
   * The trigger is set up beforehand by connecting to the
   * `LteUeRrc::RecvMeasurementReport` trace source.
   *
   * Verification consists of checking whether the report carries the right
   * value of RSRP or not, and whether it occurs at the expected time or not.
   */
  void RecvMeasurementReportCallback (std::string context, uint64_t imsi,
                                      uint16_t cellId, uint16_t rnti,
                                      LteRrcSap::MeasurementReport report);

private:
  /**
   * \brief Setup the simulation with the intended UE measurement reporting
   *        configuration, run it, and connect the
   *        `RecvMeasurementReportCallback` function to the
   *        `LteUeRrc::RecvMeasurementReport` trace source.
   */
  virtual void DoRun ();

  /**
   * \brief Runs at the end of the simulation, verifying that all expected
   *        measurement reports have been examined.
   */
  virtual void DoTeardown ();

  void TeleportVeryNear ();
  void TeleportNear ();
  void TeleportFar ();
  void TeleportVeryFar ();

  /**
   * \brief The active report triggering configuration.
   */
  LteRrcSap::ReportConfigEutra m_config;

  /**
   * \brief The list of expected time when measurement reports are received by
   *        eNodeB.
   */
  std::vector<Time> m_expectedTime;

  /**
   * \brief The list of expected values of RSRP (in 3GPP range unit) from the
   *        measurement reports received.
   */
  std::vector<uint8_t> m_expectedRsrp;

  /**
   * \brief Pointer to the element of `m_expectedTime` which is expected to
   *        occur next in the simulation.
   */
  std::vector<Time>::iterator m_itExpectedTime;

  /**
   * \brief Pointer to the element of `m_expectedRsrp` which is expected to
   *        occur next in the simulation.
   */
  std::vector<uint8_t>::iterator m_itExpectedRsrp;

  /**
   * \brief The measurement identity being tested. Measurement reports with
   *        different measurement identity (e.g. from handover algorithm) will
   *        be ignored.
   */
  uint8_t m_expectedMeasId;

  Ptr<MobilityModel> m_ueMobility;

}; // end of class LteUeMeasurementsPiecewiseTestCase1



// ===== LTE-UE-MEASUREMENTS-PIECEWISE-2 TEST SUITE ======================== //


/**
 * \brief Test suite for generating calls to UE measurements test case
 *        ns3::LteUeMeasurementsPiecewiseTestCase2.
 */
class LteUeMeasurementsPiecewiseTestSuite2 : public TestSuite
{
public:
  LteUeMeasurementsPiecewiseTestSuite2 ();
};


/**
 * \brief Testing UE measurements in LTE with simulation of 2 eNodeB and 1 UE in
 *        piecewise configuration and 240 ms report interval.
 */
class LteUeMeasurementsPiecewiseTestCase2 : public TestCase
{
public:
  LteUeMeasurementsPiecewiseTestCase2 (std::string name,
                                       LteRrcSap::ReportConfigEutra config,
                                       std::vector<Time> expectedTime,
                                       std::vector<uint8_t> expectedRsrp);

  virtual ~LteUeMeasurementsPiecewiseTestCase2 ();

  /**
   * \brief Triggers when eNodeB receives measurement report from UE, then
   *        perform verification on it.
   *
   * The trigger is set up beforehand by connecting to the
   * `LteUeRrc::RecvMeasurementReport` trace source.
   *
   * Verification consists of checking whether the report carries the right
   * value of RSRP or not, and whether it occurs at the expected time or not.
   */
  void RecvMeasurementReportCallback (std::string context, uint64_t imsi,
                                      uint16_t cellId, uint16_t rnti,
                                      LteRrcSap::MeasurementReport report);

private:
  /**
   * \brief Setup the simulation with the intended UE measurement reporting
   *        configuration, run it, and connect the
   *        `RecvMeasurementReportCallback` function to the
   *        `LteUeRrc::RecvMeasurementReport` trace source.
   */
  virtual void DoRun ();

  /**
   * \brief Runs at the end of the simulation, verifying that all expected
   *        measurement reports have been examined.
   */
  virtual void DoTeardown ();

  void TeleportVeryNear ();
  void TeleportNear ();
  void TeleportFar ();
  void TeleportVeryFar ();

  /**
   * \brief The active report triggering configuration.
   */
  LteRrcSap::ReportConfigEutra m_config;

  /**
   * \brief The list of expected time when measurement reports are received by
   *        eNodeB.
   */
  std::vector<Time> m_expectedTime;

  /**
   * \brief The list of expected values of RSRP (in 3GPP range unit) from the
   *        measurement reports received.
   */
  std::vector<uint8_t> m_expectedRsrp;

  /**
   * \brief Pointer to the element of `m_expectedTime` which is expected to
   *        occur next in the simulation.
   */
  std::vector<Time>::iterator m_itExpectedTime;

  /**
   * \brief Pointer to the element of `m_expectedRsrp` which is expected to
   *        occur next in the simulation.
   */
  std::vector<uint8_t>::iterator m_itExpectedRsrp;

  /**
   * \brief The measurement identity being tested. Measurement reports with
   *        different measurement identity (e.g. from handover algorithm) will
   *        be ignored.
   */
  uint8_t m_expectedMeasId;

  Ptr<MobilityModel> m_ueMobility;

}; // end of class LteUeMeasurementsPiecewiseTestCase2



// ===== LTE-UE-MEASUREMENTS-HANDOVER TEST SUITE =========================== //


/**
 * \brief Test suite for generating calls to UE measurements test case
 *        ns3::LteUeMeasurementsHandoverTestCase.
 */
class LteUeMeasurementsHandoverTestSuite : public TestSuite
{
public:
  LteUeMeasurementsHandoverTestSuite ();
};


/**
 * \brief Testing UE measurements in LTE with simulation of 2 eNodeB and 1 UE in
 *        a handover configuration.
 *
 * The simulation will run for the specified duration, while the handover
 * command will be issued exactly at the middle of simulation.
 */
class LteUeMeasurementsHandoverTestCase : public TestCase
{
public:
  LteUeMeasurementsHandoverTestCase (std::string name,
                                     std::list<LteRrcSap::ReportConfigEutra> sourceConfigList,
                                     std::list<LteRrcSap::ReportConfigEutra> targetConfigList,
                                     std::vector<Time> expectedTime,
                                     std::vector<uint8_t> expectedRsrp,
                                     Time duration);

  virtual ~LteUeMeasurementsHandoverTestCase ();

  /**
   * \brief Triggers when either one of the eNodeBs receives measurement report
   *        from UE, then perform verification on it.
   *
   * The trigger is set up beforehand by connecting to the
   * `LteUeRrc::RecvMeasurementReport` trace source.
   *
   * Verification consists of checking whether the report carries the right
   * value of RSRP or not, and whether it occurs at the expected time or not.
   */
  void RecvMeasurementReportCallback (std::string context, uint64_t imsi,
                                      uint16_t cellId, uint16_t rnti,
                                      LteRrcSap::MeasurementReport report);

private:
  /**
   * \brief Setup the simulation with the intended UE measurement reporting
   *        configuration, run it, and connect the
   *        `RecvMeasurementReportCallback` function to the
   *        `LteUeRrc::RecvMeasurementReport` trace source.
   */
  virtual void DoRun ();

  /**
   * \brief Runs at the end of the simulation, verifying that all expected
   *        measurement reports have been examined.
   */
  virtual void DoTeardown ();

  /**
   * \brief The list of active report triggering configuration for the source
   *        eNodeB.
   */
  std::list<LteRrcSap::ReportConfigEutra> m_sourceConfigList;

  /**
   * \brief The list of active report triggering configuration for the target
   *        eNodeB.
   */
  std::list<LteRrcSap::ReportConfigEutra> m_targetConfigList;

  /**
   * \brief The list of expected time when measurement reports are received by
   *        eNodeB.
   */
  std::vector<Time> m_expectedTime;

  /**
   * \brief The list of expected values of RSRP (in 3GPP range unit) from the
   *        measurement reports received.
   */
  std::vector<uint8_t> m_expectedRsrp;

  /**
   * \brief Pointer to the element of `m_expectedTime` which is expected to
   *        occur next in the simulation.
   */
  std::vector<Time>::iterator m_itExpectedTime;

  /**
   * \brief Pointer to the element of `m_expectedRsrp` which is expected to
   *        occur next in the simulation.
   */
  std::vector<uint8_t>::iterator m_itExpectedRsrp;

  /**
   * \brief Duration of simulation.
   */
  Time m_duration;

  /**
   * \brief The list of measurement identities being tested in the source cell.
   *        Measurement reports with different measurement identity (e.g. from
   *        handover algorithm and ANR) will be ignored.
   */
  std::set<uint8_t> m_expectedSourceCellMeasId;

  /**
   * \brief The list of measurement identities being tested in the target cell.
   *        Measurement reports with different measurement identity (e.g. from
   *        handover algorithm and ANR) will be ignored.
   */
  std::set<uint8_t> m_expectedTargetCellMeasId;

}; // end of class LteUeMeasurementsHandoverTestCase

#endif /* LTE_TEST_UE_MEASUREMENTS_H */
