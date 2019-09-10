
#ifndef _JEVENTPROCESSOR_JREADER_H_
#define _JEVENTPROCESSOR_JREADER_H_

#include <JANA/JEventProcessor.h>
#include <JEventSource_jreader.h>

class JEventProcessor_jreader: public JEventProcessor {
 public:
 JEventProcessor_jreader(): mFout(0), mOutputTree(0), 
    mOutputValue(0.0), mOutputQueueDepth(10) {};

  void Init(void);

  std::mutex outmutex;

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
      mOutputQueueArray.push_back(mOutputQueue);
    }
  };
  
  static void FillThreadHistogram(double value) {
    if (!mHist) InitializeLocalThreadHistogram();

    mHist->Fill(value);
  };

  void FlushOutputQueue(std::vector<MyDouble> *queue) {
    std::lock_guard<std::mutex> lock(outmutex);

    for(auto val: *queue) {
      mOutputValue = val.mValue;
      mOutputTree->Fill();
    } 
    
    queue->clear();
  };

  void Process(const std::shared_ptr<const JEvent>& aEvent) {
    if (!WithProcessor) return;

    const MyDouble *md = aEvent->GetSingle<MyDouble>("value"); 
    FillThreadHistogram(md->mValue);
    
    mOutputQueue->push_back(*md);
    if (mOutputQueue->size() == mOutputQueueDepth) FlushOutputQueue(mOutputQueue);
  };

  void Finish(void); 

  TFile *mFout;
  TTree *mOutputTree;
  double mOutputValue;
  static TList *mList;

  unsigned mOutputQueueDepth;
  static thread_local std::vector<MyDouble> *mOutputQueue;
  static std::vector<std::vector<MyDouble>*> mOutputQueueArray;
};

#endif 

