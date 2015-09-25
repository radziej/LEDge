// -*- C++ -*-
// Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

#ifndef LEDGE_H_
#define LEDGE_H_

// C++ standard libraries
#include <string>
#include <vector>

// Tools
// #include "Tools/Tools.hh"
#include "Tools/MConfig.hh"

// Pxl libraries
#include "Pxl/Pxl/interface/pxl/core.hh"
#include "Pxl/Pxl/interface/pxl/hep.hh"

// ROOT libraries
#include "TFile.h"

class LEDge : public pxl::AnalysisProcess {
 public:
  ///////////////////////////////////////
  // Constructor & Destructor
  explicit LEDge(const Tools::MConfig &cfg);
  ~LEDge();

  ///////////////////////////////////////
  // analysisFork functions
  void analyseEvent(const pxl::Event *event);
  void endJob(const Serializable *);


 private:
  ///////////////////////////////////////
  // Primary functions called from analyseEvent
  void initializeEvent(const pxl::Event *event);
  void releaseEvent();
  void fillParticleVector(std::vector<pxl::Particle *> *all_particles,
                          std::vector<pxl::Particle *> *electrons,
                          std::vector<pxl::Particle *> *muons);
  bool selectTrigger();
  bool preselectLeptons();
  bool selectLeptons();
  bool selectLeptonPairs();
  void fillFinalDistributions();

  ///////////////////////////////////////
  // Secondary functions assisting the primary ones
  bool passPreselection(pxl::Particle *muon);
  bool passMuonID(pxl::Particle *muon);
  bool triggerMatched();
  bool passMuonPairID(std::pair<pxl::Particle *, pxl::Particle *> pair);


  ///////////////////////////////////////
  // Variables
  const bool is_data_;
  std::vector<std::string> trigger_list;

  // Output file
  TFile * output_file_;

  // Muon ID criteria
  double muoid_pt_min_;
  double muoid_eta_max_;
  bool muoid_isglobalmuon_;
  bool muoid_istrackermuon_;
  double muoid_ptrelativeerror_max_;
  int muoid_nmatchedstations_min_;
  int muoid_vhitsmuonsys_min_;
  int muoid_vhitspixel_min_;
  int muoid_trackerlayerswithmeas_min_;
  double muoid_dxy_max_;

  ///////////////////////////////////////
  // Variables set in initializeEvent function

  // Global event weight
  double weight_;

  // Event views
  pxl::EventView *rec_evt_view_;
  pxl::EventView *gen_evt_view_;
  pxl::EventView *tri_evt_view_;

  // Particle counts
  unsigned int num_muo_;
  unsigned int num_ele_;
  // unsigned int num_gam_;
  // unsigned int num_tau_;
  // unsigned int num_met_;
  // unsigned int num_jet_;

  // Particle vectors
  std::vector<pxl::Particle *> muos_;
  std::vector<pxl::Particle *> eles_;
  // std::vector<pxl::Particle *> taus_;
  // std::vector<pxl::Particle *> gams_;
  // std::vector<pxl::Particle *> mets_;
  // std::vector<pxl::Particle *> jets_;

  // Gen particle vectors
  std::vector<pxl::Particle *> muos_gen_;
  std::vector<pxl::Particle *> eles_gen_;
  // std::vector<pxl::Particle *> taus_gen_;
  // std::vector<pxl::Particle *> gams_gen_;
  // std::vector<pxl::Particle *> mets_gen_;
  // std::vector<pxl::Particle *> jets_gen_;

  // Lepton pair vector
  std::vector<std::pair<pxl::Particle *, pxl::Particle *>> muo_pairs_;

  // Lepton candidates
  pxl::Particle *muo_candidate_1_ = nullptr;
  pxl::Particle *muo_candidate_2_ = nullptr;
  pxl::Particle *muo_gen_candidate_1_ = nullptr;
  pxl::Particle *muo_gen_candidate_2_ = nullptr;
};

#endif  // LEDGE_H_
