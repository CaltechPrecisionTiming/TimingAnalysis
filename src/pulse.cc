#define pulse_cxx
#include "pulse.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>

void pulse::Loop()
{
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

void pulse::GetAmp( int ch )
{
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

   TH1F* h_amp = new TH1F( Form("amp_channel%d",ch), Form("amp_channel%d",ch), 200,0, 500);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( jentry%10000 == 0) std::cout << "[INFO]: events " << jentry << std::endl;
      h_amp->Fill(amp[ch]);
      // if (Cut(ientry) < 0) continue;
   }


   TCanvas *cv = new TCanvas("Cv","Cv", 800,800);
   cv->SetLeftMargin(0.13);
   cv->SetBottomMargin(0.12);
   cv->SetRightMargin(0.05);

   h_amp->Draw();
   cv->SaveAs(Form("amp_ch%d.pdf",ch));
   
   
   return;
};    

void pulse::GetAmps( )
{
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

   TH1F* h_amp[36];
   TF1* landau[36];
   //Histogram definition (units in mV)
   float x_low = 0;
   float x_high = 500;
   int nbins = 100;
   float bin_width = (x_high-x_low)/(float)nbins;
   //define saturation level
   float saturation = 450;//mV
   
   for ( int ch = 0; ch < 36; ch++ )
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
      for ( int ch = 0; ch < 36; ch++ ) h_amp[ch]->Fill(amp[ch]);
      // if (Cut(ientry) < 0) continue;
   }

   //get mpv from histogram
   float mpv_histo[36];
   //define saturation bin
   int saturation_bin = (int)saturation/bin_width;
   //------------------------------
   //locate MPV from histogram only
   //------------------------------
    for ( int ch = 0; ch < 36; ch++ )
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
   for ( int ch = 0; ch < 36; ch++ )
     {
       std::cout << ch << " mpv: " << mpv_histo[ch] << std::endl;
       float mpv_high = 450;
       float mpv_low;
       mpv_low  = mpv_histo[ch]*0.65;
       if ( mpv_histo[ch]*1.6 < 450 ) mpv_high =  mpv_histo[ch]*1.6;
       h_amp[ch]->Fit(Form("landau_%d",ch), "Q", "", mpv_low, mpv_high);
       mpv[ch] = landau[ch]->GetParameter(1);
       std::cout << "MPV: " << mpv[ch] << std::endl;
       h_amp[ch]->Draw();
       cv->SaveAs(Form("amp_ch%d.pdf",ch));
     }
   
   
   return;
}; 

void pulse::GetDeltaT( )
{
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();

   TH1F* h_dt[36];
   for ( int ch = 0; ch < 36; ch++ )
     h_dt[ch] = new TH1F( Form("dt_channel%d",ch), Form("dt_channel%d",ch), 200,-5, 5);
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if ( jentry%10000 == 0) std::cout << "[INFO]: events " << jentry << std::endl;
      for ( int ch = 0; ch < 36; ch++ )
	{
	  if ( ch >= 0  && ch < 9  && amp[0] > 30 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(gaus_mean[0]-LP2_10[ch]);
	  if ( ch >= 9  && ch < 18 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(gaus_mean[9]-LP2_10[ch]);
	  if ( ch >= 18 && ch < 27 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(gaus_mean[18]-LP2_10[ch]);
	  if ( ch >= 27 && ch < 35 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(gaus_mean[27]-LP2_10[ch]);
	}
      // if (Cut(ientry) < 0) continue;
   }


   TCanvas *cv = new TCanvas("Cv","Cv", 800,800);
   cv->SetLeftMargin(0.13);
   cv->SetBottomMargin(0.12);
   cv->SetRightMargin(0.05);
   for ( int ch = 0; ch < 36; ch++ )
     {
       h_dt[ch]->Draw();
       cv->SaveAs(Form("dt_ch%d.pdf",ch));
     }
   
   
   return;
}; 
