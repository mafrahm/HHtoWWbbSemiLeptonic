    
#pragma once
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"
#include "UHH2/HHtoWWbbSemiLeptonic/include/HHtoWWbbSemiLeptonicHists.h"



double TransverseMass(LorentzVector A, LorentzVector B, double mA, double mB);
double TransverseMass4particles(LorentzVector A, LorentzVector B, LorentzVector C, LorentzVector D);


double minDeltaR(vector<Jet>* A, LorentzVector b);
double minDeltaR_jj(vector<Jet>* jets);
double minDeltaPhi(vector<Jet>* A, LorentzVector b);
double minDeltaPhi_jj(vector<Jet>* jets);

double minDeltaEta(vector<Jet>* A, LorentzVector b);
double minDeltaEta_jj(vector<Jet>* jets);

