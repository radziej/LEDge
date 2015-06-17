//-*- C++ -*-
// Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

#ifndef LEDGE_ANALYSISCOMPOSER_HH_
#define LEDGE_ANALYSISCOMPOSER_HH_

// C++ Standard libraries
#include <string>

// Tools
#include "Tools/Tools.hh"
#include "boost/program_options.hpp"
#include "Main/EventSelector.hh"
#include "Main/PDFTool.hh"

// Pxl libraries
#include "Pxl/Pxl/interface/pxl/core.hh"
#include "Pxl/Pxl/interface/pxl/hep.hh"

namespace po = boost::program_options;

class AnalysisComposer {
 public:
  AnalysisComposer();
  ~AnalysisComposer();

  po::options_description getCmdArguments();
  pxl::AnalysisFork addForkObjects(const Tools::MConfig &config,
                                   std::string outputDirectory,
                                   pdf::PDFInfo const &pdfInfo,
                                   EventSelector &selector,
                                   const bool debug);
  void endAnalysis();

 private:
  std::string m_analysisName;
  bool runOnData;
};

#endif  // LEDGE_ANALYSISCOMPOSER_HH_
