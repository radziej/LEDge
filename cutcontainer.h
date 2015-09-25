// -*- C++ -*-
// Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

#ifndef CUTCONTAINER_H_
#define CUTCONTAINER_H_

#include <string>
#include <unordered_map>

// ROOT libraries
#include "TH1D.h"

typedef std::pair<bool, double> CutPair;

class CutContainer {
 public:
  CutContainer(std::unordered_map<std::string, TH1D *> &histo, double weight);
  ~CutContainer();

  void AddCut(std::string name, bool cut, double value);
  bool PassesAll();
  bool PassesAllExcept(std::string name);
  void FillHistograms();


 private:
  std::unordered_map<std::string, TH1D *> &histo_;
  std::unordered_map<std::string, CutPair *> cuts_;
  double weight_;
};

#endif  // CUTCONTAINER_H_
