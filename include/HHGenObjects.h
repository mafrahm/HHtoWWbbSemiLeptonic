#pragma once

#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include <vector>


class HHGenObjects {
 public:

  explicit HHGenObjects(const std::vector<GenParticle> & genparts, bool throw_on_failure = true);

  GenParticle H_bb() const;
  GenParticle H_WW() const;
  GenParticle B1() const;
  GenParticle B2() const;
  GenParticle WLep() const;
  GenParticle WHad() const;
  GenParticle ChargedLepton() const;
  GenParticle Neutrino() const;
  GenParticle Q1() const;
  GenParticle Q2() const;




  bool isQuark(int id);
  bool isLepton(int id);
  bool isChargedLepton(int id);
  bool isNeutrino(int id);

 private:

  GenParticle m_H_bb;
  GenParticle m_H_WW;
  GenParticle m_B1;
  GenParticle m_B2;
  GenParticle m_WLep;
  GenParticle m_WHad;
  GenParticle m_ChargedLepton;
  GenParticle m_Neutrino;
  GenParticle m_Q1;
  GenParticle m_Q2;


};


class HHGenObjectsProducer: public uhh2::AnalysisModule {
 public:
  explicit HHGenObjectsProducer(uhh2::Context & ctx, const std::string & name = "HHgenobjects", bool throw_on_failure=true);
  virtual bool process(uhh2::Event & event) override;

 private: 
  uhh2::Event::Handle<HHGenObjects> h_HHgenobjects;
  bool throw_on_failure;
};
