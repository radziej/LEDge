// -*- C++ -*-
// Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

#include "cutcontainer.h"

// C++ STL includes
#include <string>
#include <unordered_map>

// ROOT libraries
#include "TH1D.h"

////////////////////////////////////////
// Constructor
CutContainer::CutContainer(std::unordered_map<std::string, TH1D *> &histo,
                           double weight) :
    histo_(histo),
    weight_(weight) {
  // Nothing to do
}

////////////////////////////////////////
// Destructor
CutContainer::~CutContainer() {
  // Free up memory of CutPairs
  for (auto &cut : cuts_) {
    delete cut.second;
  }
}

////////////////////////////////////////
// Member functions

void CutContainer::AddCut(std::string name, bool cut, double value) {
  // If the cut does not exist, create it, else update its contents
  if (cuts_.find(name) == cuts_.end()) {
    cuts_[name] = new CutPair(cut, value);
  } else {
    cuts_[name]->first = cut;
    cuts_[name]->second = value;
  }
}

bool CutContainer::PassesAll() {
  bool passes = true;
  for (const auto &cut : cuts_) {
    passes = passes && cut.second->first;
  }
  return passes;
}

bool CutContainer::PassesAllExcept(std::string name) {
  bool passes = true;
  bool cut_found = false;
  for (const auto &cut : cuts_) {
    if (cut.first != name) {
      passes = passes && cut.second->first;
    } else {
      cut_found = true;
    }
  }

  if (!cut_found) {
    throw std::runtime_error("Cut " + name + " does not exist!");
  }
  return passes;
}

void CutContainer::FillHistograms() {
  for (const auto &cut : cuts_) {
    if (!PassesAllExcept(cut.first)) {
      continue;
    }

    std::string name_tmp = "h1_" + cut.first;
    TH1D * hist = (histo_.find(name_tmp) != histo_.end()) ?
        histo_[name_tmp] :
        nullptr;
    if (hist != nullptr) {
      hist->Fill(cut.second->second, weight_);
    } else {
      throw std::runtime_error("Histogram " + name_tmp + " does not exist. Possibly misspelled or not created.");
    }
  }
}
