

#ifndef EPC_UE_NAS_H
#define EPC_UE_NAS_H


#include <ns3/object.h>
#include <ns3/lte-as-sap.h>
#include <ns3/epc-tft-classifier.h>

namespace ns3 {


class EpcHelper;

class EpcUeNas : public Object
{
  friend class MemberLteAsSapUser<EpcUeNas>;
public:

 
  EpcUeNas ();


  virtual ~EpcUeNas ();

  // inherited from Object
  virtual void DoDispose (void);
  static TypeId GetTypeId (void);


  void SetDevice (Ptr<NetDevice> dev);

  void SetImsi (uint64_t imsi);

  void SetCsgId (uint32_t csgId);

  uint32_t GetCsgId () const;

  
  void SetAsSapProvider (LteAsSapProvider* s);

 
  LteAsSapUser* GetAsSapUser ();


  void SetForwardUpCallback (Callback <void, Ptr<Packet> > cb);


  void StartCellSelection (uint16_t dlEarfcn);

 
  void Connect ();

 
  void Connect (uint16_t cellId, uint16_t dlEarfcn);
 
  
  void Disconnect ();



  void ActivateEpsBearer (EpsBearer bearer, Ptr<EpcTft> tft);

 
  bool Send (Ptr<Packet> p);


  enum State 
  {
    OFF = 0,
    ATTACHING,
    IDLE_REGISTERED,
    CONNECTING_TO_EPC,
    ACTIVE,
    NUM_STATES
  };

  /**
   * \return The current state
   */
  State GetState () const;

  
  typedef void (* StateTracedCallback)
    (const State oldState, const State newState);
 
private:

  // LTE AS SAP methods
  void DoNotifyConnectionSuccessful ();
  void DoNotifyConnectionFailed ();
  void DoNotifyConnectionReleased ();
  void DoRecvData (Ptr<Packet> packet);

  // internal methods
  void DoActivateEpsBearer (EpsBearer bearer, Ptr<EpcTft> tft);

  void SwitchToState (State s);

  /// The current UE NAS state.
  State m_state;

  TracedCallback<State, State> m_stateTransitionCallback;

  /// The UE NetDevice.
  Ptr<NetDevice> m_device;

  /// The unique UE identifier.
  uint64_t m_imsi;

  /// Closed Subscriber Group identity.
  uint32_t m_csgId;

  LteAsSapProvider* m_asSapProvider;
  LteAsSapUser* m_asSapUser;

  uint8_t m_bidCounter;
  EpcTftClassifier m_tftClassifier;

  Callback <void, Ptr<Packet> > m_forwardUpCallback;

  struct BearerToBeActivated
  {
    EpsBearer bearer;
    Ptr<EpcTft> tft;
  };

  std::list<BearerToBeActivated> m_bearersToBeActivatedList;

};


} // namespace ns3

#endif // EPC_UE_NAS_H
