
#include <TFile.h>
#include <TH1D.h>
#include <ROOT/TTreeProcessorMT.hxx>

int main( void )
{
  ROOT::EnableImplicitMT(4);

  // Initialize TTreeProcessorMT and then let it do the job;
  ROOT::TTreeProcessorMT tp("events.root", "tree"); 

  TFile fout("histograms.root", "RECREATE");

  ROOT::TThreadedObject<TH1D> hv("hv", "hv", 1000, -10., 10.);
  
  auto myFunction = [&](TTreeReader &myReader) {
    TTreeReaderValue<double> value(myReader, "value");

    auto myHvHist = hv.Get();

    while (myReader.Next()) myHvHist->Fill(*value);
  };
  
  tp.Process(myFunction);

  auto hvMerged = hv.Merge();

  hv->Write(); fout.Close();
} // main()
