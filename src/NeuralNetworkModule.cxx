#include <iostream>
#include <memory>

#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/AdditionalSelections.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/LuminosityHists.h"
#include "UHH2/common/include/TriggerSelection.h"
#include "UHH2/common/include/Utils.h"

#include "UHH2/HHtoWWbbSemiLeptonic/include/NeuralNetworkModule.h"

NeuralNetworkModule::NeuralNetworkModule(Context& ctx, const std::string & ModelName, const std::string& ConfigName): NeuralNetworkBase(ctx, ModelName, ConfigName) {
  
  h_eventweight = ctx.declare_event_output<float> ("eventweight");

  map<string, uhh2::Event::Handle<float>>::iterator it;
  for(it=NNInputs_map.begin(); it!=NNInputs_map.end();it++){
    it->second = ctx.get_handle<float>(it->first);
  }

  NNmodel = ctx.get("NNModel");

  // read out number of input variables
  ifstream normfile ("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/NNModel/"+NNmodel+"/NormInfo.txt", ios::in);
  N_variables = 0;
  string line;
  while(getline(normfile, line)) ++N_variables;
  normfile.close();
  cout << "Number of NN variables: " << N_variables << endl;
}

  
void NeuralNetworkModule::CreateInputs(Event & event) {
  NNInputs.clear();
  NNoutputs.clear();
 
  string varname[N_variables];
  string scal[N_variables];
  string mean[N_variables];
  string std[N_variables];
  double mean_val[N_variables];
  double std_val[N_variables];
  ifstream normfile ("/nfs/dust/cms/user/frahmmat/CMSSW_10_2_X_v2/CMSSW_10_2_17/src/UHH2/HHtoWWbbSemiLeptonic/data/NNModel/"+NNmodel+"/NormInfo.txt", ios::in);
  if (normfile.is_open()) { 
    for(int i = 0; i < N_variables; ++i) {   
      normfile >> varname[i] >> scal[i] >> mean[i] >> std[i];
      mean_val[i] = std::stod(mean[i]);
      std_val[i] = std::stod(std[i]);
    }
    normfile.close();
  }
  NNInputs.push_back( tensorflow::Tensor(tensorflow::DT_FLOAT, {1, N_variables}));
  //cout << varname[0] << endl;
  //cout << mean_val[0] << endl;

  
  for(int i = 0; i<N_variables; i++) {
    string identifier = varname[i];
    map<string, uhh2::Event::Handle<float>>::iterator it = NNInputs_map.find(identifier);
    if(it == NNInputs_map.end()) throw runtime_error("NNInputs_map in CreateInputs: "+identifier+ " is not mapped");
    float val = event.get(it->second);
    //cout << val << endl;
    NNInputs.at(0).tensor<float, 2>()(0,i)  = (val - mean_val[i]) / (std_val[i]);
  }

  if (NNInputs.size()!=LayerInputs.size()) throw logic_error("NeuralNetworkModule.cxx: Create a number of inputs diffetent wrt. LayerInputs.size()="+to_string(LayerInputs.size()));
}
