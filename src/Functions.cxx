#include <iostream>
#include <memory>
#include <cmath>

#include "UHH2/HHtoWWbbSemiLeptonic/include/Functions.h"
//#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenRecoMatching.h"

using namespace std;
using namespace uhh2;

double TransverseMass(LorentzVector A, LorentzVector B, double mA, double mB) {
  double pTA = A.Pt();
  double pTB = B.Pt();
  double pt = (A+B).Pt();

  //double Et = sqrt(pow(pTA,2)+pow(mA,2))+sqrt(pow(pTB,2)+pow(mB,2));
  double Et = sqrt(pow(pTA,2)+pow(mA,2))+sqrt(pow(pTB,2)+pow(mB,2));
  double mt;
  // save for timelike/spacelike vectors ?
  if(Et > pt) mt = sqrt(pow(Et,2)-pow(pt,2));
  else mt = -sqrt(-(pow(Et,2)-pow(pt,2)));
  //cout << "mt: " << mt << endl;
  return mt;
}

// X->Y+Z, Y->A+B, Z->C+D with A,B,C,D assumed to be massless
double TransverseMass4particles(LorentzVector A, LorentzVector B, LorentzVector C, LorentzVector D) {
  double mtAB = TransverseMass(A,B,0,0);
  double mtCD = TransverseMass(C,D,0,0);
  double mtABCD = TransverseMass(A+B,C+D,mtAB,mtCD);
  return mtABCD;
}

// could be improved to a more generalized case using auto type instead of Jet/LorentzVector
double minDeltaR(vector<Jet>* A, LorentzVector b) {
  double dRmin = 999;
  for(const Jet a: *A) {
    double dR = deltaR(a,b);
    // dR should only be 0 if a and b are the same jets (I hope)
    if(dR<dRmin && dR!=0) dRmin = dR;
  }
  //cout << "minDeltaR: dRmin = " << dRmin << endl;
  return dRmin;
}

double minDeltaR_jj(vector<Jet>* jets) {
  int Njets = jets->size();
  double dRmin = 999;
  // loop over every pair of jets without repetition of pairs
  for(int i=0; i<Njets-1; i++){
    for(int j=i+1; j<Njets; j++){
      double dR = deltaR(jets->at(i),jets->at(j));
      if(dR<dRmin) dRmin=dR;
    }
  }
  //cout << "minDeltaR_jj: dRmin = " << dRmin << endl;
  return dRmin;
}

double minDeltaEta(vector<Jet>* A, LorentzVector b) {
  double dEtamin = 999;
  for(const Jet a: *A) {
    double dEta = abs(a.eta()-b.eta());
    // dEta should only be 0 if a and b are the same jets (I hope)
    if(dEta<dEtamin && dEta!=0) dEtamin = dEta;
  }
  //cout << "minDeltaEta: dEtamin = " << dEtamin << endl;
  return dEtamin;
}

double minDeltaEta_jj(vector<Jet>* jets) {
  int Njets = jets->size();
  double dEtamin = 999;
  // loop over every pair of jets without repetition of pairs
  for(int i=0; i<Njets-1; i++){
    for(int j=i+1; j<Njets; j++){
      double dEta = abs(jets->at(i).eta()-jets->at(j).eta());
      if(dEta<dEtamin) dEtamin=dEta;
    }
  }
  //cout << "minDeltaEta_jj: dEtamin = " << dEtamin << endl;
  return dEtamin;
}
