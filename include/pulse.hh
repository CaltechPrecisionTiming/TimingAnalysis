//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Mar 31 10:53:05 2018 by ROOT version 6.12/04
// from TTree pulse/Digitized waveforms
// found on file: /Users/cmorgoth/Work/data/test_beam/BTL_March2018/RawDataSaver0CMSVMETiming_Run160.root
//////////////////////////////////////////////////////////

#ifndef pulse_hh
#define pulse_hh

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class pulse {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

    // Declaration of leaf types
    UInt_t          i_evt;
    Float_t         channel[4][1000];
    Float_t         time[1][1000];
    Float_t         channel_spectrum[4][500];
    Float_t         frequency[500];
    Float_t         baseline[4];
    Float_t         baseline_RMS[4];
    Float_t         amp[4];
    Float_t         t_peak[4];
    Float_t         integral[4];
    Float_t         intfull[4];
    Float_t         risetime[4];
    Float_t         decaytime[4];
    Float_t         LP1_5[4];
    Float_t         LP1_10[4];
    Float_t         LP1_15[4];
    Float_t         LP1_20[4];
    Float_t         LP1_25[4];
    Float_t         LP1_30[4];
    Float_t         LP1_35[4];
    Float_t         LP1_40[4];
    Float_t         LP1_45[4];
    Float_t         LP1_50[4];
    Float_t         LP1_60[4];
    Float_t         LP1_70[4];
    Float_t         LP1_80[4];
    Float_t         LP1_10mV[4];
    Float_t         LP1_15mV[4];
    Float_t         LP1_20mV[4];
    Float_t         LP1_25mV[4];
    Float_t         LP1_35mV[4];
    Float_t         LP1_40mV[4];
    Float_t         LP1_45mV[4];
    Float_t         LP1_50mV[4];
    Float_t         LP1_75mV[4];
    Float_t         LP1_100mV[4];
    Float_t         LP2_5[4];
    Float_t         LP2_10[4];
    Float_t         LP2_15[4];
    Float_t         LP2_20[4];
    Float_t         LP2_25[4];
    Float_t         LP2_30[4];
    Float_t         LP2_35[4];
    Float_t         LP2_40[4];
    Float_t         LP2_45[4];
    Float_t         LP2_50[4];
    Float_t         LP2_60[4];
    Float_t         LP2_70[4];
    Float_t         LP2_80[4];
    Float_t         LP2_10mV[4];
    Float_t         LP2_15mV[4];
    Float_t         LP2_20mV[4];
    Float_t         LP2_25mV[4];
    Float_t         LP2_35mV[4];
    Float_t         LP2_40mV[4];
    Float_t         LP2_45mV[4];
    Float_t         LP2_50mV[4];
    Float_t         LP2_75mV[4];
    Float_t         LP2_100mV[4];
    Float_t         InterpolatedAmp[4];
    Float_t         t0_3[4];
    Float_t         t1_3[4];
    Float_t         tot_3[4];
    Float_t         t0_6[4];
    Float_t         t1_6[4];
    Float_t         tot_6[4];
    Float_t         t0_9[4];
    Float_t         t1_9[4];
    Float_t         tot_9[4];
    Float_t         t0_12[4];
    Float_t         t1_12[4];
    Float_t         tot_12[4];
    Float_t         t0_15[4];
    Float_t         t1_15[4];
    Float_t         tot_15[4];
    Float_t         t0_18[4];
    Float_t         t1_18[4];
    Float_t         tot_18[4];
    Float_t         t0_21[4];
    Float_t         t1_21[4];
    Float_t         tot_21[4];
    Float_t         t0_24[4];
    Float_t         t1_24[4];
    Float_t         tot_24[4];
    Float_t         t0_27[4];
    Float_t         t1_27[4];
    Float_t         tot_27[4];
    Float_t         t0_30[4];
    Float_t         t1_30[4];
    Float_t         tot_30[4];
    Float_t         t0_33[4];
    Float_t         t1_33[4];
    Float_t         tot_33[4];
    Float_t         t0CFD_5[4];
    Float_t         t1CFD_5[4];
    Float_t         totCFD_5[4];
    Float_t         t0CFD_10[4];
    Float_t         t1CFD_10[4];
    Float_t         totCFD_10[4];
    Float_t         t0CFD_15[4];
    Float_t         t1CFD_15[4];
    Float_t         totCFD_15[4];
    Float_t         t0CFD_20[4];
    Float_t         t1CFD_20[4];
    Float_t         totCFD_20[4];
    Float_t         t0CFD_25[4];
    Float_t         t1CFD_25[4];
    Float_t         totCFD_25[4];
    Float_t         t0CFD_30[4];
    Float_t         t1CFD_30[4];
    Float_t         totCFD_30[4];
    Float_t         t0CFD_35[4];
    Float_t         t1CFD_35[4];
    Float_t         totCFD_35[4];
    Float_t         t0CFD_40[4];
    Float_t         t1CFD_40[4];
    Float_t         totCFD_40[4];
    Float_t         t0CFD_45[4];
    Float_t         t1CFD_45[4];
    Float_t         totCFD_45[4];
    Float_t         t0CFD_50[4];
    Float_t         t1CFD_50[4];
    Float_t         totCFD_50[4];
    Float_t         t0CFD_60[4];
    Float_t         t1CFD_60[4];
    Float_t         totCFD_60[4];
    Float_t         t0CFD_70[4];
    Float_t         t1CFD_70[4];
    Float_t         totCFD_70[4];
    Float_t         t0CFD_80[4];
    Float_t         t1CFD_80[4];
    Float_t         totCFD_80[4];
    Float_t         xIntercept;
    Float_t         yIntercept;
    Float_t         xSlope;
    Float_t         ySlope;
    Float_t         x_dut[3];
    Float_t         y_dut[3];
    Float_t         chi2;
    Int_t           ntracks;

  float mpv[36];

   // List of branches
   TBranch        *b_i_evt;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_time;   //!
   TBranch        *b_channel_spectrum;   //!
   TBranch        *b_frequency;   //!
   TBranch        *b_baseline;   //!
   TBranch        *b_baseline_RMS;   //!
   TBranch        *b_amp;   //!
   TBranch        *b_t_peak;   //!
   TBranch        *b_integral;   //!
   TBranch        *b_intfull;   //!
   TBranch        *b_risetime;   //!
   TBranch        *b_decaytime;   //!
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
   TBranch        *b_LP1_60;   //!
   TBranch        *b_LP1_70;   //!
   TBranch        *b_LP1_80;   //!
   TBranch        *b_LP1_10mV;   //!
   TBranch        *b_LP1_15mV;   //!
   TBranch        *b_LP1_20mV;   //!
   TBranch        *b_LP1_25mV;   //!
   TBranch        *b_LP1_35mV;   //!
   TBranch        *b_LP1_40mV;   //!
   TBranch        *b_LP1_45mV;   //!
   TBranch        *b_LP1_50mV;   //!
   TBranch        *b_LP1_75mV;   //!
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
   TBranch        *b_LP2_60;   //!
   TBranch        *b_LP2_70;   //!
   TBranch        *b_LP2_80;   //!
   TBranch        *b_LP2_10mV;   //!
   TBranch        *b_LP2_15mV;   //!
   TBranch        *b_LP2_20mV;   //!
   TBranch        *b_LP2_25mV;   //!
   TBranch        *b_LP2_35mV;   //!
   TBranch        *b_LP2_40mV;   //!
   TBranch        *b_LP2_45mV;   //!
   TBranch        *b_LP2_50mV;   //!
   TBranch        *b_LP2_75mV;   //!
   TBranch        *b_LP2_100mV;   //!
   TBranch        *b_InterpolatedAmp;   //!
   TBranch        *b_t0_3;   //!
   TBranch        *b_t1_3;   //!
   TBranch        *b_tot_3;   //!
   TBranch        *b_t0_6;   //!
   TBranch        *b_t1_6;   //!
   TBranch        *b_tot_6;   //!
   TBranch        *b_t0_9;   //!
   TBranch        *b_t1_9;   //!
   TBranch        *b_tot_9;   //!
   TBranch        *b_t0_12;   //!
   TBranch        *b_t1_12;   //!
   TBranch        *b_tot_12;   //!
   TBranch        *b_t0_15;   //!
   TBranch        *b_t1_15;   //!
   TBranch        *b_tot_15;   //!
   TBranch        *b_t0_18;   //!
   TBranch        *b_t1_18;   //!
   TBranch        *b_tot_18;   //!
   TBranch        *b_t0_21;   //!
   TBranch        *b_t1_21;   //!
   TBranch        *b_tot_21;   //!
   TBranch        *b_t0_24;   //!
   TBranch        *b_t1_24;   //!
   TBranch        *b_tot_24;   //!
   TBranch        *b_t0_27;   //!
   TBranch        *b_t1_27;   //!
   TBranch        *b_tot_27;   //!
   TBranch        *b_t0_30;   //!
   TBranch        *b_t1_30;   //!
   TBranch        *b_tot_30;   //!
   TBranch        *b_t0_33;   //!
   TBranch        *b_t1_33;   //!
   TBranch        *b_tot_33;   //!
   TBranch        *b_t0CFD_5;   //!
   TBranch        *b_t1CFD_5;   //!
   TBranch        *b_totCFD_5;   //!
   TBranch        *b_t0CFD_10;   //!
   TBranch        *b_t1CFD_10;   //!
   TBranch        *b_totCFD_10;   //!
   TBranch        *b_t0CFD_15;   //!
   TBranch        *b_t1CFD_15;   //!
   TBranch        *b_totCFD_15;   //!
   TBranch        *b_t0CFD_20;   //!
   TBranch        *b_t1CFD_20;   //!
   TBranch        *b_totCFD_20;   //!
   TBranch        *b_t0CFD_25;   //!
   TBranch        *b_t1CFD_25;   //!
   TBranch        *b_totCFD_25;   //!
   TBranch        *b_t0CFD_30;   //!
   TBranch        *b_t1CFD_30;   //!
   TBranch        *b_totCFD_30;   //!
   TBranch        *b_t0CFD_35;   //!
   TBranch        *b_t1CFD_35;   //!
   TBranch        *b_totCFD_35;   //!
   TBranch        *b_t0CFD_40;   //!
   TBranch        *b_t1CFD_40;   //!
   TBranch        *b_totCFD_40;   //!
   TBranch        *b_t0CFD_45;   //!
   TBranch        *b_t1CFD_45;   //!
   TBranch        *b_totCFD_45;   //!
   TBranch        *b_t0CFD_50;   //!
   TBranch        *b_t1CFD_50;   //!
   TBranch        *b_totCFD_50;   //!
   TBranch        *b_t0CFD_60;   //!
   TBranch        *b_t1CFD_60;   //!
   TBranch        *b_totCFD_60;   //!
   TBranch        *b_t0CFD_70;   //!
   TBranch        *b_t1CFD_70;   //!
   TBranch        *b_totCFD_70;   //!
   TBranch        *b_t0CFD_80;   //!
   TBranch        *b_t1CFD_80;   //!
   TBranch        *b_totCFD_80;   //!
   TBranch        *b_xIntercept;   //!
   TBranch        *b_yIntercept;   //!
   TBranch        *b_xSlope;   //!
   TBranch        *b_ySlope;   //!
   TBranch        *b_x_dut;   //!
   TBranch        *b_y_dut;   //!
   TBranch        *b_chi2;   //!
   TBranch        *b_ntracks;   //!


   pulse(TTree *tree=0);
   virtual ~pulse();
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
  //Loop, Fits, and Computations are done in these functions; They are used by the end USER Methods
  virtual std::pair<float,float> MPV_vs_Position( int dut = -1, TString coor = "X", const int channel = -1,
						  const float coorLow = 0, const float step = 25.,
						  const float AmpLowCut = 0, const float AmpHighCut = 0.0,
						  float other_corr_low = 0, float other_corr_high = 99999,
						  float photek_low = 0.1, float photek_high = 0.3);

  virtual std::pair<float,float> MPV_vs_Position_ROOFIT( int dut = -1, TString coor = "X", const int channel = -1,
						  const float coorLow = 0, const float step = 25.,
						  const float AmpLowCut = 0, const float AmpHighCut = 0.0,
						  float other_corr_low = 0, float other_corr_high = 99999,
						  float photek_low = 0.1, float photek_high = 0.3);


  virtual std::pair<float,float> DeltaT_vs_Position( int dut = -1, TString coor = "X", const int channel = -1,
						     const int timestampOption = 0,
						     const float coorLow = 0, const float step = 25.,
						     const float AmpLowCut = 0, const float AmpHighCut = 0.0,
						     float other_corr_low = 0, float other_corr_high = 99999, bool _isMean = true,
						     float photek_low = 0.1, float photek_high = 0.3);

  //This Methods are recommended to be used for by end USER
  virtual void CreateMPV_vs_PositionHisto(  int dut, int channelNumber, float binWidth, float threshold_low, float threshold_high,
					    float xmin, float xmax, float ymin, float ymax,
					    float photek_low = 0.1, float photek_high = 0.3);
  virtual void CreateDeltaT_vs_PositionHisto(  int dut, int channelNumber, int timestampOption,
					       float binWidth, float threshold_low, float threshold_high,
					       float xmin, float xmax, float ymin, float ymax,
					       float deltaTMin, float deltaTMax,
					       bool _isMean = true,
					       float photek_low = 0.1, float photek_high = 0.3);
  void MakeEfficiencyVsXY(int channelNumber, int nbins, float threshold, float xmin, float xmax, float ymin, float ymax,
			  float photek_low = 0.1, float photek_high = 0.3);

  void PlotAll_CFD_DeltaTs(unsigned int channelNumber, unsigned int channelNumberReference,
			   double SignalAmpLow = 100, double SignalAmpHigh = 240,
			   double RefAmpLow = 50, double RefAmpHigh = 130);

  void PlotAll_CFD_DeltaTs_SIM(unsigned int channelNumber, double SignalAmpLow = 100, double SignalAmpHigh = 240);

};

#endif

#ifdef pulse_cxx
pulse::pulse(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/Users/cmorgoth/Work/data/test_beam/BTL_March2018/RawDataSaver0CMSVMETiming_Run160.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/Users/cmorgoth/Work/data/test_beam/BTL_March2018/RawDataSaver0CMSVMETiming_Run160.root");
      }
      f->GetObject("pulse",tree);

   }
   Init(tree);
}

pulse::~pulse()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pulse::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pulse::LoadTree(Long64_t entry)
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

void pulse::Init(TTree *tree)
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
   fChain->SetBranchAddress("channel_spectrum", channel_spectrum, &b_channel_spectrum);
   fChain->SetBranchAddress("frequency", frequency, &b_frequency);
   fChain->SetBranchAddress("baseline", baseline, &b_baseline);
   fChain->SetBranchAddress("baseline_RMS", baseline_RMS, &b_baseline_RMS);
   fChain->SetBranchAddress("amp", amp, &b_amp);
   fChain->SetBranchAddress("t_peak", t_peak, &b_t_peak);
   fChain->SetBranchAddress("integral", integral, &b_integral);
   fChain->SetBranchAddress("intfull", intfull, &b_intfull);
   fChain->SetBranchAddress("risetime", risetime, &b_risetime);
   fChain->SetBranchAddress("decaytime", decaytime, &b_decaytime);
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
   fChain->SetBranchAddress("LP1_60", LP1_60, &b_LP1_60);
   fChain->SetBranchAddress("LP1_70", LP1_70, &b_LP1_70);
   fChain->SetBranchAddress("LP1_80", LP1_80, &b_LP1_80);
   fChain->SetBranchAddress("LP1_10mV", LP1_10mV, &b_LP1_10mV);
   fChain->SetBranchAddress("LP1_15mV", LP1_15mV, &b_LP1_15mV);
   fChain->SetBranchAddress("LP1_20mV", LP1_20mV, &b_LP1_20mV);
   fChain->SetBranchAddress("LP1_25mV", LP1_25mV, &b_LP1_25mV);
   fChain->SetBranchAddress("LP1_35mV", LP1_35mV, &b_LP1_35mV);
   fChain->SetBranchAddress("LP1_40mV", LP1_40mV, &b_LP1_40mV);
   fChain->SetBranchAddress("LP1_45mV", LP1_45mV, &b_LP1_45mV);
   fChain->SetBranchAddress("LP1_50mV", LP1_50mV, &b_LP1_50mV);
   fChain->SetBranchAddress("LP1_75mV", LP1_75mV, &b_LP1_75mV);
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
   fChain->SetBranchAddress("LP2_60", LP2_60, &b_LP2_60);
   fChain->SetBranchAddress("LP2_70", LP2_70, &b_LP2_70);
   fChain->SetBranchAddress("LP2_80", LP2_80, &b_LP2_80);
   fChain->SetBranchAddress("LP2_10mV", LP2_10mV, &b_LP2_10mV);
   fChain->SetBranchAddress("LP2_15mV", LP2_15mV, &b_LP2_15mV);
   fChain->SetBranchAddress("LP2_20mV", LP2_20mV, &b_LP2_20mV);
   fChain->SetBranchAddress("LP2_25mV", LP2_25mV, &b_LP2_25mV);
   fChain->SetBranchAddress("LP2_35mV", LP2_35mV, &b_LP2_35mV);
   fChain->SetBranchAddress("LP2_40mV", LP2_40mV, &b_LP2_40mV);
   fChain->SetBranchAddress("LP2_45mV", LP2_45mV, &b_LP2_45mV);
   fChain->SetBranchAddress("LP2_50mV", LP2_50mV, &b_LP2_50mV);
   fChain->SetBranchAddress("LP2_75mV", LP2_75mV, &b_LP2_75mV);
   fChain->SetBranchAddress("LP2_100mV", LP2_100mV, &b_LP2_100mV);
   fChain->SetBranchAddress("InterpolatedAmp", InterpolatedAmp, &b_InterpolatedAmp);
   fChain->SetBranchAddress("t0_3", t0_3, &b_t0_3);
   fChain->SetBranchAddress("t1_3", t1_3, &b_t1_3);
   fChain->SetBranchAddress("tot_3", tot_3, &b_tot_3);
   fChain->SetBranchAddress("t0_6", t0_6, &b_t0_6);
   fChain->SetBranchAddress("t1_6", t1_6, &b_t1_6);
   fChain->SetBranchAddress("tot_6", tot_6, &b_tot_6);
   fChain->SetBranchAddress("t0_9", t0_9, &b_t0_9);
   fChain->SetBranchAddress("t1_9", t1_9, &b_t1_9);
   fChain->SetBranchAddress("tot_9", tot_9, &b_tot_9);
   fChain->SetBranchAddress("t0_12", t0_12, &b_t0_12);
   fChain->SetBranchAddress("t1_12", t1_12, &b_t1_12);
   fChain->SetBranchAddress("tot_12", tot_12, &b_tot_12);
   fChain->SetBranchAddress("t0_15", t0_15, &b_t0_15);
   fChain->SetBranchAddress("t1_15", t1_15, &b_t1_15);
   fChain->SetBranchAddress("tot_15", tot_15, &b_tot_15);
   fChain->SetBranchAddress("t0_18", t0_18, &b_t0_18);
   fChain->SetBranchAddress("t1_18", t1_18, &b_t1_18);
   fChain->SetBranchAddress("tot_18", tot_18, &b_tot_18);
   fChain->SetBranchAddress("t0_21", t0_21, &b_t0_21);
   fChain->SetBranchAddress("t1_21", t1_21, &b_t1_21);
   fChain->SetBranchAddress("tot_21", tot_21, &b_tot_21);
   fChain->SetBranchAddress("t0_24", t0_24, &b_t0_24);
   fChain->SetBranchAddress("t1_24", t1_24, &b_t1_24);
   fChain->SetBranchAddress("tot_24", tot_24, &b_tot_24);
   fChain->SetBranchAddress("t0_27", t0_27, &b_t0_27);
   fChain->SetBranchAddress("t1_27", t1_27, &b_t1_27);
   fChain->SetBranchAddress("tot_27", tot_27, &b_tot_27);
   fChain->SetBranchAddress("t0_30", t0_30, &b_t0_30);
   fChain->SetBranchAddress("t1_30", t1_30, &b_t1_30);
   fChain->SetBranchAddress("tot_30", tot_30, &b_tot_30);
   fChain->SetBranchAddress("t0_33", t0_33, &b_t0_33);
   fChain->SetBranchAddress("t1_33", t1_33, &b_t1_33);
   fChain->SetBranchAddress("tot_33", tot_33, &b_tot_33);
   fChain->SetBranchAddress("t0CFD_5", t0CFD_5, &b_t0CFD_5);
   fChain->SetBranchAddress("t1CFD_5", t1CFD_5, &b_t1CFD_5);
   fChain->SetBranchAddress("totCFD_5", totCFD_5, &b_totCFD_5);
   fChain->SetBranchAddress("t0CFD_10", t0CFD_10, &b_t0CFD_10);
   fChain->SetBranchAddress("t1CFD_10", t1CFD_10, &b_t1CFD_10);
   fChain->SetBranchAddress("totCFD_10", totCFD_10, &b_totCFD_10);
   fChain->SetBranchAddress("t0CFD_15", t0CFD_15, &b_t0CFD_15);
   fChain->SetBranchAddress("t1CFD_15", t1CFD_15, &b_t1CFD_15);
   fChain->SetBranchAddress("totCFD_15", totCFD_15, &b_totCFD_15);
   fChain->SetBranchAddress("t0CFD_20", t0CFD_20, &b_t0CFD_20);
   fChain->SetBranchAddress("t1CFD_20", t1CFD_20, &b_t1CFD_20);
   fChain->SetBranchAddress("totCFD_20", totCFD_20, &b_totCFD_20);
   fChain->SetBranchAddress("t0CFD_25", t0CFD_25, &b_t0CFD_25);
   fChain->SetBranchAddress("t1CFD_25", t1CFD_25, &b_t1CFD_25);
   fChain->SetBranchAddress("totCFD_25", totCFD_25, &b_totCFD_25);
   fChain->SetBranchAddress("t0CFD_30", t0CFD_30, &b_t0CFD_30);
   fChain->SetBranchAddress("t1CFD_30", t1CFD_30, &b_t1CFD_30);
   fChain->SetBranchAddress("totCFD_30", totCFD_30, &b_totCFD_30);
   fChain->SetBranchAddress("t0CFD_35", t0CFD_35, &b_t0CFD_35);
   fChain->SetBranchAddress("t1CFD_35", t1CFD_35, &b_t1CFD_35);
   fChain->SetBranchAddress("totCFD_35", totCFD_35, &b_totCFD_35);
   fChain->SetBranchAddress("t0CFD_40", t0CFD_40, &b_t0CFD_40);
   fChain->SetBranchAddress("t1CFD_40", t1CFD_40, &b_t1CFD_40);
   fChain->SetBranchAddress("totCFD_40", totCFD_40, &b_totCFD_40);
   fChain->SetBranchAddress("t0CFD_45", t0CFD_45, &b_t0CFD_45);
   fChain->SetBranchAddress("t1CFD_45", t1CFD_45, &b_t1CFD_45);
   fChain->SetBranchAddress("totCFD_45", totCFD_45, &b_totCFD_45);
   fChain->SetBranchAddress("t0CFD_50", t0CFD_50, &b_t0CFD_50);
   fChain->SetBranchAddress("t1CFD_50", t1CFD_50, &b_t1CFD_50);
   fChain->SetBranchAddress("totCFD_50", totCFD_50, &b_totCFD_50);
   fChain->SetBranchAddress("t0CFD_60", t0CFD_60, &b_t0CFD_60);
   fChain->SetBranchAddress("t1CFD_60", t1CFD_60, &b_t1CFD_60);
   fChain->SetBranchAddress("totCFD_60", totCFD_60, &b_totCFD_60);
   fChain->SetBranchAddress("t0CFD_70", t0CFD_70, &b_t0CFD_70);
   fChain->SetBranchAddress("t1CFD_70", t1CFD_70, &b_t1CFD_70);
   fChain->SetBranchAddress("totCFD_70", totCFD_70, &b_totCFD_70);
   fChain->SetBranchAddress("t0CFD_80", t0CFD_80, &b_t0CFD_80);
   fChain->SetBranchAddress("t1CFD_80", t1CFD_80, &b_t1CFD_80);
   fChain->SetBranchAddress("totCFD_80", totCFD_80, &b_totCFD_80);
   fChain->SetBranchAddress("xIntercept", &xIntercept, &b_xIntercept);
   fChain->SetBranchAddress("yIntercept", &yIntercept, &b_yIntercept);
   fChain->SetBranchAddress("xSlope", &xSlope, &b_xSlope);
   fChain->SetBranchAddress("ySlope", &ySlope, &b_ySlope);
   fChain->SetBranchAddress("x_dut", &x_dut, &b_x_dut);
   fChain->SetBranchAddress("y_dut", &y_dut, &b_y_dut);
   fChain->SetBranchAddress("chi2", &chi2, &b_chi2);
   fChain->SetBranchAddress("ntracks", &ntracks, &b_ntracks);
   Notify();
}

Bool_t pulse::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pulse::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pulse::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pulse_cxx
