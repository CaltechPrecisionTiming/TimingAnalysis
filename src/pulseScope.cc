#define pulseScope_cxx
#include "pulseScope.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>
#include <TGraphErrors.h>
//#include "EfficiencyUtils.hh"
#include <TSystem.h>
#include <TTree.h>
#include <TLatex.h>
#include <TString.h>
#include <TFile.h>
#include <TH1D.h>
#include <TF1.h>
#include <TBox.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TRandom3.h>
#include <TLegend.h>
#include <TMath.h>
#include <TROOT.h>
#include <Math/GaussIntegrator.h>
#include <Math/IntegratorOptions.h>
//ROOFIT INCLUDES
#include <RooWorkspace.h>
#include <RooDataSet.h>
#include <RooRealVar.h>
#include <RooExponential.h>
#include <RooAddPdf.h>
#include <RooGaussian.h>
#include <RooLandau.h>
#include <RooFFTConvPdf.h>
#include <RooMinimizer.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include <RooExtendPdf.h>
#include <RooStats/SPlot.h>
#include <RooStats/ModelConfig.h>
#include <RooGenericPdf.h>
#include <RooFormulaVar.h>
#include <RooBernstein.h>
#include <RooMinuit.h>
#include <RooNLLVar.h>
#include <RooRandom.h>
#include <RooDataHist.h>
#include <RooHistPdf.h>
#include <RooArgList.h>
#include <RooRealBinding.h>
#include <RooBrentRootFinder.h>
#include <RooDerivative.h>

void pulseScope::Loop()
{
//   In a ROOT session, you can do:
//      root> .L pulse.C
//      root> pulse t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}


void pulseScope::GetAmps( )
{
   if (fChain == 0) return;
   fChain->SetBranchStatus("*", 0);
   fChain->SetBranchStatus("amp", 1);
   Long64_t nentries = fChain->GetEntriesFast();

   TH1F* h_amp[nchannels];
   TF1* landau[nchannels];
   //Histogram definition (units in mV)
   float x_low = 0;
   float x_high = 350;
   int nbins = 100;
   float bin_width = (x_high-x_low)/(float)nbins;
   //define saturation level
   float saturation = 350;//mV
   //const float ch_saturation[4] = {80., 160., 200., 350.};
   //const float ch_noise[4] = {25., 70., 100., 30.};
   const float ch_saturation[4] = {150., 160., 220., 350.};
   const float ch_noise[4] = {80., 70., 100., 30.};

   for ( int ch = 0; ch < nchannels; ch++ )
     {
       h_amp[ch]  = new TH1F( Form("amp_channel%d",ch), Form("amp_channel%d",ch), nbins, x_low, x_high);
       landau[ch] = new TF1( Form("landau_%d",ch), "landau", 10, 450 );
     }
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( jentry%10000 == 0) std::cout << "[INFO]: events " << jentry << std::endl;
      for ( int ch = 0; ch < nchannels; ch++ )
      {
        if( amp[ch] < ch_noise[ch] || amp[ch] > ch_saturation[ch] ) continue;
        h_amp[ch]->Fill(amp[ch]);
      }
      // if (Cut(ientry) < 0) continue;
   }

   //get mpv from histogram
   float mpv_histo[nchannels];
   //define saturation bin
   int saturation_bin = (int)saturation/bin_width;
   //------------------------------
   //locate MPV from histogram only
   //------------------------------
    for ( int ch = 0; ch < nchannels; ch++ )
     {
       //define noise bin
       //int noise_bin = (int)(10.*baseline_RMS[ch]/bin_width);
       int noise_bin = (int)(30./bin_width);//
       std::cout << "noise bin: " << noise_bin << std::endl;
       int max = 0;
       int max_bin = 0;
       for( int bin = noise_bin; bin <= saturation_bin; bin++ )
	 {
	   if ( h_amp[ch]->GetBinContent(bin) > max )
	     {
	       max = h_amp[ch]->GetBinContent(bin);
	       max_bin = bin;
	     }
	 }
       mpv_histo[ch] = h_amp[ch]->GetBinLowEdge(max_bin);
     }

   TCanvas *cv = new TCanvas("Cv","Cv", 800,800);
   cv->SetLeftMargin(0.13);
   cv->SetBottomMargin(0.12);
   cv->SetRightMargin(0.05);
   for ( int ch = 0; ch < nchannels; ch++ )
     {
        if( h_amp[ch]->GetEntries() < 5 ) continue;
       std::cout << ch << " mpv: " << mpv_histo[ch] << std::endl;
       float mpv_high = 450;
       float mpv_low;
       mpv_low  = mpv_histo[ch]*0.75;

       if ( mpv_histo[ch]*1.7 < 450 ) mpv_high =  mpv_histo[ch]*1.7;
       h_amp[ch]->Fit(Form("landau_%d",ch), "Q", "", mpv_low, mpv_high);
       mpv[ch] = landau[ch]->GetParameter(1);
       std::cout << "MPV: " << mpv[ch] << std::endl;
       h_amp[ch]->Draw();
       cv->SetLogy();
       cv->SaveAs(Form("amp_ch%d.pdf",ch));
     }

  for ( int ch = 0; ch < nchannels; ch++ )
  {
    delete h_amp[ch];
    delete landau[ch];
  }
  delete cv;
    std::cout << "passed here" << std::endl;
  return;
  std::cout << "passed here" << std::endl;
};

void pulseScope::GetDeltaT( )
{
  std::cout << "Get Delta T" << std::endl;
   if (fChain == 0) return;
   fChain->SetBranchStatus("*",0);
   fChain->SetBranchStatus("amp",1);
   fChain->SetBranchStatus("LP1_5",1);
   fChain->SetBranchStatus("LP1_10",1);
   fChain->SetBranchStatus("LP1_15",1);
   fChain->SetBranchStatus("LP1_20",1);
   fChain->SetBranchStatus("LP1_25",1);
   fChain->SetBranchStatus("LP1_30",1);
   fChain->SetBranchStatus("LP1_35",1);
   fChain->SetBranchStatus("LP1_40",1);
   fChain->SetBranchStatus("LP2_5",1);
   fChain->SetBranchStatus("LP2_10",1);
   fChain->SetBranchStatus("LP2_15",1);
   fChain->SetBranchStatus("LP2_20",1);
   fChain->SetBranchStatus("LP2_25",1);
   fChain->SetBranchStatus("LP2_30",1);
   fChain->SetBranchStatus("LP2_35",1);
   fChain->SetBranchStatus("LP2_40",1);
   //
   fChain->SetBranchStatus("LP3_5",1);
   fChain->SetBranchStatus("LP3_10",1);
   fChain->SetBranchStatus("LP3_15",1);
   fChain->SetBranchStatus("LP3_20",1);
   fChain->SetBranchStatus("LP3_25",1);
   fChain->SetBranchStatus("LP3_30",1);
   fChain->SetBranchStatus("LP3_35",1);
   fChain->SetBranchStatus("LP3_40",1);
   Long64_t nentries = fChain->GetEntriesFast();

   TH1F* h_dt[256];
   TF1* gausF[256];
   //for ( int ch = 0; ch < 36; ch++ )
   for ( int ch = 0; ch < nchannels; ch++ )
   {
     for ( int i = 0; i < 8; i++ )
     {
       for ( int j = 0; j < 8; j++ )
       {
         h_dt[64*ch+8*i+j]  = new TH1F( Form("dt_channel%d_%d_%d",ch, i, j), Form("dt_channel%d_%d_%d",ch,i,j), 400,-10,10);
         gausF[64*ch+8*i+j] = new TF1( Form("gausF%d_%d_%d", ch,i, j), "gaus(0)", -10, 10);
       }
     }
   }

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( jentry%10000 == 0) std::cout << "[INFO]: events " << jentry << std::endl;
      for ( int ch = 0; ch < nchannels; ch++ )
      {
        if ( ch >= 0  && ch < 9  && amp[0] > 0.65*mpv[0] && amp[0] < 1.6*mpv[0] && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] )
        {
          h_dt[64*ch]->Fill(LP1_5[0]-LP2_5[ch]);
          h_dt[64*ch+1]->Fill(LP1_5[0]-LP2_10[ch]);
          h_dt[64*ch+2]->Fill(LP1_5[0]-LP2_15[ch]);
          h_dt[64*ch+3]->Fill(LP1_5[0]-LP2_20[ch]);
          h_dt[64*ch+4]->Fill(LP1_5[0]-LP2_25[ch]);
          h_dt[64*ch+5]->Fill(LP1_5[0]-LP2_30[ch]);
          h_dt[64*ch+6]->Fill(LP1_5[0]-LP2_35[ch]);
          h_dt[64*ch+7]->Fill(LP1_5[0]-LP2_40[ch]);
          //
          h_dt[64*ch+8]->Fill(LP1_10[0]-LP2_5[ch]);
          h_dt[64*ch+9]->Fill(LP1_10[0]-LP2_10[ch]);
          h_dt[64*ch+10]->Fill(LP1_10[0]-LP2_15[ch]);
          h_dt[64*ch+11]->Fill(LP1_10[0]-LP2_20[ch]);
          h_dt[64*ch+12]->Fill(LP1_10[0]-LP2_25[ch]);
          h_dt[64*ch+13]->Fill(LP1_10[0]-LP2_30[ch]);
          h_dt[64*ch+14]->Fill(LP1_10[0]-LP2_35[ch]);
          h_dt[64*ch+15]->Fill(LP1_10[0]-LP2_40[ch]);
          //
          h_dt[64*ch+16]->Fill(LP1_15[0]-LP2_5[ch]);
          h_dt[64*ch+17]->Fill(LP1_15[0]-LP2_10[ch]);
          h_dt[64*ch+18]->Fill(LP1_15[0]-LP2_15[ch]);
          h_dt[64*ch+19]->Fill(LP1_15[0]-LP2_20[ch]);
          h_dt[64*ch+20]->Fill(LP1_15[0]-LP2_25[ch]);
          h_dt[64*ch+21]->Fill(LP1_15[0]-LP2_30[ch]);
          h_dt[64*ch+22]->Fill(LP1_15[0]-LP2_35[ch]);
          h_dt[64*ch+23]->Fill(LP1_15[0]-LP2_40[ch]);
          //
          h_dt[64*ch+24]->Fill(LP1_20[0]-LP2_5[ch]);
          h_dt[64*ch+25]->Fill(LP1_20[0]-LP2_10[ch]);
          h_dt[64*ch+26]->Fill(LP1_20[0]-LP2_15[ch]);
          h_dt[64*ch+27]->Fill(LP1_20[0]-LP2_20[ch]);
          h_dt[64*ch+28]->Fill(LP1_20[0]-LP2_25[ch]);
          h_dt[64*ch+29]->Fill(LP1_20[0]-LP2_30[ch]);
          h_dt[64*ch+30]->Fill(LP1_20[0]-LP2_35[ch]);
          h_dt[64*ch+31]->Fill(LP1_20[0]-LP2_40[ch]);
          //
          h_dt[64*ch+32]->Fill(LP1_25[0]-LP2_5[ch]);
          h_dt[64*ch+33]->Fill(LP1_25[0]-LP2_10[ch]);
          h_dt[64*ch+34]->Fill(LP1_25[0]-LP2_15[ch]);
          h_dt[64*ch+35]->Fill(LP1_25[0]-LP2_20[ch]);
          h_dt[64*ch+36]->Fill(LP1_25[0]-LP2_25[ch]);
          h_dt[64*ch+37]->Fill(LP1_25[0]-LP2_30[ch]);
          h_dt[64*ch+38]->Fill(LP1_25[0]-LP2_35[ch]);
          h_dt[64*ch+30]->Fill(LP1_25[0]-LP2_40[ch]);
          //
          h_dt[64*ch+40]->Fill(LP1_30[0]-LP2_5[ch]);
          h_dt[64*ch+41]->Fill(LP1_30[0]-LP2_10[ch]);
          h_dt[64*ch+42]->Fill(LP1_30[0]-LP2_15[ch]);
          h_dt[64*ch+43]->Fill(LP1_30[0]-LP2_20[ch]);
          h_dt[64*ch+44]->Fill(LP1_30[0]-LP2_25[ch]);
          h_dt[64*ch+45]->Fill(LP1_30[0]-LP2_30[ch]);
          h_dt[64*ch+46]->Fill(LP1_30[0]-LP2_35[ch]);
          h_dt[64*ch+47]->Fill(LP1_30[0]-LP2_40[ch]);
          //
          h_dt[64*ch+48]->Fill(LP1_35[0]-LP2_5[ch]);
          h_dt[64*ch+49]->Fill(LP1_35[0]-LP2_10[ch]);
          h_dt[64*ch+50]->Fill(LP1_35[0]-LP2_15[ch]);
          h_dt[64*ch+51]->Fill(LP1_35[0]-LP2_20[ch]);
          h_dt[64*ch+52]->Fill(LP1_35[0]-LP2_25[ch]);
          h_dt[64*ch+53]->Fill(LP1_35[0]-LP2_30[ch]);
          h_dt[64*ch+54]->Fill(LP1_35[0]-LP2_35[ch]);
          h_dt[64*ch+55]->Fill(LP1_35[0]-LP2_40[ch]);
          //
          h_dt[64*ch+56]->Fill(LP1_40[0]-LP2_5[ch]);
          h_dt[64*ch+57]->Fill(LP1_40[0]-LP2_10[ch]);
          h_dt[64*ch+58]->Fill(LP1_40[0]-LP2_15[ch]);
          h_dt[64*ch+59]->Fill(LP1_40[0]-LP2_20[ch]);
          h_dt[64*ch+60]->Fill(LP1_40[0]-LP2_25[ch]);
          h_dt[64*ch+61]->Fill(LP1_40[0]-LP2_30[ch]);
          h_dt[64*ch+62]->Fill(LP1_40[0]-LP2_35[ch]);
          h_dt[64*ch+63]->Fill(LP1_40[0]-LP2_40[ch]);
        }
	  	}
      // if (Cut(ientry) < 0) continue;
   }

   TCanvas *cv = new TCanvas("Cv","Cv", 800,800);
   cv->SetLeftMargin(0.13);
   cv->SetBottomMargin(0.12);
   cv->SetRightMargin(0.05);
   //gStyle->SetOptStat(1111);
   gStyle->SetStatX(0.99);
   gStyle->SetStatY(0.99);
   gStyle->SetOptFit();
   for ( int ch = 0; ch < nchannels; ch++ )
     {
       for ( int i = 0; i < 8; i++ )
       {
         for ( int j = 0; j < 8; j++ )
         {
           /*gausF[64*ch+8*i+j]->SetParameter(0, h_dt[ch]->GetEntries());
           gausF[64*ch+8*i+j]->SetParameter(1, h_dt[ch]->GetMean());
           gausF[64*ch+8*i+j]->SetParameter(2, h_dt[ch]->GetRMS());*/
           h_dt[64*ch+8*i+j]->Fit(Form("gausF%d_%d_%d", ch,i, j), "LQ", "", h_dt[64*ch+8*i+j]->GetMean()-2.0*h_dt[64*ch+8*i+j]->GetRMS(),
            h_dt[64*ch+8*i+j]->GetMean()+2.*h_dt[64*ch+8*i+j]->GetRMS());
           h_dt[64*ch+8*i+j]->GetXaxis()->SetRangeUser(h_dt[64*ch+8*i+j]->GetMean()-6.*h_dt[64*ch+8*i+j]->GetRMS(),
            h_dt[64*ch+8*i+j]->GetMean()+6.*h_dt[64*ch+8*i+j]->GetRMS());
           h_dt[64*ch+8*i+j]->SetXTitle("#Delta t [ns] ");
           h_dt[64*ch+8*i+j]->SetTitle("");
           h_dt[64*ch+8*i+j]->SetMarkerStyle(20);
           h_dt[64*ch+8*i+j]->SetMarkerSize(2);
           h_dt[64*ch+8*i+j]->SetMarkerColor(kBlue);
           h_dt[64*ch+8*i+j]->Draw("E");
           cv->SaveAs(Form("dt_ch%d_%d_%d.pdf",ch,i,j));
         }
       }
     }


   return;
};
