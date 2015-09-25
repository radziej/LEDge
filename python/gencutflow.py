#!/bin/env python
# Copyright [2015] <RWTH Aachen, III. Phys. Inst. A>

import os
import sys
from string import Template
import argparse
import subprocess

cutflow_template= Template("""#include <string>
#include <iostream>

#include <TH1D.h>

const char * stages[] = {
$placeholder
};

TH1D * get_cutflow_histogram() {
    UInt_t size = sizeof(stages) / sizeof(const TH1D *);
    TH1D * h = new TH1D("h1_cutflow", "cutflow", size, 0, size);
    // cout << " found " << size << " stages " << endl;
    for (UInt_t i = 0; i < size; i++) {
      // initialize bin
      h->Fill(stages[i], 0.);
    }
    // deflate -> remove unnecessary labels
    // h->LabelsDeflate();
    // Reset histogram statistics
    h->Reset();
    return h;
}""")

def main():
    # load argument parser
    parser = argparse.ArgumentParser(description="Produce a C++ file containing a function that returns a cutflow histogram.")
    parser.add_argument("files", metavar="file", type=str, nargs="+",
                        help="The filenames of the input files which are being parsed for cutflow stages")
    parser.add_argument("-f", dest="output_file", default="cutflow.h",
                        help="The filename of the output file")

    # parse arguments
    args = parser.parse_args()
    if len(args.files) < 1:
        parser.print_help()
        return 1
    # grep input files for cutflow
    files = " ".join(args.files)
    grep        = subprocess.Popen(["grep", "FillStr(\"cutflow\"", files], stdout=subprocess.PIPE)
    grep2       = subprocess.Popen(["grep", "-v", "//"], stdin=grep.stdout, stdout=subprocess.PIPE)
    cut         = subprocess.Popen(["cut", '-d"', "-f4"], stdin=grep2.stdout, stdout=subprocess.PIPE).communicate()

    # insert C++ quotes
    stages = '"' + '", "'.join(cut[0].splitlines()) + '"'


    # check if output file already exists
    if os.path.isfile(args.output_file):
        # if it does, try to see if the stages are already correct
        with open(args.output_file, "r") as output_file:
            for line in output_file:
                # find the stages array
                if line.startswith("const char * stages[] = {"):
                    # stripping the newline command before comparing
                    if output_file.next().rstrip() == stages:
                        print "File cutflow.h is already up to date. Skipping generation..."
                        return 0

    # open output file
    output_file = open(args.output_file, "w")
    output_file.write(cutflow_template.substitute(placeholder=stages))
    output_file.close()

    return 0


if __name__ == "__main__":
    sys.exit(main())
