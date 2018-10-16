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
  if ( inputRootFile != "" ) myChain->Add(inputRootFile.c_str());
  else {
    cout << "Reading input files from the list : " << inputListFile << "\n";
    ifstream inListFile;
    inListFile.open (inputListFile.c_str(), ios::in);
    if (inListFile.is_open()) {
      string tempFilename;
      char temp;
      while (! inListFile.eof ()) {
  	//getline (inListFile, temp);
  	inListFile >> tempFilename;
  	cout << "Adding file: " << tempFilename << "\n";
  	myChain->Add(tempFilename.c_str());
      }
    } else {
      std::cerr << "[ERROR]: List file provided " << inputListFile << " does not exist.\n";
      return -1;
    }
  }

  //myChain->Add("dataMarch/RECO/v1/RawDataSaver0NetScope_Run1251_0_Raw.root");
  //myChain->Add("data/RECO/v2/DataCMSVMETiming_Run1222.root");
  // TTree *myTree = (TTree*)myChain->GetTree();
  // assert(myTree);
  pulse* myPulse = new pulse( myChain );

  const int kGausTimestampOption = 0;
  const int kLinearTime45TimestampOption = 1;


  // //------------------------
  // //Run 1208 CH1(pre-rad), CH2(W6 1.5E15), CH3(W6 8E14)
  // //------------------------
  // //Efficiency
  // myPulse->MakeEfficiencyVsXY(1, 200, 20, 17.4, 18.2, 17.9, 18.6, 50, 110);

  // //MPV
  // myPulse->CreateMPV_vs_PositionHisto(1, 3, 250, 0.02, 0.1, 11100., 13500., 20500, 23000.);
  //myPulse->CreateMPV_vs_PositionHisto(1, 4, 250, 0.02, 0.1, 11100., 13500., 23500, 26000.);
  //myPulse->CreateMPV_vs_PositionHisto(1, 5, 250, 0.02, 0.1, 13800., 16500., 23500, 26000.);
  //myPulse->CreateMPV_vs_PositionHisto(1, 6, 250, 0.02, 0.1, 13800., 16500., 20500, 23000.);

  //------------------------
  //Run 1251 CH3(Photek), CH2(W6 pre-rad)
  //------------------------
  int name_low = inputRootFile.find("ShapingTime");
  int name_high = inputRootFile.find("_ALL_converted.root");
  //std::cout << "NEW NAME: " << inputRootFile.substr(name_low,name_high-name_low) << std::endl;
  std::string prefix = inputRootFile.substr(name_low,name_high-name_low);
  myPulse->PlotAll_CFD_DeltaTs_SIM(0,15,80,prefix);





  return 0;
}
