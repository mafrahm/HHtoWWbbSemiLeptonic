#include "UHH2/HHtoWWbbSemiLeptonic/include/HHGenObjects.h"

using namespace uhh2;
using namespace std;


HHGenObjects::HHGenObjects(const vector<GenParticle> & genparticles, bool throw_on_failure) {
  //cout << "HHGenObjects: start" << endl;
  //cout << "genp size: " <<genparticles.size() << endl;
  //for(unsigned int i=0; i<genparticles.size(); i++) cout << "Genparticle Ids: " << genparticles[i].pdgId() << endl;

  for(unsigned int i=0; i<genparticles.size(); i++) {
    
    const GenParticle & genp = genparticles[i];
    if (abs(genp.pdgId()) == 25) {
      auto hd1 = genp.daughter(&genparticles,1);
      auto hd2 = genp.daughter(&genparticles,2);
      // check for more daughter particles?
      if (!hd1 || !hd2) throw runtime_error("Higgs has no 2 daughters");


      int hd1_Id = abs(hd1->pdgId()); // should be either 5 (b) or 24 (W)
      int hd2_Id = abs(hd1->pdgId()); // should be either 5 (b) or 24 (W)
      if(hd1_Id != hd2_Id) throw runtime_error("two Higgs daughter particles are not the same (?)");

      if(hd1_Id == 5) { // hd1, hd2 are bottom quarks
	// Higgs
	m_H_bb = genp;
	m_B1 = *hd1;
	m_B2 = *hd2;
      }
      else if(abs(hd1->pdgId()) == 24) { // hd1, hd2 are W bosons
	// Higgs
	m_H_WW = genp;
	
	m_WHad = *hd1;
	m_WLep = *hd2;

	// randomly sorted
	auto quark1 = hd1->daughter(&genparticles, 1);
	auto quark2 = hd1->daughter(&genparticles, 2);
	auto lepton = hd2->daughter(&genparticles, 1);
	auto neutrino = hd2->daughter(&genparticles, 2);


	if(isQuark(lepton->pdgId()) || isNeutrino(quark1->pdgId()) || isNeutrino(quark2->pdgId())) {
	  std::swap(quark1, lepton);
	  std::swap(quark2, neutrino);
	  std::swap(m_WHad, m_WLep);
	}
	if(isNeutrino(abs(lepton->pdgId()))) {
	  std::swap(lepton, neutrino);
	}


	int q1_Id = quark1->pdgId();
	int q2_Id = quark2->pdgId();
	int l_Id = lepton->pdgId();
	int n_Id = neutrino->pdgId();
	/*
	cout << "Quark1 Id: " << q1_Id << endl;
	cout << "Quark2 Id: " << q2_Id << endl;
	cout << "Lepton Id: " << l_Id << endl;
	cout << "Neutrino Id: " << n_Id << endl;
	*/
	//	int charge = quark1->charge() << endl;
	//	cout << "charge " << charge << endl;

	if(isChargedLepton(l_Id) && isChargedLepton(n_Id)) {
	  //cout << "PHOTON RADIATION! (l)" << endl;
	  for(unsigned int j=0; j<genparticles.size(); j++) {
	    const GenParticle & gp = genparticles[j];
	   
	    int gp_Id = gp.pdgId();
	    auto m_gp = gp.mother(&genparticles, 1); // to check if gp even has a mother
	    if(isNeutrino(gp_Id) && m_gp && abs(m_gp->pdgId()) == 24) {
	      neutrino = &gp;
	      if(isNeutrino(genparticles[j-1].pdgId()) && abs(genparticles[j-1].mother(&genparticles,1)->pdgId()) == 24) {
		lepton = &genparticles[j-1]; // lepton is always right before it's associated neutrino
		cout << lepton->pdgId() << endl;
	      }
	    }
	  }
	}

	if(isChargedLepton(q1_Id) && isChargedLepton(q2_Id)) { // photon radiation
	  //cout << "PHOTON RADIATION! (q)" << endl;
	  int counter = 1;
	  for(unsigned int j=0; j<genparticles.size(); j++) {
	    // 
	    const GenParticle & gp = genparticles[j];
	    int gp_Id = gp.pdgId();
	    //cout << gp_Id << endl;
	    auto m_gp = gp.mother(&genparticles, 1); // to check if gp even has a mother
	    //if(!m_gp) continue;
	    if(isQuark(gp_Id) && m_gp && abs(m_gp->pdgId()) == 24) {
	      //cout << "counter: " <<  counter << endl;
	      if(counter==1) quark1 = &gp;
	      else if(counter==2) quark2 = &gp;
	      else runtime_error("there should only be 2 quarks decaying from W");
	      counter++;
	    }
	  }
	}

	// should be correctly sortet by now
	q1_Id = quark1->pdgId();
	q2_Id = quark2->pdgId();
	l_Id = lepton->pdgId();
	n_Id = neutrino->pdgId();
	/*
	cout << "Quark1 Id: " << q1_Id << endl;
	cout << "Quark2 Id: " << q2_Id << endl;
	cout << "Lepton Id: " << l_Id << endl;
	cout << "Neutrino Id: " << n_Id << endl;
	*/
	if(throw_on_failure){ 
	  if (!isQuark(q1_Id)) throw runtime_error("quark1 should be a Quark!");
	  if (!isQuark(q2_Id)) throw runtime_error("quark2 should be a Quark!");
	  if (!isLepton(l_Id)) throw runtime_error("lepton should be a Lepton!");
	  if (!isNeutrino(n_Id)) throw runtime_error("neutrino should be a Neutrino!");
	}
        m_ChargedLepton = *lepton;
	m_Neutrino = *neutrino;
	m_Q1 = *quark1;
	m_Q2 = *quark2;




      }
    }
  } // end of for loop
}


GenParticle HHGenObjects::H_bb() const{
  return m_H_bb;
}

GenParticle HHGenObjects::H_WW() const{
  return m_H_WW;
}

GenParticle HHGenObjects::B1() const{
  return m_B1;
}

GenParticle HHGenObjects::B2() const{
  return m_B2;
}

GenParticle HHGenObjects::WLep() const{
  return m_WLep;
}

GenParticle HHGenObjects::WHad() const{
  return m_WHad;
}

GenParticle HHGenObjects::ChargedLepton() const{
  return m_ChargedLepton;
}

GenParticle HHGenObjects::Neutrino() const{
  return m_Neutrino;
}

GenParticle HHGenObjects::Q1() const{
  return m_Q1;
}

GenParticle HHGenObjects::Q2() const{
  return m_Q2;
}



bool HHGenObjects::isQuark(int id){
  id = abs(id);
  return(id==1 || id==2 || id==3 || id==4 || id==5 || id==6) ;
}
bool HHGenObjects::isLepton(int id){
  id = abs(id);
  return(id==11 || id==12 || id==13 || id==14 || id==15 || id==16) ;
}
bool HHGenObjects::isChargedLepton(int id){
  id = abs(id);
  return(id==11 || id==13 || id==15) ;
}
bool HHGenObjects::isNeutrino(int id){
  id = abs(id);
  return(id==12 || id==14 || id==16) ;
}





HHGenObjectsProducer::HHGenObjectsProducer(uhh2::Context & ctx, const std::string & name, bool throw_on_failure): throw_on_failure(throw_on_failure) {
  h_HHgenobjects = ctx.get_handle<HHGenObjects>(name);
}

bool HHGenObjectsProducer::process(Event & event) {
  event.set(h_HHgenobjects, HHGenObjects(*event.genparticles, throw_on_failure));
  return true;
}
