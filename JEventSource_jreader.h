
#ifndef _JEVENT_SOURCE_JREADER_
#define _JEVENT_SOURCE_JREADER_

#include <JANA/JApplication.h>
#include <JANA/JEventSource.h>
#include <JANA/JEvent.h>

#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TList.h>

extern bool WithProcessor;

class JEventSource_jreader: public JEventSource {
 public:

  // Constructor must take string and JApplication pointer as arguments
 JEventSource_jreader(std::string source_name, JApplication *app):JEventSource(source_name, app),
    mFin(0), mFout(0), mTree(0), mHistSum(0), mValue(0.0), mEvCurrent(-1), mEventsTotal(0) {}
  virtual ~JEventSource_jreader() {
    if (mHistSum && mFout) {
      mHistSum->Merge(mList);

      mFout->cd();
      mHistSum->Write(); 
      mFout->Close(); 
    } //if
  }
  
  // A description of this source type must be provided as a static member
  static std::string GetDescription(void){ return "Event source for jreader example"; }
  
  void Open(void);
  void GetEvent(std::shared_ptr<JEvent>);

  TFile *mFin;
  TFile *mFout;
  TTree *mTree;
  TH1D *mHistSum;

  static thread_local TH1D *mHist;
  static TList *mList;
  static void InitializeLocalHistogram( void );

  double mValue;

  int mEvCurrent, mEventsTotal;
};

class MyDouble: public JObject {
 public:
 MyDouble(double value): mValue(value) {};

  double mValue;
};

#endif
