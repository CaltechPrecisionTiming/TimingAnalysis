//C++ includes
#include <iostream>
//ROOT FILES
#include <TFile.h>
#include <TTree.h>
//LOCAL FILES
#include <pulse.hh>

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
  if ( inputRootFile == "" )
    {
      std::cerr << "[ERROR]: Please provide a valid ROOT file to run on!! Please use --inputRootFile=<your_file_name>\n";
      return -1;
    }

  TFile* fin = new TFile(inputRootFile.c_str(), "READ");
  TTree* myTree = (TTree*)fin->Get("pulse");
  pulse* myPulse = new pulse( myTree );

  const int kGausTimestampOption = 0;
  const int kLinearTime45TimestampOption = 1;

  
  // //------------------------
  // //Run 1208 CH1(pre-rad), CH2(W6 1.5E15), CH3(W6 8E14)
  // //------------------------
  // //Efficiency
  myPulse->MakeEfficiencyVsXY(1, 200, 20, 17.0, 18.0, 17.7, 18.7, 50, 110);
  
  // //MPV
  // myPulse->CreateMPV_vs_PositionHisto(1, 3, 250, 0.02, 0.1, 11100., 13500., 20500, 23000.);
  //myPulse->CreateMPV_vs_PositionHisto(1, 4, 250, 0.02, 0.1, 11100., 13500., 23500, 26000.);
  //myPulse->CreateMPV_vs_PositionHisto(1, 5, 250, 0.02, 0.1, 13800., 16500., 23500, 26000.);
  //myPulse->CreateMPV_vs_PositionHisto(1, 6, 250, 0.02, 0.1, 13800., 16500., 20500, 23000.);

 

  

  return 0;
}
