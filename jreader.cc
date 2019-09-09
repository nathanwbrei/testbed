
#include <JANA/JEventSourceGeneratorT.h>

#include "JEventProcessor_jreader.h"
#include "JEventSource_jreader.h"

extern "C"{
void InitPlugin(JApplication *app) {

  InitJANAPlugin(app);
	
  // Add source generator
  app->Add( new JEventSourceGeneratorT<JEventSource_jreader>() );
  
  JParameterManager *pm = app->GetJParameterManager();
  if (pm->Exists("with-processor")) {
    WithProcessor = true;

    // Add event processor in this case;
    app->Add( new JEventProcessor_jreader() );  
  } //if
}
} // "C"

