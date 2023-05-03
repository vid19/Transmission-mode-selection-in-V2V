

#ifndef LTE_TEST_CELL_SELECTION_H
#define LTE_TEST_CELL_SELECTION_H

#include <ns3/test.h>
#include <ns3/nstime.h>
#include <ns3/node-container.h>
#include <ns3/vector.h>
#include <ns3/lte-ue-rrc.h>
#include <vector>


namespace ns3 {

class LteUeNetDevice;

}

using namespace ns3;


class LteCellSelectionTestSuite : public TestSuite
{
public:
  LteCellSelectionTestSuite ();
};



class LteCellSelectionTestCase : public TestCase
{
public:
 
  struct UeSetup_t
  {
    Vector position; ///< The position, relative to the inter site distance, where the UE will be spawned in the simulation.
    bool isCsgMember; ///< Whether UE is allowed access to CSG cell.
    Time checkPoint; ///< The time in simulation when the UE is verified by the test script.
    uint16_t expectedCellId1; ///< The cell ID that the UE is expected to attach to (0 means that the UE should not attach to any cell).
    uint16_t expectedCellId2; ///< An alternative cell ID that the UE is expected to attach to (0 means that this no alternative cell is expected).
    UeSetup_t (double relPosX, double relPosY, bool isCsgMember, Time checkPoint,
               uint16_t expectedCellId1, uint16_t expectedCellId2);
  };

  
  LteCellSelectionTestCase (std::string name, bool isEpcMode, bool isIdealRrc,
                            double interSiteDistance,
                            std::vector<UeSetup_t> ueSetupList,
                            int64_t rngRun);

  virtual ~LteCellSelectionTestCase ();

private:
  
  virtual void DoRun ();

  
  void CheckPoint (Ptr<LteUeNetDevice> ueDev, uint16_t expectedCellId1,
                   uint16_t expectedCellId2);

  void StateTransitionCallback (std::string context, uint64_t imsi,
                                uint16_t cellId, uint16_t rnti,
                                LteUeRrc::State oldState, LteUeRrc::State newState);
  void InitialCellSelectionEndOkCallback (std::string context, uint64_t imsi,
                                          uint16_t cellId);
  void InitialCellSelectionEndErrorCallback (std::string context, uint64_t imsi,
                                             uint16_t cellId);
  void ConnectionEstablishedCallback (std::string context, uint64_t imsi,
                                      uint16_t cellId, uint16_t rnti);

  bool m_isEpcMode;
  bool m_isIdealRrc;
  double m_interSiteDistance;
  std::vector<UeSetup_t> m_ueSetupList;
  int64_t m_rngRun;

  /// The current UE RRC state.
  std::vector<LteUeRrc::State> m_lastState;

}; // end of class LteCellSelectionTestCase

#endif /* LTE_TEST_CELL_SELECTION_H */
