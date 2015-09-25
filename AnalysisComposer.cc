// -*- C++ -*-
// Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

#include "AnalysisComposer.hh"

// C++ standard libraries
#include <string>

// Tools
#include "Tools/Tools.hh"
#include "boost/program_options.hpp"
#include "Main/EventSelector.hh"
#include "Main/Systematics.hh"
#include "Main/PDFTool.hh"

// Pxl libraries
#include "Pxl/Pxl/interface/pxl/core.hh"
#include "Pxl/Pxl/interface/pxl/hep.hh"

// The analysis
#include "ledge.h"

namespace po = boost::program_options;

AnalysisComposer::AnalysisComposer() :
    m_analysisName("ledge"),
    runOnData(false) {
}

AnalysisComposer::~AnalysisComposer() {
}

po::options_description AnalysisComposer::getCmdArguments() {
  // You may add your analysis specific options here.
  // you should stor them as member variables of the AnalysisComposer
  // in order to access them later in addForkObjects or endAnalysis
  po::options_description myoptions("Analysis options");
  return myoptions;
}

void AnalysisComposer::endAnalysis() {
  // You may add code here which should be called after the complete
  // analysis has finished. Place e.g. merging of different ForkObject
  // results here.
}

pxl::AnalysisFork AnalysisComposer::addForkObjects(const Tools::MConfig &config,
                                                   std::string outputDirectory,
                                                   pdf::PDFInfo const &pdfInfo,
                                                   EventSelector &selector,
                                                   Systematics &syst_shifter,
                                                   const bool debug) {
  // This is the function where you need to initalize your Analysis.
  // Create one or several implementations of pxl::AnalysisProcess and
  // add it / them to the fork which is returned by this function.
  pxl::AnalysisFork fork;
  fork.setName(m_analysisName);
  // add validation to fork
  LEDge * ledge = nullptr;
  ledge = new LEDge(config);
  fork.insertObject(ledge, "LEDge");
  return fork;
}
