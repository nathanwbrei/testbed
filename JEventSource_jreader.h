
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
    mFin(0), mTree(0), mValue(0.0), mEvCurrent(-1), mEventsTotal(0) {}
  virtual ~JEventSource_jreader() {}
  
  // A description of this source type must be provided as a static member
  static std::string GetDescription(void) { return "Event source for jreader example"; }
  
  void Open(void);
  void GetEvent(std::shared_ptr<JEvent>);

  TFile *mFin;
  TTree *mTree;

  double mValue;

  int mEvCurrent, mEventsTotal;
};

class MyDouble: public JObject {
 public:
 MyDouble(double value): mValue(value) {};

  double mValue;
};

#endif
