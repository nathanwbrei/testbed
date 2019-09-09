
#ifndef _JEVENTPROCESSOR_JREADER_H_
#define _JEVENTPROCESSOR_JREADER_H_

#include <JANA/JEventProcessor.h>
#include <JEventSource_jreader.h>

class JEventProcessor_jreader:public JEventProcessor {
 public:
  void Init(void) {};

  void Process(const std::shared_ptr<const JEvent>& aEvent) {
    const MyDouble *md = aEvent->GetSingle<MyDouble>("value"); 

    // This is essential: while thread#1 is busy buffering first events, other 
    // threads may reach this point before their local mHist was initialized;
    // therefore should NOT put this call in JEventSource_jreader::GetEvent();
    if (!JEventSource_jreader::mHist) JEventSource_jreader::InitializeLocalHistogram();

    JEventSource_jreader::mHist->Fill(md->mValue);
  };

  void Finish(void) {};
};

#endif 

