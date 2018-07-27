//C++ includes
#include <iostream>
//ROOT FILES
#include <TFile.h>
#include <TTree.h>
//LOCAL FILES
#include <pulse.hh>
#include <assert.h>
#include <fstream>

using namespace std;

std::string ParseCommandLine( int argc, char* argv[], std::string opt )
{
  for (int i = 1; i < argc; i++ )
    {
      std::string tmp( argv[i] );
      if ( tmp.find( opt ) != std::string::npos )
	{
	  if ( tmp.find( "=" )  != std::string::npos ) return tmp.substr( tmp.find_last_of("=") + 1 );
	  if ( tmp.find( "--" ) != std::string::npos ) return "yes";
	}
    }
  
  return "";
};


int main( int argc, char** argv)
{

  std::string inputRootFile = ParseCommandLine( argc, argv, "--inputRootFile" );
  std::string inputListFile = ParseCommandLine( argc, argv, "--inputListFile" );
  if ( inputRootFile == "" && inputListFile == "" )
    {
      std::cerr << "[ERROR]: Please provide a valid ROOT file or list file to run on!! Please use --inputRootFile=<your_file_name> or --inputListFile=<your_list_file_name>\n";
      return -1;
    }

  //  TFile* fin = new TFile(inputRootFile.c_str(), "READ");
  //TTree* myTree = (TTree*)fin->Get("pulse");

  TChain *myChain = new TChain("pulse");
  // if ( inputRootFile != "" ) myChain->Add(inputRootFile.c_str());
  // else {
  //   cout << "Reading input files from the list : " << inputListFile << "\n";
  //   ifstream inListFile;
  //   inListFile.open (inputListFile.c_str(), ios::in);
  //   if (inListFile.is_open()) {
  //     string tempFilename;
  //     char temp;
  //     while (! inListFile.eof ()) {
  // 	//getline (inListFile, temp);
  // 	inListFile >> tempFilename;
  // 	cout << "Adding file: " << tempFilename << "\n";
  // 	myChain->Add(tempFilename.c_str());
  //     }
  //   } else {
  //     std::cerr << "[ERROR]: List file provided " << inputListFile << " does not exist.\n";
  //     return -1;
  //   }
  // }
 
  
  // //---------------------------------------------
  // //March 2018 Run 1251 CH3(Photek), CH2(W6 pre-rad @ 330V)
  // //------------------------  ---------------------
  // myChain->Add("dataMarch/RECO/v1/RawDataSaver0NetScope_Run1251_0_Raw.root");

  // //---------------------------------------------
  // //March 2018 Run 1260 CH1(Photek), CH2(W6 1.5E15 @ 590V)
  // //------------------------  ---------------------
  // myChain->Add("dataMarch/RECO/v1/RawDataSaver0NetScope_Run1260_0_Raw.root");

  // //---------------------------------------------
  // //March 2018 Run 1262 CH1(Photek), CH2(W6 1.5E15 @ 560V)
  // //------------------------  ---------------------
  // // myChain->Add("dataMarch/RECO/v1/RawDataSaver0NetScope_Run1262_0_Raw.root");

  // // ---------------------------------------------
  // // March 2018 Run 1260+1262 CH1(Photek), CH3(W6 8E14 @ 520V)
  // // ------------------------  ---------------------
  // myChain->Add("dataMarch/RECO/v1/RawDataSaver0NetScope_Run1260+1262.root");



  pulse* myPulse = new pulse( myChain  );

  // //------------------------------------------------
  // //March 2018 Run 1251 CH3(Photek), CH2(W6 pre-rad @ 330V)
  // //------------------------------------------------
  // myPulse->PlotAll_CFD_DeltaTs(1,2, 50, 130, 100, 240);

  // //------------------------------------------------
  // //March 2018 Run 1260 CH1(Photek), CH2(W6 1.5E15 @ 590V)
  // //------------------------  ------------------------
  // myPulse->PlotAll_CFD_DeltaTs(1,0, 35, 150, 60, 160);

  // //------------------------------------------------
  // //March 2018 Run 1262 CH1(Photek), CH2(W6 1.5E15 @ 560V)
  // //------------------------  ------------------------
  // myPulse->PlotAll_CFD_DeltaTs(1,0, 30, 130, 60, 160);

  // //------------------------------------------------
  // //March 2018 Run 1262 CH1(Photek), CH2(W6 8E14 @ 520V)
  // //------------------------  ------------------------
  // myPulse->PlotAll_CFD_DeltaTs(2,0, 100, 240, 60, 160);
 
  return 0;
}
