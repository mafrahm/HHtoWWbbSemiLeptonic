#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesisDiscriminators.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHReconstructionHypothesis.h"
//#include "UHH2/LQToTopMu/include/LQGen.h"
#include "UHH2/common/include/PDFWeights.h"

using namespace std;
namespace uhh2examples {

  /**  \brief Example class for booking and filling histograms
  *
  * NOTE: This class uses the 'hist' method to retrieve histograms.
  * This requires a string lookup and is therefore slow if you have
  * many histograms. Therefore, it is recommended to use histogram
  * pointers as member data instead, like in 'common/include/ElectronHists.h'.
  */
  class HHPDFHists: public uhh2::Hists {
  public:
    // use the same constructor arguments as Hists for forwarding:
    HHPDFHists(uhh2::Context & ctx, const std::string & dirname);

    virtual void fill(const uhh2::Event & ev) override;

    int noSysweightsCount=0;
  protected:
    vector<vector<TString>> histo_names;
    std::vector<TString> histo_names0, histo_names1, histo_names2, histo_names3, hist_names4;

    uhh2::Event::Handle<double> h_NNoutput0;
    uhh2::Event::Handle<double> h_NNoutput1;
    uhh2::Event::Handle<double> h_NNoutput2;
    uhh2::Event::Handle<double> h_NNoutput3;
    uhh2::Event::Handle<double> h_NNoutput4;
    bool is_mc, take_ntupleweights;
    TString m_oname;
    std::unique_ptr<PDFWeights> m_pdfweights;


    virtual ~HHPDFHists();
  };

}
