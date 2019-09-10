
#include <JANA/JEventSourceGeneratorT.h>

#include "JEventProcessor_jreader.h"
#include "JEventSource_jreader.h"

bool WithProcessor = false;

extern "C"{
void InitPlugin(JApplication *app) {

  InitJANAPlugin(app);
	
  // Add source generator
  app->Add( new JEventSourceGeneratorT<JEventSource_jreader>() );
  
  JParameterManager *pm = app->GetJParameterManager();
  if (pm->Exists("with-processor")) WithProcessor = true;

  // Add event processor anyway, since it is managing the output as well;
  app->Add( new JEventProcessor_jreader() ); 
}
} // "C"

