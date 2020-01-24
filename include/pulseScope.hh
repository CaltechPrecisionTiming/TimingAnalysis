//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Apr 28 12:36:57 2018 by ROOT version 6.12/06
// from TTree pulse/Digitized waveforms
// found on file: DataNetScope_Run1200.root
//////////////////////////////////////////////////////////

#ifndef pulseScope_hh
#define pulseScope_hh

#include <iostream>

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "pulse.hh"

// Header file for the classes stored in the TTree if any.

class pulseScope {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   static const int nchannels = 4;
   static const int nsamples = 1000;
   static const int ntimes = 1;
   float mpv[nchannels];
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          i_evt;
   Float_t         channel[nsamples];
   Float_t         time[ntimes][nsamples];
   Float_t         baseline[nchannels];
   Float_t         baseline_RMS[nchannels];
   Float_t         amp[nchannels];
   Float_t         t_peak[nchannels];
   Float_t         integral[nchannels];
   Float_t         intfull[nchannels];
   Float_t         risetime[nchannels];
   Float_t         decaytime[nchannels];
   Float_t         gaus_mean[nchannels];
   Float_t         gaus_sigma[nchannels];
   Float_t         gaus_chi2[nchannels];
   Float_t         LP1_5[nchannels];
   Float_t         LP1_10[nchannels];
   Float_t         LP1_15[nchannels];
   Float_t         LP1_20[nchannels];
   Float_t         LP1_25[nchannels];
   Float_t         LP1_30[nchannels];
   Float_t         LP1_35[nchannels];
   Float_t         LP1_40[nchannels];
   Float_t         LP1_45[nchannels];
   Float_t         LP1_50[nchannels];
   Float_t         LP1_55[nchannels];
   Float_t         LP1_60[nchannels];
   Float_t         LP1_65[nchannels];
   Float_t         LP1_70[nchannels];
   Float_t         LP1_75[nchannels];
   Float_t         LP1_80[nchannels];
   Float_t         LP1_90[nchannels];
   Float_t         LP1_20mV[nchannels];
   Float_t         LP1_30mV[nchannels];
   Float_t         LP1_40mV[nchannels];
   Float_t         LP1_60mV[nchannels];
   Float_t         LP1_80mV[nchannels];
   Float_t         LP1_90mV[nchannels];
   Float_t         LP1_100mV[nchannels];
   Float_t         LP2_5[nchannels];
   Float_t         LP2_10[nchannels];
   Float_t         LP2_15[nchannels];
   Float_t         LP2_20[nchannels];
   Float_t         LP2_25[nchannels];
   Float_t         LP2_30[nchannels];
   Float_t         LP2_35[nchannels];
   Float_t         LP2_40[nchannels];
   Float_t         LP2_45[nchannels];
   Float_t         LP2_50[nchannels];
   Float_t         LP2_55[nchannels];
   Float_t         LP2_60[nchannels];
   Float_t         LP2_65[nchannels];
   Float_t         LP2_70[nchannels];
   Float_t         LP2_75[nchannels];
   Float_t         LP2_80[nchannels];
   Float_t         LP2_90[nchannels];
   Float_t         LP2_20mV[nchannels];
   Float_t         LP2_30mV[nchannels];
   Float_t         LP2_40mV[nchannels];
   Float_t         LP2_60mV[nchannels];
   Float_t         LP2_80mV[nchannels];
   Float_t         LP2_90mV[nchannels];
   Float_t         LP2_100mV[nchannels];
   Float_t         LP3_5[nchannels];
   Float_t         LP3_10[nchannels];
   Float_t         LP3_15[nchannels];
   Float_t         LP3_20[nchannels];
   Float_t         LP3_25[nchannels];
   Float_t         LP3_30[nchannels];
   Float_t         LP3_35[nchannels];
   Float_t         LP3_40[nchannels];
   Float_t         LP3_45[nchannels];
   Float_t         LP3_50[nchannels];
   Float_t         LP3_55[nchannels];
   Float_t         LP3_60[nchannels];
   Float_t         LP3_65[nchannels];
   Float_t         LP3_70[nchannels];
   Float_t         LP3_75[nchannels];
   Float_t         LP3_80[nchannels];
   Float_t         LP3_90[nchannels];
   Float_t         LP3_20mV[nchannels];
   Float_t         LP3_30mV[nchannels];
   Float_t         LP3_40mV[nchannels];
   Float_t         LP3_60mV[nchannels];
   Float_t         LP3_80mV[nchannels];
   Float_t         LP3_90mV[nchannels];
   Float_t         LP3_100mV[nchannels];

   // List of branches
   TBranch        *b_i_evt;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_time;   //!
   TBranch        *b_baseline;   //!
   TBranch        *b_baseline_RMS;   //!
   TBranch        *b_amp;   //!
   TBranch        *b_t_peak;   //!
   TBranch        *b_integral;   //!
   TBranch        *b_intfull;   //!
   TBranch        *b_risetime;   //!
   TBranch        *b_decaytime;   //!
   TBranch        *b_gaus_mean;   //!
   TBranch        *b_gaus_sigma;   //!
   TBranch        *b_gaus_chi2;   //!
   TBranch        *b_LP1_5;   //!
   TBranch        *b_LP1_10;   //!
   TBranch        *b_LP1_15;   //!
   TBranch        *b_LP1_20;   //!
   TBranch        *b_LP1_25;   //!
   TBranch        *b_LP1_30;   //!
   TBranch        *b_LP1_35;   //!
   TBranch        *b_LP1_40;   //!
   TBranch        *b_LP1_45;   //!
   TBranch        *b_LP1_50;   //!
   TBranch        *b_LP1_55;   //!
   TBranch        *b_LP1_60;   //!
   TBranch        *b_LP1_65;   //!
   TBranch        *b_LP1_70;   //!
   TBranch        *b_LP1_75;   //!
   TBranch        *b_LP1_80;   //!
   TBranch        *b_LP1_90;   //!
   TBranch        *b_LP1_20mV;   //!
   TBranch        *b_LP1_30mV;   //!
   TBranch        *b_LP1_40mV;   //!
   TBranch        *b_LP1_60mV;   //!
   TBranch        *b_LP1_80mV;   //!
   TBranch        *b_LP1_90mV;   //!
   TBranch        *b_LP1_100mV;   //!
   TBranch        *b_LP2_5;   //!
   TBranch        *b_LP2_10;   //!
   TBranch        *b_LP2_15;   //!
   TBranch        *b_LP2_20;   //!
   TBranch        *b_LP2_25;   //!
   TBranch        *b_LP2_30;   //!
   TBranch        *b_LP2_35;   //!
   TBranch        *b_LP2_40;   //!
   TBranch        *b_LP2_45;   //!
   TBranch        *b_LP2_50;   //!
   TBranch        *b_LP2_55;   //!
   TBranch        *b_LP2_60;   //!
   TBranch        *b_LP2_65;   //!
   TBranch        *b_LP2_70;   //!
   TBranch        *b_LP2_75;   //!
   TBranch        *b_LP2_80;   //!
   TBranch        *b_LP2_90;   //!
   TBranch        *b_LP2_20mV;   //!
   TBranch        *b_LP2_30mV;   //!
   TBranch        *b_LP2_40mV;   //!
   TBranch        *b_LP2_60mV;   //!
   TBranch        *b_LP2_80mV;   //!
   TBranch        *b_LP2_90mV;   //!
   TBranch        *b_LP2_100mV;   //!
   TBranch        *b_LP3_5;   //!
   TBranch        *b_LP3_10;   //!
   TBranch        *b_LP3_15;   //!
   TBranch        *b_LP3_20;   //!
   TBranch        *b_LP3_25;   //!
   TBranch        *b_LP3_30;   //!
   TBranch        *b_LP3_35;   //!
   TBranch        *b_LP3_40;   //!
   TBranch        *b_LP3_45;   //!
   TBranch        *b_LP3_50;   //!
   TBranch        *b_LP3_55;   //!
   TBranch        *b_LP3_60;   //!
   TBranch        *b_LP3_65;   //!
   TBranch        *b_LP3_70;   //!
   TBranch        *b_LP3_75;   //!
   TBranch        *b_LP3_80;   //!
   TBranch        *b_LP3_90;   //!
   TBranch        *b_LP3_20mV;   //!
   TBranch        *b_LP3_30mV;   //!
   TBranch        *b_LP3_40mV;   //!
   TBranch        *b_LP3_60mV;   //!
   TBranch        *b_LP3_80mV;   //!
   TBranch        *b_LP3_90mV;   //!
   TBranch        *b_LP3_100mV;   //!


   pulseScope(TTree *tree=0);
   virtual ~pulseScope();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   void              GetAmp( int ch = -1 );
   void              GetAmps( );
   void              GetDeltaT( );
};

#endif

#ifdef pulseScope_cxx

pulseScope::pulseScope(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("DataNetScope_Run1200.root");
    if (!f || !f->IsOpen()) {
       f = new TFile("DataNetScope_Run1200.root");
    }
    f->GetObject("pulse",tree);

 }
 Init(tree);
}

pulseScope::~pulseScope()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pulseScope::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pulseScope::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void pulseScope::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("i_evt", &i_evt, &b_i_evt);
   fChain->SetBranchAddress("channel", channel, &b_channel);
   fChain->SetBranchAddress("time", time, &b_time);
   fChain->SetBranchAddress("baseline", baseline, &b_baseline);
   fChain->SetBranchAddress("baseline_RMS", baseline_RMS, &b_baseline_RMS);
   fChain->SetBranchAddress("amp", amp, &b_amp);
   fChain->SetBranchAddress("t_peak", t_peak, &b_t_peak);
   fChain->SetBranchAddress("integral", integral, &b_integral);
   fChain->SetBranchAddress("intfull", intfull, &b_intfull);
   fChain->SetBranchAddress("risetime", risetime, &b_risetime);
   fChain->SetBranchAddress("decaytime", decaytime, &b_decaytime);
   fChain->SetBranchAddress("gaus_mean", gaus_mean, &b_gaus_mean);
   fChain->SetBranchAddress("gaus_sigma", gaus_sigma, &b_gaus_sigma);
   fChain->SetBranchAddress("gaus_chi2", gaus_chi2, &b_gaus_chi2);
   fChain->SetBranchAddress("LP1_5", LP1_5, &b_LP1_5);
   fChain->SetBranchAddress("LP1_10", LP1_10, &b_LP1_10);
   fChain->SetBranchAddress("LP1_15", LP1_15, &b_LP1_15);
   fChain->SetBranchAddress("LP1_20", LP1_20, &b_LP1_20);
   fChain->SetBranchAddress("LP1_25", LP1_25, &b_LP1_25);
   fChain->SetBranchAddress("LP1_30", LP1_30, &b_LP1_30);
   fChain->SetBranchAddress("LP1_35", LP1_35, &b_LP1_35);
   fChain->SetBranchAddress("LP1_40", LP1_40, &b_LP1_40);
   fChain->SetBranchAddress("LP1_45", LP1_45, &b_LP1_45);
   fChain->SetBranchAddress("LP1_50", LP1_50, &b_LP1_50);
   fChain->SetBranchAddress("LP1_55", LP1_55, &b_LP1_55);
   fChain->SetBranchAddress("LP1_60", LP1_60, &b_LP1_60);
   fChain->SetBranchAddress("LP1_65", LP1_65, &b_LP1_65);
   fChain->SetBranchAddress("LP1_70", LP1_70, &b_LP1_70);
   fChain->SetBranchAddress("LP1_75", LP1_75, &b_LP1_75);
   fChain->SetBranchAddress("LP1_80", LP1_80, &b_LP1_80);
   fChain->SetBranchAddress("LP1_90", LP1_90, &b_LP1_90);
   fChain->SetBranchAddress("LP1_20mV", LP1_20mV, &b_LP1_20mV);
   fChain->SetBranchAddress("LP1_30mV", LP1_30mV, &b_LP1_30mV);
   fChain->SetBranchAddress("LP1_40mV", LP1_40mV, &b_LP1_40mV);
   fChain->SetBranchAddress("LP1_60mV", LP1_60mV, &b_LP1_60mV);
   fChain->SetBranchAddress("LP1_80mV", LP1_80mV, &b_LP1_80mV);
   fChain->SetBranchAddress("LP1_90mV", LP1_90mV, &b_LP1_90mV);
   fChain->SetBranchAddress("LP1_100mV", LP1_100mV, &b_LP1_100mV);
   fChain->SetBranchAddress("LP2_5", LP2_5, &b_LP2_5);
   fChain->SetBranchAddress("LP2_10", LP2_10, &b_LP2_10);
   fChain->SetBranchAddress("LP2_15", LP2_15, &b_LP2_15);
   fChain->SetBranchAddress("LP2_20", LP2_20, &b_LP2_20);
   fChain->SetBranchAddress("LP2_25", LP2_25, &b_LP2_25);
   fChain->SetBranchAddress("LP2_30", LP2_30, &b_LP2_30);
   fChain->SetBranchAddress("LP2_35", LP2_35, &b_LP2_35);
   fChain->SetBranchAddress("LP2_40", LP2_40, &b_LP2_40);
   fChain->SetBranchAddress("LP2_45", LP2_45, &b_LP2_45);
   fChain->SetBranchAddress("LP2_50", LP2_50, &b_LP2_50);
   fChain->SetBranchAddress("LP2_55", LP2_55, &b_LP2_55);
   fChain->SetBranchAddress("LP2_60", LP2_60, &b_LP2_60);
   fChain->SetBranchAddress("LP2_65", LP2_65, &b_LP2_65);
   fChain->SetBranchAddress("LP2_70", LP2_70, &b_LP2_70);
   fChain->SetBranchAddress("LP2_75", LP2_75, &b_LP2_75);
   fChain->SetBranchAddress("LP2_80", LP2_80, &b_LP2_80);
   fChain->SetBranchAddress("LP2_90", LP2_90, &b_LP2_90);
   fChain->SetBranchAddress("LP2_20mV", LP2_20mV, &b_LP2_20mV);
   fChain->SetBranchAddress("LP2_30mV", LP2_30mV, &b_LP2_30mV);
   fChain->SetBranchAddress("LP2_40mV", LP2_40mV, &b_LP2_40mV);
   fChain->SetBranchAddress("LP2_60mV", LP2_60mV, &b_LP2_60mV);
   fChain->SetBranchAddress("LP2_80mV", LP2_80mV, &b_LP2_80mV);
   fChain->SetBranchAddress("LP2_90mV", LP2_90mV, &b_LP2_90mV);
   fChain->SetBranchAddress("LP2_100mV", LP2_100mV, &b_LP2_100mV);
   fChain->SetBranchAddress("LP3_5", LP3_5, &b_LP3_5);
   fChain->SetBranchAddress("LP3_10", LP3_10, &b_LP3_10);
   fChain->SetBranchAddress("LP3_15", LP3_15, &b_LP3_15);
   fChain->SetBranchAddress("LP3_20", LP3_20, &b_LP3_20);
   fChain->SetBranchAddress("LP3_25", LP3_25, &b_LP3_25);
   fChain->SetBranchAddress("LP3_30", LP3_30, &b_LP3_30);
   fChain->SetBranchAddress("LP3_35", LP3_35, &b_LP3_35);
   fChain->SetBranchAddress("LP3_40", LP3_40, &b_LP3_40);
   fChain->SetBranchAddress("LP3_45", LP3_45, &b_LP3_45);
   fChain->SetBranchAddress("LP3_50", LP3_50, &b_LP3_50);
   fChain->SetBranchAddress("LP3_55", LP3_55, &b_LP3_55);
   fChain->SetBranchAddress("LP3_60", LP3_60, &b_LP3_60);
   fChain->SetBranchAddress("LP3_65", LP3_65, &b_LP3_65);
   fChain->SetBranchAddress("LP3_70", LP3_70, &b_LP3_70);
   fChain->SetBranchAddress("LP3_75", LP3_75, &b_LP3_75);
   fChain->SetBranchAddress("LP3_80", LP3_80, &b_LP3_80);
   fChain->SetBranchAddress("LP3_90", LP3_90, &b_LP3_90);
   fChain->SetBranchAddress("LP3_20mV", LP3_20mV, &b_LP3_20mV);
   fChain->SetBranchAddress("LP3_30mV", LP3_30mV, &b_LP3_30mV);
   fChain->SetBranchAddress("LP3_40mV", LP3_40mV, &b_LP3_40mV);
   fChain->SetBranchAddress("LP3_60mV", LP3_60mV, &b_LP3_60mV);
   fChain->SetBranchAddress("LP3_80mV", LP3_80mV, &b_LP3_80mV);
   fChain->SetBranchAddress("LP3_90mV", LP3_90mV, &b_LP3_90mV);
   fChain->SetBranchAddress("LP3_100mV", LP3_100mV, &b_LP3_100mV);
   Notify();
}

Bool_t pulseScope::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pulseScope::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pulseScope::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pulse_cxx
