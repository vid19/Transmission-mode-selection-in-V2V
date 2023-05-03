
#ifndef RADIO_ENVIRONMENT_MAP_HELPER_H
#define RADIO_ENVIRONMENT_MAP_HELPER_H


#include <ns3/object.h>
#include <fstream>


namespace ns3 {

class RemSpectrumPhy;
class Node;
class NetDevice;
class SpectrumChannel;
//class BuildingsMobilityModel;
class MobilityModel;


class RadioEnvironmentMapHelper : public Object
{
public:  

  RadioEnvironmentMapHelper ();
  virtual ~RadioEnvironmentMapHelper ();
  
  // inherited from Object
  virtual void DoDispose (void);
  /**
   *  Register this type.
   *  \return The object TypeId.
   */
  static TypeId GetTypeId (void);

 
  uint8_t GetBandwidth () const;

  
  void SetBandwidth (uint8_t bw);

  void Install ();

private:

 
  void DelayedInstall ();

  
  void RunOneIteration (double xMin, double xMax, double yMin, double yMax);

  /// Go through every listener, write the computed SINR, and then reset it.
  void PrintAndReset ();

  /// Called when the map generation procedure has been completed.
  void Finalize ();

  /// A complete Radio Environment Map is composed of many of this structure.
  struct RemPoint 
  {
    /// Simplified listener which compute SINR over the DL channel.
    Ptr<RemSpectrumPhy> phy;
    /// Position of the listener in the environment.
    Ptr<MobilityModel> bmm;
  };

  /// List of listeners in the environment.
  std::list<RemPoint> m_rem;

  double m_xMin;   
  double m_xMax;   
  uint16_t m_xRes; 
  double m_xStep;  

  double m_yMin;   
  double m_yMax;   
  uint16_t m_yRes; 
  double m_yStep;  

  uint32_t m_maxPointsPerIteration;  

  uint16_t m_earfcn;     
  uint16_t m_bandwidth;  
 
  double m_z;  

  std::string m_channelPath; 
  std::string m_outputFile;  

  bool m_stopWhenDone;   
  Ptr<SpectrumChannel> m_channel;

  double m_noisePower;  

  std::ofstream m_outFile;  

  bool m_useDataChannel;  
  int32_t m_rbId;         

};
} 

#endif
