// -*- C++ -*-
// Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

#ifndef LEDGE_LEDGE_H_
#define LEDGE_LEDGE_H_

// Tools
// #include "Tools/Tools.hh"
#include "Tools/MConfig.hh"

// Pxl libraries
#include "Pxl/Pxl/interface/pxl/core.hh"
#include "Pxl/Pxl/interface/pxl/hep.hh"

class LEDge : public pxl::AnalysisProcess {
 public:
  LEDge(const Tools::MConfig &cfg);
  ~LEDge();

  void analyseEvent(const pxl::Event *event);
  void endEvent(const pxl::Event *event);
  void endJob(const Serializable *);
 private:

};

#endif // LEDGE_LEDGE_H_
