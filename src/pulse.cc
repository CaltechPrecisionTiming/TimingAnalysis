#define pulse_cxx
#include "pulse.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF1.h>
#include <iostream>
#include <TGraphErrors.h>
#include "EfficiencyUtils.hh"
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

using namespace std;

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
	  if ( ch >= 0  && ch < 9  && amp[0] > 30 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(t0CFD_20[0]-LP2_10[ch]);
	  if ( ch >= 9  && ch < 18 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(t0CFD_20[9]-LP2_10[ch]);
	  if ( ch >= 18 && ch < 27 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(t0CFD_20[18]-LP2_10[ch]);
	  if ( ch >= 27 && ch < 35 && amp[ch] > 0.65*mpv[ch] && amp[ch] < 1.6*mpv[ch] ) h_dt[ch]->Fill(t0CFD_20[27]-LP2_10[ch]);
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




void pulse::MakeEfficiencyVsXY(int channelNumber, int nbins, float threshold, float xmin, float xmax, float ymin, float ymax,
			       float photek_low, float photek_high)
{
  //declare histograms
  float histo_x_min = 10.;
  float histo_x_max = 30.;
  float histo_y_min = 10.;
  float histo_y_max = 30.;

  TH1F *histY_den = new TH1F("histX_den",";Y [mm];Number of Events", nbins, histo_y_min, histo_y_max);
  TH1F *histY_num = new TH1F("histX_num",";Y [mm];Number of Events", nbins, histo_y_min, histo_y_max);
  TH1F *histX_den = new TH1F("histY_den",";X [mm];Number of Events", nbins, histo_x_min, histo_x_max);
  TH1F *histX_num = new TH1F("histY_num",";X [mm];Number of Events", nbins, histo_x_min, histo_x_max);

  //Activate Only Necessary Branches
  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("amp", 1);
  fChain->SetBranchStatus("x_dut", 1);
  fChain->SetBranchStatus("y_dut", 1);
  fChain->SetBranchStatus("ntracks", 1);
  fChain->SetBranchStatus("chi2", 1);
  fChain->SetBranchStatus("xSlope", 1);
  fChain->SetBranchStatus("ySlope", 1);

  if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (jentry % 10000 == 0) cout << "Processing Event " << jentry << " of " << nentries << "\n";

      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //cuts

      //require photek to show MIP signal
      if (!(amp[0] > photek_low && amp[0] < photek_high)) continue;

      //reject events with more than 1 track
      if ( !(ntracks == 1 && chi2 < 10 )) continue;

      // if ( !(fabs(xSlope) < 5e-4 && fabs(ySlope) < 5e-4)) continue;
      //if ( !(fabs(xSlope) < 1e-3 && (fabs(ySlope) < 4e-3) && fabs(ySlope) > 3e-3)) continue;
      //if ( !(fabs(xSlope + 1.12687e-04) < 5e-4 && fabs(ySlope + 3.546e-3) < 5e-4)) continue; //For CNM W9HG11 Run 838-839-841
      if ( !(amp[channelNumber] < 450 )) continue;//No saturation


      //For irradiated 50D sensor on UCSC board (ch1), require that the particle is within the sensor circular region
      //if (!(sqrt(pow(x_dut[0] - 13930,2) + pow(y_dut[0] - 21830 ,2)) < 400)) continue;

      if ( y_dut[2] > ymin && y_dut[2] < ymax ) {
	histX_den->Fill( x_dut[2]);
	if ( amp[channelNumber] > threshold ) {
	    histX_num->Fill( x_dut[0] );
	}
      }

      if ( x_dut[2] > xmin && x_dut[2] < xmax ) {
	histY_den->Fill(y_dut[2] );
	if ( amp[channelNumber] > threshold ) {
	  histY_num->Fill( y_dut[2] );
	}
      }


   }

   vector<double> xbins;
   vector<double> ybins;
   TGraphAsymmErrors* effX = createEfficiencyGraph(histX_num, histX_den,
						   Form("EfficiencyVsX_Channel%d",channelNumber),
						   xbins,
						   histo_x_min, histo_x_max,
						   0.0, 1.0,
						   false
						   );
   TGraphAsymmErrors* effY = createEfficiencyGraph(histY_num, histY_den,
						   Form("EfficiencyVsY_Channel%d",channelNumber),
						   ybins,
						   histo_y_min, histo_y_max,
						   0.0, 1.0,
						   false
						   );

   //Find x,y position for the max efficiency
   double x_eff_low, x_eff_high;
   double y_eff_low, y_eff_high;
   double dummy_eff;
   //For X
   for ( int i = 1; i <= nbins; i++ )
     {
       effX->GetPoint( i, x_eff_low, dummy_eff );
       if( dummy_eff > 0.5 ) break;
     }

   for ( int i = 1; i <= nbins; i++ )
     {
       effX->GetPoint( nbins-i, x_eff_high, dummy_eff );
       if( dummy_eff > 0.5 ) break;
     }

   //For Y
   for ( int i = 1; i <= nbins; i++ )
     {
       effY->GetPoint( i, y_eff_low, dummy_eff );
       if( dummy_eff > 0.5 ) break;
     }

   for ( int i = 1; i <= nbins; i++ )
     {
       effY->GetPoint( nbins-i, y_eff_high, dummy_eff );
       if( dummy_eff > 0.5 ) break;
     }


   //std::cout << " x:" << y_eff_low << " - " << y_eff_high << std::endl;
   //Cosmetics
   effX->SetTitle("");
   effX->GetXaxis()->SetTitleSize(0.05);
   effX->GetXaxis()->SetTitleOffset(0.87);
   effX->GetYaxis()->SetTitleSize(0.05);
   effX->GetYaxis()->SetTitleOffset(0.83);
   effX->SetMarkerStyle(kBlue);
   effX->SetMarkerSize(1.1);
   effX->SetMarkerColor(kBlue);
   effX->SetLineColor(kBlue);
   effX->SetMarkerStyle(20);
   effX->GetYaxis()->SetTitle("Efficiency");
   effX->GetXaxis()->SetTitle("x-coordinate [mm]");
   effX->GetXaxis()->SetRangeUser( x_eff_low-1., x_eff_high+1.);
   effX->GetYaxis()->SetRangeUser( 0, 1.11);


   effY->SetTitle("");
   effY->GetXaxis()->SetTitleSize(0.05);
   effY->GetXaxis()->SetTitleOffset(0.87);
   effY->GetYaxis()->SetTitleSize(0.05);
   effY->GetYaxis()->SetTitleOffset(0.83);
   effY->SetMarkerStyle(20);
   effY->SetMarkerStyle(kBlue);
   effY->SetMarkerSize(1.1);
   effY->SetMarkerColor(kBlue);
   effY->SetLineColor(kBlue);
   effY->SetMarkerStyle(20);
   effY->GetYaxis()->SetTitle("Efficiency");
   effY->GetXaxis()->SetTitle("y-coordinate [mm]");
   effY->GetXaxis()->SetRangeUser( y_eff_low-1., y_eff_high+1.);
   effY->GetYaxis()->SetRangeUser( 0, 1.11);

   TCanvas* c = new TCanvas("canvas","canvas",600,400);
   effX->Draw("AP");
   c->SaveAs(Form("Eff_vs_X_Ch%d.pdf",channelNumber));
   c->SaveAs(Form("Eff_vs_X_Ch%d.C",channelNumber));
   effY->Draw("AP");
   c->SaveAs(Form("Eff_vs_Y_Ch%d.pdf",channelNumber));
   c->SaveAs(Form("Eff_vs_Y_Ch%d.C",channelNumber));
   delete c;


   //Activate all branches back to normal
   fChain->SetBranchStatus("*", 1);

   TFile *file = new TFile(Form("eff_Channel%d.root", channelNumber),"UPDATE");
   file->cd();
   file->WriteTObject(effX, "Efficiency_X", "WriteDelete");
   file->WriteTObject(effY, "Efficiency_Y", "WriteDelete");
   file->WriteTObject(histX_num, "histX_num", "WriteDelete");
   file->WriteTObject(histX_den, "histX_den", "WriteDelete");
   file->WriteTObject(histY_num, "histY_num", "WriteDelete");
   file->WriteTObject(histY_den, "histY_den", "WriteDelete");
   file->Close();
   delete file;
};



void pulse::CreateMPV_vs_PositionHisto( int dut, int channelNumber, float binWidth, float threshold_low, float threshold_high,
					float xmin, float xmax, float ymin, float ymax,
					float photek_low, float photek_high)
{
   if ( dut <= 0 || dut > 2 )
     {
       std::cerr << "[ERROR]: please provide a valid dut = <1,2>" << std::endl;
       return;
     }
  //x_init, y_init, and steps are in microns
  //const int npoints = 30;


  //------------------
  //Define initial positions and step size, all units are in microns
  //-------------------
  float x_init    = 10000.;//microns
  float y_init    = 10000.;//microns
  int niterations = (int)((30000.-10000.)/binWidth);//microns


  float x_pos[niterations];//x-positions
  float x_pos_un[niterations];//x-position uncertainty
  float mpv_x[niterations];//mpv amplitude for x
  float mpv_x_un[niterations];//uncertainty on mpv amplitude x
  float y_pos[niterations];//y-positions
  float y_pos_un[niterations];//y-position uncertainty
  float mpv_y[niterations];//mpv amplitude for x
  float mpv_y_un[niterations];//uncertainty on mpv amplitude y


  const float um_to_mm = 0.001;
  float average_x = 0;
  float average_y = 0;
  int npoints_above_zero_x = 0;
  int npoints_above_zero_y = 0;
  for ( int i = 0; i < niterations; i++ )
    {
      x_pos[i] = x_init + binWidth*(float)i;
      x_pos_un[i] = 0;
      std::pair<float,float> MPVAndError_X = MPV_vs_Position_ROOFIT( dut, "X", channelNumber, x_pos[i], binWidth, threshold_low, threshold_high, ymin, ymax,
       							      photek_low, photek_high );
      x_pos[i] = x_pos[i]*um_to_mm;
      mpv_x[i] = MPVAndError_X.first;
      mpv_x_un[i] = MPVAndError_X.second;
      if ( mpv_x_un[i]/mpv_x[i] > 0.5 )
	{
	  cout << "MPV: " << x_pos[i] << " : " << mpv_x[i] << " +/- " << mpv_x_un[i] << "\n";
	   mpv_x[i]    = 0;
	   mpv_x_un[i] = 0;
	}
      if ( mpv_x[i] > 0 && mpv_x[i] < 0.5)
	{
	  npoints_above_zero_x++;
	  average_x += mpv_x[i];
	}

      y_pos[i] = y_init + binWidth*(float)i;
      y_pos_un[i] = 0;
      std::pair<float,float> MPVAndError_Y = MPV_vs_Position_ROOFIT( dut, "Y", channelNumber, y_pos[i], binWidth, threshold_low, threshold_high, xmin, xmax,
							      photek_low, photek_high);
      y_pos[i] = y_pos[i]*um_to_mm;
      mpv_y[i] = MPVAndError_Y.first;
      mpv_y_un[i] = MPVAndError_Y.second;
      if ( mpv_y_un[i]/mpv_y[i] > 0.1 )
	{
	  mpv_y[i]    = 0;
	  mpv_y_un[i] = 0;
	}
      if ( mpv_y[i] > 0 && mpv_y[i] < 0.5)
	{
	  npoints_above_zero_y++;
	  average_y += mpv_y[i];
	}

    }

  TGraphErrors* gr_mpv_x = new TGraphErrors(niterations, x_pos, mpv_x, x_pos_un, mpv_x_un);
  TGraphErrors* gr_mpv_y = new TGraphErrors(niterations, y_pos, mpv_y, y_pos_un, mpv_y_un);
  average_x = average_x/((float)npoints_above_zero_x);
  average_y = average_y/((float)npoints_above_zero_y);
  std::cout << "x: " <<  average_x << " y: " << average_y << std::endl;

  //Find x,y position for the max efficiency
   double x_eff_low, x_eff_high;
   double y_eff_low, y_eff_high;
   double dummy_eff;
   //For X
   for ( int i = 1; i <= niterations; i++ )
     {
       gr_mpv_x->GetPoint( i, x_eff_low, dummy_eff );
       if( dummy_eff > 0.8*average_x ) break;
     }

   for ( int i = 1; i <= niterations; i++ )
     {
       gr_mpv_x->GetPoint( niterations-i, x_eff_high, dummy_eff );
       if( dummy_eff > 0.8*average_x ) break;
     }

   //For Y
   for ( int i = 1; i <= niterations; i++ )
     {
       gr_mpv_y->GetPoint( i, y_eff_low, dummy_eff );
       if( dummy_eff > 0.8*average_y ) break;
     }

   for ( int i = 1; i <= niterations; i++ )
     {
       gr_mpv_y->GetPoint( niterations-i, y_eff_high, dummy_eff );
       if( dummy_eff > 0.8*average_y ) break;
     }

  //Cosmetics
  gr_mpv_x->GetYaxis()->SetRangeUser(0,2.8*max(average_x,average_y));
  gr_mpv_x->GetXaxis()->SetRangeUser(x_eff_low-1.0,x_eff_high+1.0);
  gr_mpv_x->SetTitle("");
  gr_mpv_x->GetXaxis()->SetTitle("x-coordinate [mm]");
  gr_mpv_x->GetYaxis()->SetTitle("m.p.v [V]");
  gr_mpv_x->GetXaxis()->SetTitleSize(0.05);
  gr_mpv_x->GetXaxis()->SetTitleOffset(0.87);
  gr_mpv_x->GetYaxis()->SetTitleSize(0.05);
  gr_mpv_x->GetYaxis()->SetTitleOffset(0.98);
  gr_mpv_x->SetMarkerStyle(20);
  gr_mpv_x->SetMarkerStyle(kBlue);
  gr_mpv_x->SetMarkerSize(1.1);
  gr_mpv_x->SetMarkerColor(kBlue);
  gr_mpv_x->SetLineColor(kBlue);
  gr_mpv_x->SetMarkerStyle(20);

  gr_mpv_y->GetYaxis()->SetRangeUser(0,2.8*max(average_x,average_y));
  gr_mpv_y->GetXaxis()->SetRangeUser(y_eff_low-1.0,y_eff_high+1.0);
  gr_mpv_y->SetTitle("");
  gr_mpv_y->GetXaxis()->SetTitle("y-coordinate [mm]");
  gr_mpv_y->GetYaxis()->SetTitle("m.p.v [V]");
  gr_mpv_y->GetXaxis()->SetTitleSize(0.05);
  gr_mpv_y->GetXaxis()->SetTitleOffset(0.87);
  gr_mpv_y->GetYaxis()->SetTitleSize(0.05);
  gr_mpv_y->GetYaxis()->SetTitleOffset(0.98);
  gr_mpv_y->SetMarkerStyle(20);
  gr_mpv_y->SetMarkerStyle(kBlue);
  gr_mpv_y->SetMarkerSize(1.1);
  gr_mpv_y->SetMarkerColor(kBlue);
  gr_mpv_y->SetLineColor(kBlue);
  gr_mpv_y->SetMarkerStyle(20);

  TCanvas* c = new TCanvas("canvas","canvas",600,400);
  gr_mpv_x->Draw("AP");
  c->SaveAs(Form("MPV_vs_X_Ch%d.pdf",channelNumber));
  c->SaveAs(Form("MPV_vs_X_Ch%d.C",channelNumber));
  gr_mpv_y->Draw("AP");
  c->SaveAs(Form("MPV_vs_Y_Ch%d.pdf",channelNumber));
  c->SaveAs(Form("MPV_vs_Y_Ch%d.C",channelNumber));
  delete c;
  TFile* fout = new TFile(Form("mpv_tgraphs_Channel%d.root", channelNumber), "RECREATE");
  gr_mpv_x->Write("mpv_x");
  gr_mpv_y->Write("mpv_y");
  fout->Close();
};


void pulse::CreateDeltaT_vs_PositionHisto( int dut, int channelNumber, int timestampOption,
					   float binWidth, float threshold_low, float threshold_high,
					   float xmin, float xmax, float ymin, float ymax,
					   float deltaTMin, float deltaTMax,
					   bool _isMean,
					   float photek_low, float photek_high)
{
   if ( dut <= 0 || dut > 2 )
     {
       std::cerr << "[ERROR]: please provide a valid dut = <1,2>" << std::endl;
       return;
     }
  //x_init, y_init, and steps are in microns
  //const int npoints = 30;


  //------------------
  //Define initial positions and step size, all units are in microns
  //-------------------
  float x_init    = 10000.;//microns
  float y_init    = 10000.;//microns
  int niterations = (int)((30000.-10000.)/binWidth);//microns

  float x_pos[niterations];//x-positions
  float x_pos_un[niterations];//x-position uncertainty
  float deltaT_x[niterations];//deltaT amplitude for x
  float deltaT_x_un[niterations];//uncertainty on deltaT amplitude x
  float y_pos[niterations];//y-positions
  float y_pos_un[niterations];//y-position uncertainty
  float deltaT_y[niterations];//deltaT amplitude for x
  float deltaT_y_un[niterations];//uncertainty on deltaT amplitude y

  const float um_to_mm = 0.001;
  const float ns_to_ps = 1000.;
  float average_x = 0;
  float average_y = 0;
  int npoints_above_zero_x = 0;
  int npoints_above_zero_y = 0;
  for ( int i = 0; i < niterations; i++ )
    {
      x_pos[i] = x_init + binWidth*(float)i;
      x_pos_un[i] = 0;
      std::pair<float,float> DeltaTAndError_X;

      if ( _isMean )
	{
	  DeltaTAndError_X = DeltaT_vs_Position( dut, "X", channelNumber, timestampOption, x_pos[i], binWidth, threshold_low, threshold_high, ymin, ymax, true, photek_low, photek_high );
	}
      else
	{
	  DeltaTAndError_X = DeltaT_vs_Position( dut, "X", channelNumber, timestampOption, x_pos[i], binWidth, threshold_low, threshold_high, ymin, ymax, false, photek_low, photek_high );
	}
      x_pos[i] = x_pos[i]*um_to_mm;
      deltaT_x[i] = DeltaTAndError_X.first*ns_to_ps;
      deltaT_x_un[i] = DeltaTAndError_X.second*ns_to_ps;
      if ( deltaT_x_un[i]/deltaT_x[i] > 0.9 )
	{
	  deltaT_x[i]    = 0;
	  deltaT_x_un[i] = 0;
	}
      if ( deltaT_x[i] > -10000 && deltaT_x[i] < 10000)
	{
	  npoints_above_zero_x++;
	  average_x += deltaT_x[i];
	}


      y_pos[i] = y_init + binWidth*(float)i;
      y_pos_un[i] = 0;
      std::pair<float,float> DeltaTAndError_Y;
      if ( _isMean )
	{
	  DeltaTAndError_Y = DeltaT_vs_Position( dut, "Y", channelNumber, timestampOption, y_pos[i], binWidth, threshold_low, threshold_high, xmin, xmax, true, photek_low, photek_high );
	}
      else
	{
	  DeltaTAndError_Y = DeltaT_vs_Position( dut, "Y", channelNumber, timestampOption, y_pos[i], binWidth, threshold_low, threshold_high, xmin, xmax, false, photek_low, photek_high );
	}
      y_pos[i] = y_pos[i]*um_to_mm;
      deltaT_y[i] = DeltaTAndError_Y.first*ns_to_ps;
      deltaT_y_un[i] = DeltaTAndError_Y.second*ns_to_ps;
      if ( deltaT_y_un[i]/deltaT_y[i] > 0.9 )
	{
	  deltaT_y[i]    = 0;
	  deltaT_y_un[i] = 0;
	}
      if ( deltaT_y[i] > -10000 && deltaT_y[i] < 10000)
	{
	  npoints_above_zero_y++;
	  average_y += deltaT_y[i];
	}

    }

  TGraphErrors* gr_deltaT_x = new TGraphErrors(niterations, x_pos, deltaT_x, x_pos_un, deltaT_x_un);
  TGraphErrors* gr_deltaT_y = new TGraphErrors(niterations, y_pos, deltaT_y, y_pos_un, deltaT_y_un);
  average_x = average_x/((float)npoints_above_zero_x);
  average_y = average_y/((float)npoints_above_zero_y);
  std::cout << "x: " <<  average_x << " y: " << average_y << std::endl;

  //Find x,y position for the max efficiency
   double x_eff_low, x_eff_high;
   double y_eff_low, y_eff_high;
   double dummy_eff;
   //For X
   for ( int i = 1; i <= niterations; i++ )
     {
       gr_deltaT_x->GetPoint( i, x_eff_low, dummy_eff );
       if( dummy_eff > 0.8*average_x ) break;
     }

   for ( int i = 1; i <= niterations; i++ )
     {
       gr_deltaT_x->GetPoint( niterations-i, x_eff_high, dummy_eff );
       if( dummy_eff > 0.8*average_x ) break;
     }

   //For Y
   for ( int i = 1; i <= niterations; i++ )
     {
       gr_deltaT_y->GetPoint( i, y_eff_low, dummy_eff );
       if( dummy_eff > 0.8*average_y ) break;
     }

   for ( int i = 1; i <= niterations; i++ )
     {
       gr_deltaT_y->GetPoint( niterations-i, y_eff_high, dummy_eff );
       if( dummy_eff > 0.8*average_y ) break;
     }

   //Cosmetics
   gr_deltaT_x->GetYaxis()->SetRangeUser(deltaTMin, deltaTMax);
   gr_deltaT_x->GetXaxis()->SetRangeUser(xmin*um_to_mm,xmax*um_to_mm);
   gr_deltaT_x->SetTitle("");
   gr_deltaT_x->GetXaxis()->SetTitle("x-coordinate [mm]");
   if ( _isMean ) gr_deltaT_x->GetYaxis()->SetTitle("#Delta t [ps]");
   else gr_deltaT_x->GetYaxis()->SetTitle("Time resolution [ps]");
   gr_deltaT_x->GetXaxis()->SetTitleSize(0.05);
   gr_deltaT_x->GetXaxis()->SetTitleOffset(0.87);
   gr_deltaT_x->GetYaxis()->SetTitleSize(0.05);
   gr_deltaT_x->GetYaxis()->SetTitleOffset(0.83);
   gr_deltaT_x->SetMarkerStyle(20);
   gr_deltaT_x->SetMarkerStyle(kBlue);
   gr_deltaT_x->SetMarkerSize(1.1);
   gr_deltaT_x->SetMarkerColor(kBlue);
   gr_deltaT_x->SetLineColor(kBlue);
   gr_deltaT_x->SetMarkerStyle(20);

   gr_deltaT_y->GetYaxis()->SetRangeUser(deltaTMin, deltaTMax);
   //gr_deltaT_y->GetYaxis()->SetRangeUser(-10000,10000);
   gr_deltaT_y->GetXaxis()->SetRangeUser(ymin*um_to_mm,ymax*um_to_mm);
   gr_deltaT_y->SetTitle("");
   gr_deltaT_y->GetXaxis()->SetTitle("y-coordinate [mm]");
   if ( _isMean ) gr_deltaT_y->GetYaxis()->SetTitle("#Delta t [ps]");
   else gr_deltaT_y->GetYaxis()->SetTitle("Time resolution [ps]");
   gr_deltaT_y->GetXaxis()->SetTitleSize(0.05);
   gr_deltaT_y->GetXaxis()->SetTitleOffset(0.87);
   gr_deltaT_y->GetYaxis()->SetTitleSize(0.05);
   gr_deltaT_y->GetYaxis()->SetTitleOffset(0.83);
   gr_deltaT_y->SetMarkerStyle(20);
   gr_deltaT_y->SetMarkerStyle(kBlue);
   gr_deltaT_y->SetMarkerSize(1.1);
   gr_deltaT_y->SetMarkerColor(kBlue);
   gr_deltaT_y->SetLineColor(kBlue);
   gr_deltaT_y->SetMarkerStyle(20);

  TString fname;
  if ( _isMean )
    {
      TCanvas* c = new TCanvas("canvas","canvas",600,400);
      gr_deltaT_x->Draw("AP");
      c->SaveAs(Form("MeanTime_vs_X_Ch%d.pdf",channelNumber));
      c->SaveAs(Form("MeanTime_vs_X_Ch%d.C",channelNumber));
      gr_deltaT_y->Draw("AP");
      c->SaveAs(Form("MeanTime_vs_Y_Ch%d.pdf",channelNumber));
      c->SaveAs(Form("MeanTime_vs_Y_Ch%d.C",channelNumber));
      delete c;
      fname = Form("deltaT_mean_tgraphs_Channel%d.root", channelNumber);
    }
  else
    {
      TCanvas* c = new TCanvas("canvas","canvas",600,400);
      gr_deltaT_x->Draw("AP");
      c->SaveAs(Form("TimeResolution_vs_X_Ch%d.pdf",channelNumber));
      c->SaveAs(Form("TimeResolution_vs_X_Ch%d.C",channelNumber));
      gr_deltaT_y->Draw("AP");
      c->SaveAs(Form("TimeResolution_vs_Y_Ch%d.pdf",channelNumber));
      c->SaveAs(Form("TimeResolution_vs_Y_Ch%d.C",channelNumber));
      delete c;
      fname = Form("deltaT_time_resolution_tgraphs_Channel%d.root", channelNumber);
    }
  TFile* fout = new TFile( fname, "RECREATE");
  gr_deltaT_x->Write("time_x");
  gr_deltaT_y->Write("time_y");
  fout->Close();
};


std::pair<float,float> pulse::MPV_vs_Position( int dut, TString coor, const int channel, const float coorLow, const float step,
					       const float AmpLowCut, const float AmpHighCut,
					       float other_corr_low, float other_corr_high,
					       float photek_low, float photek_high)
{
  if ( channel < 0 ) return std::pair<float,float>(-999,0);
  if ( dut <= 0 || dut > 2 )
    {
      std::cerr << "[ERROR]: please provide a valid dut = <1,2>" << std::endl;
      return std::pair<float,float>(-999,0);
    }

  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("amp", 1);
  fChain->SetBranchStatus("x_dut", 1);
  fChain->SetBranchStatus("y_dut", 1);
  if (fChain == 0) return std::pair<float,float>(-999,0);
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  cout << "Running MPV_vs_Position Analysis\n";
  cout << "Total Events: " << nentries << "\n";
  TH1F* h_mpv = new TH1F("h_mpv", "h_mpv", 100, 0, 0.5);
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (ientry % 10000 == 0) cout << "Processing Event " << ientry << "\n";
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( amp[channel] >= AmpLowCut && amp[channel] <= AmpHighCut && amp[0] > photek_low && amp[0] < photek_high )
	{
	  if ( dut == 1 )
	    {
	      if ( (coor == "x" || coor == "X") && x_dut[0] >= coorLow && x_dut[0] < (coorLow + step) && y_dut[0] > other_corr_low && y_dut[0] < other_corr_high ) h_mpv->Fill(amp[channel]);
	      if ( (coor == "y" || coor == "Y") && y_dut[0] >= coorLow && y_dut[0] < (coorLow + step) && x_dut[0] > other_corr_low && x_dut[0] < other_corr_high ) h_mpv->Fill(amp[channel]);
	    }
	  else if ( dut == 2 )
	    {
	      if ( (coor == "x" || coor == "X") && x_dut[1] >= coorLow && x_dut[1] < (coorLow + step) && y_dut[1] > other_corr_low && y_dut[1] < other_corr_high ) h_mpv->Fill(amp[channel]);
	      if ( (coor == "y" || coor == "Y") && y_dut[1] >= coorLow && y_dut[1] < (coorLow + step) && x_dut[1] > other_corr_low && x_dut[1] < other_corr_high ) h_mpv->Fill(amp[channel]);
	    }
	}
    }

  //Restoring all branches
  fChain->SetBranchStatus("*", 1);
  //Fitting
  TF1* landau = new TF1( "landau", "landau", AmpLowCut, AmpHighCut );
  h_mpv->Fit("landau","Q","", AmpLowCut, AmpHighCut);
  std::pair<float,float> result;
  result.first = landau->GetParameter(1);
  result.second = landau->GetParError(1);
  //Creating output file
  //Creating output file
  std::string myCoor;
  if ( coor == "X" || coor == "x" ) myCoor = "X";
  if ( coor == "Y" || coor == "y" ) myCoor = "Y";

  TString fname = Form("mpv_Channel%d_step%.2f_%s.root", channel,coorLow + step, myCoor.c_str());
  TFile* fout = new TFile(fname, "recreate");
  h_mpv->Write();
  fout->Close();
  return result;
};

std::pair<float,float> pulse::MPV_vs_Position_ROOFIT( int dut, TString coor, const int channel, const float coorLow, const float step,
					       const float AmpLowCut, const float AmpHighCut,
					       float other_corr_low, float other_corr_high,
					       float photek_low, float photek_high)
{
  if ( channel < 0 ) return std::pair<float,float>(-999,0);
  if ( dut <= 0 || dut > 2 )
    {
      std::cerr << "[ERROR]: please provide a valid dut = <1,2>" << std::endl;
      return std::pair<float,float>(-999,0);
    }

  //------------------------------
  //RooFit Setup
  //------------------------------
  RooRealVar Amp( "amplitude", "Amp", 0, 0.5, "V" );
  Amp.setBins(100);
  Amp.setRange( "fitRange", 0.01, 0.35 );
  RooDataSet data( "data", "", RooArgSet(Amp) );

  //---------------
  //Define Model
  //---------------
  // Construct landau(t,ml,sl) ;
  //RooRealVar ml("ml", "mean landau", 5.0e-02);
  //RooRealVar ml("ml","mean landau",0.055);
  RooRealVar ml("ml", "mean landau", 3.0e-02, 0, 1.0);
  ml.setConstant( kFALSE );
  //  RooRealVar sl("sl", "sigma landau", 1.95e-03) ;
  //RooRealVar sl("sl","sigma landau",0.01);
  RooRealVar sl("sl", "sigma landau", 0.5e-03, 0, 1.0) ;
  sl.setConstant( kFALSE );
  RooLandau landau("lx", "lx",Amp,ml,sl);

  // Construct gauss(t,mg,sg)
  RooRealVar mg("mg", "mg", 0);
  //  RooRealVar sg("sg", "sg", 1.094e-02, 0, 0.003);
  RooRealVar sg("sg", "sg", 1.094e-02, 0, 0.005);
  sg.setConstant( kFALSE );
  RooGaussian gauss("gauss", "gauss", Amp, mg, sg);

  //--------------------------------------------------
  // C o n s t r u c t   c o n v o l u t i o n   p d f
  // -------------------------------------------------

  // Construct landau (x) gauss
  RooFFTConvPdf lxg("lxg", "landau (X) gauss", Amp, landau, gauss) ;
  //Extended variable
  RooRealVar* Ns = new RooRealVar( "Ns", "N_{s}", 8000, "events");
  Ns->setConstant(kFALSE);

  //------------------------------------
  //C r e a t e   E x t e n d e d  p.d.f
  //------------------------------------
  TString ex_pdf_name          = "lxg_ext";
  RooAddPdf* ex_lxg = new RooAddPdf( ex_pdf_name, "extLxG", RooArgList(lxg), RooArgList(*Ns) );
  //RooAddPdf* ex_lxg = new RooAddPdf( ex_pdf_name, "extLxG", RooArgList(landau), RooArgList(*Ns) );

  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("amp", 1);
  fChain->SetBranchStatus("x_dut", 1);
  fChain->SetBranchStatus("y_dut", 1);
  if (fChain == 0) return std::pair<float,float>(-999,0);
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  cout << "Running MPV_vs_Position Analysis\n";
  cout << "Total Events: " << nentries << "\n";
  TH1F* h_mpv = new TH1F("h_mpv", "h_mpv", 100, 0, 0.5);
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (ientry % 10000 == 0) cout << "Processing Event " << ientry << "\n";
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if ( amp[channel] >= AmpLowCut && amp[channel] <= AmpHighCut && amp[0] > photek_low && amp[0] < photek_high )
	{
	  if ( dut == 1 )
	    {
	      if ( (coor == "x" || coor == "X") && x_dut[0] >= coorLow && x_dut[0] < (coorLow + step) && y_dut[0] > other_corr_low && y_dut[0] < other_corr_high )
		{
		  h_mpv->Fill(amp[channel]);
		  Amp.setVal( amp[channel] );
		  data.add(RooArgSet(Amp));
		}
	      if ( (coor == "y" || coor == "Y") && y_dut[0] >= coorLow && y_dut[0] < (coorLow + step) && x_dut[0] > other_corr_low && x_dut[0] < other_corr_high )
		{
		  h_mpv->Fill(amp[channel]);
		  Amp.setVal( amp[channel] );
		  data.add(RooArgSet(Amp));
		}
	    }
	  else if ( dut == 2 )
	    {
	      if ( (coor == "x" || coor == "X") && x_dut[1] >= coorLow && x_dut[1] < (coorLow + step) && y_dut[1] > other_corr_low && y_dut[1] < other_corr_high )
		{
		  h_mpv->Fill(amp[channel]);
		  Amp.setVal( amp[channel] );
		  data.add(RooArgSet(Amp));
		}
	      if ( (coor == "y" || coor == "Y") && y_dut[1] >= coorLow && y_dut[1] < (coorLow + step) && x_dut[1] > other_corr_low && x_dut[1] < other_corr_high )
		{
		  h_mpv->Fill(amp[channel]);
		  Amp.setVal( amp[channel] );
		  data.add(RooArgSet(Amp));
		}
	    }

	}
    }

  //Restoring all branches
  fChain->SetBranchStatus("*", 1);

  if ( data.numEntries() < 10 )
    {
      std::cout << "======================" << std::endl;
      std::cout << "============nofit==========" << std::endl;
      std::cout << "======================" << std::endl;
     return std::pair<float,float>(0,999);
    }
  // ----------------------------------------------------------------------
  // f i t   a n d   p l o t   c o n v o l u t e d   p d f
  // ----------------------------------------------------------------------
  std::cout << "======================" << std::endl;
  std::cout << "============" << data.numEntries() << "==========" << std::endl;
  std::cout << "======================" << std::endl;
  Ns->setVal( data.numEntries() );
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  // Fit gxlx to data
  ex_lxg->fitTo(data, RooFit::Strategy(0), RooFit::Extended( kTRUE ), RooFit::Range("fitRange") );

  RooFitResult* sres = ex_lxg->fitTo(data, RooFit::Strategy(2), RooFit::Extended( kTRUE ), RooFit::Save( kTRUE ), RooFit::Range("fitRange") );

  /*
  RooPlot* frame = amp.frame();
  data.plotOn( frame );

  ex_lxg->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("Full"), RooFit::NormRange("Full") );
  ws->import( amp );
  ws->import( data );
  frame->SetName("MY_frame" );
  ws->import( *frame );
  */
  std::pair<float,float> result;
  result.first = ml.getVal();
  result.second = ml.getError();

   std::string myCoor;
  if ( coor == "X" || coor == "x" ) myCoor = "X";
  if ( coor == "Y" || coor == "y" ) myCoor = "Y";
  TString fname = Form("mpv_Channel%d_step%.2f_%s.root", channel,coorLow + step, myCoor.c_str());
  TFile* fout = new TFile(fname, "recreate");
  h_mpv->Write();
  RooWorkspace* ws = new RooWorkspace( "ws", "" );
  sres->SetName( "sres" );
  ws->import( *sres );
  RooPlot* frame = Amp.frame();
  data.plotOn( frame );

  ex_lxg->plotOn( frame, RooFit::LineColor( kBlue ), RooFit::Range("Full"), RooFit::NormRange("Full") );
  ws->import( Amp );
  ws->import( data );
  frame->SetName("MY_frame" );
  ws->import( *frame );
  ws->Write("myws");
  frame->Write();
  fout->Close();

  /*
  //Fitting
  TF1* landau = new TF1( "landau", "landau", AmpLowCut, AmpHighCut );
  h_mpv->Fit("landau","Q","", AmpLowCut, AmpHighCut);
  std::pair<float,float> result;
  result.first = landau->GetParameter(1);
  result.second = landau->GetParError(1);
  //Creating output file
  //Creating output file
  std::string myCoor;
  if ( coor == "X" || coor == "x" ) myCoor = "X";
  if ( coor == "Y" || coor == "y" ) myCoor = "Y";

  TString fname = Form("mpv_Channel%d_step%.2f_%s.root", channel,coorLow + step, myCoor.c_str());
  TFile* fout = new TFile(fname, "recreate");
  h_mpv->Write();
  fout->Close();
  */

  RooAbsReal* dldx = lxg.derivative(Amp) ;
  Double_t xpeak = 0.0;
  double scanmin = 0.0;
  double scanmax = 0.1;
  Bool_t ok = RooBrentRootFinder(RooRealBinding(*dldx,Amp)).findRoot(xpeak,scanmin,scanmax,0.) ;
  cout << "Max = " << xpeak << "\n";

  return result;
};

std::pair<float,float> pulse::DeltaT_vs_Position( int dut, TString coor, const int channel, const int timestampOption, const float coorLow, const float step,
						  const float AmpLowCut, const float AmpHighCut,
						  float other_corr_low, float other_corr_high, bool _isMean,
						  float photek_low, float photek_high)
{
  if ( channel < 0 ) return std::pair<float,float>(-999,0);
  if ( dut <= 0 || dut > 2 )
    {
      std::cerr << "[ERROR]: please provide a valid dut = <1,2>" << std::endl;
      return std::pair<float,float>(-999,0);
    }

  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("amp", 1);
  fChain->SetBranchStatus("gaus_mean", 1);
  fChain->SetBranchStatus("linearTime0", 1);
  fChain->SetBranchStatus("linearTime15", 1);
  fChain->SetBranchStatus("linearTime30", 1);
  fChain->SetBranchStatus("LP2_30", 1);
  fChain->SetBranchStatus("linearTime60", 1);
  fChain->SetBranchStatus("x_dut", 1);
  fChain->SetBranchStatus("y_dut", 1);
  if (fChain == 0) return std::pair<float,float>(-999,0);
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  cout << "Running Delta T_vs_Position Analysis\n";
  cout << "Total Events: " << nentries << "\n";
  TH1F* h_deltaT = new TH1F("h_delta_T", "h_delta_T", 1000, -10, 10);
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if (ientry % 10000 == 0) cout << "Processing Event " << ientry << "\n";
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      //timestamp uses algorithm selected by the timestampOption parameter
      double timestamp = t0CFD_20[channel];
      if (timestampOption == 1) timestamp = LP2_30[channel];

      double timeReference = t0CFD_20[0];
      if (channel >= 9) timeReference = t0CFD_20[9];

      if ( amp[channel] >= AmpLowCut && amp[channel] <= AmpHighCut && amp[0] > photek_low && amp[0] < photek_high )
	{
	  if ( dut == 1 )
	    {
	      if ( (coor == "x" || coor == "X") && x_dut[0] >= coorLow && x_dut[0] < (coorLow + step) && y_dut[0] > other_corr_low && y_dut[0] < other_corr_high ) h_deltaT->Fill(timestamp-timeReference);
	      if ( (coor == "y" || coor == "Y") && y_dut[0] >= coorLow && y_dut[0] < (coorLow + step) && x_dut[0] > other_corr_low && x_dut[0] < other_corr_high ) h_deltaT->Fill(timestamp-timeReference);
	    }
	  else if ( dut == 2 )
	    {
	      if ( (coor == "x" || coor == "X") && x_dut[1] >= coorLow && x_dut[1] < (coorLow + step) && y_dut[1] > other_corr_low && y_dut[1] < other_corr_high ) h_deltaT->Fill(timestamp-timeReference);
	      if ( (coor == "y" || coor == "Y") && y_dut[1] >= coorLow && y_dut[1] < (coorLow + step) && x_dut[1] > other_corr_low && x_dut[1] < other_corr_high ) h_deltaT->Fill(timestamp-timeReference);
	    }
	}
    }

  if ( h_deltaT->GetEntries() < 10 ) return std::pair<float,float>(-999,0);
  double mean = h_deltaT->GetMean();
  double rms = h_deltaT->GetRMS();
  //Restoring all branches
  fChain->SetBranchStatus("*", 1);
  //Fitting
  TF1* gaus = new TF1( "gaus", "gaus", mean -2.*rms, mean +2.*rms );
  h_deltaT->Fit("gaus","Q","", mean -2.*rms, mean +2.*rms);
  std::pair<float,float> result;
  if ( _isMean )
    {
      result.first  = gaus->GetParameter(1);
      result.second = gaus->GetParError(1);
    }
  else
    {
      result.first  = gaus->GetParameter(2);
      result.second = gaus->GetParError(2);
    }
  //Creating output file
  std::string myCoor;
  if ( coor == "X" || coor == "x" ) myCoor = "X";
  if ( coor == "Y" || coor == "y" ) myCoor = "Y";
  TString fname;
  if ( _isMean ) fname  = Form("gaus_mean_Channel%d_step%.2f_%s.root", channel,coorLow + step, myCoor.c_str());
  else fname  = Form("gaus_sigma_Channel%d_step%.2f_%s.root", channel,coorLow + step, myCoor.c_str());
  TFile* fout = new TFile(fname, "recreate");
  h_deltaT->Write();
  fout->Close();
  return result;
};

void pulse::PlotAll_CFD_DeltaTs(unsigned int channelNumber, unsigned int channelNumberReference)
{
  fChain->SetBranchStatus("*", 0);
  fChain->SetBranchStatus("InterpolatedAmp", 1);
  fChain->SetBranchStatus("t0_10",1);
  fChain->SetBranchStatus("t0_15",1);
  fChain->SetBranchStatus("t0_20",1);
  fChain->SetBranchStatus("t0_25",1);
  fChain->SetBranchStatus("t0_35",1);
  fChain->SetBranchStatus("t0_40",1);
  fChain->SetBranchStatus("t0_45",1);
  fChain->SetBranchStatus("t0_50",1);
  fChain->SetBranchStatus("t0_75",1);
  fChain->SetBranchStatus("t0_100",1);
  fChain->SetBranchStatus("t0CFD_5",1);
  fChain->SetBranchStatus("t0CFD_10",1);
  fChain->SetBranchStatus("t0CFD_15",1);
  fChain->SetBranchStatus("t0CFD_20",1);
  fChain->SetBranchStatus("t0CFD_25",1);
  fChain->SetBranchStatus("t0CFD_30",1);
  fChain->SetBranchStatus("t0CFD_35",1);
  fChain->SetBranchStatus("t0CFD_40",1);
  fChain->SetBranchStatus("t0CFD_45",1);
  fChain->SetBranchStatus("t0CFD_50",1);
  fChain->SetBranchStatus("t0CFD_60",1);
  fChain->SetBranchStatus("t0CFD_70",1);
  fChain->SetBranchStatus("t0CFD_80",1);

};
