
#ifndef _JEVENTPROCESSOR_JREADER_H_
#define _JEVENTPROCESSOR_JREADER_H_

#include <JANA/JEventProcessor.h>
#include <JEventSource_jreader.h>

class JEventProcessor_jreader: public JEventProcessor {
 public:
 JEventProcessor_jreader(): mFout(0) {};

  void Init(void);

  static thread_local TH1D *mHist;

  static void InitializeLocalThreadHistogram( void )
  {
    static std::mutex mymutex;

    TString hh; hh.Form("hvl%08u", (unsigned)pthread_self());
    mHist = new TH1D(hh.Data(), "", 1000, -10., 10.);
    
    // Basically the only place, which requires an extra lock;
    {
      std::lock_guard<std::mutex> lock(mymutex);
      
      mList->Add(mHist);
    }
  };
  
  static void FillThreadHistogram(double value) {
    if (!mHist) InitializeLocalThreadHistogram();

    mHist->Fill(value);
  };

  void Process(const std::shared_ptr<const JEvent>& aEvent) {
    if (!WithProcessor) return;

    const MyDouble *md = aEvent->GetSingle<MyDouble>("value"); 
    FillThreadHistogram(md->mValue);
  };

  void Finish(void); 

  TFile *mFout;
  static TList *mList;
};

#endif 

