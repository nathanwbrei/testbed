
void plotter( void )
{
  auto ff = new TFile("histograms.root");
  auto hv = dynamic_cast<TH1D*>(ff->Get("hv"));

  hv->Fit("gaus");
} // plotter()
