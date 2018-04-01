//C++ includes
#include <iostream>
//ROOT FILES
#include <TFile.h>
#include <TTree.h>
//LOCAL FILES
#include <pulse.hh>

int main( int argc, char** argv)
{
  //opening input file with pixel data
  TFile* f = new TFile("/Users/cmorgoth/Work/data/test_beam/BTL_March2018/DataCMSVMETiming_Run222.root", "READ");
  //retrieving tree from file
  TTree* tree = (TTree*)f->Get("pulse");
  //creating instance of pulse class
  pulse* mypulse = new pulse( tree );
  mypulse->GetAmps();
  mypulse->GetDeltaT();
  return 0;
}
