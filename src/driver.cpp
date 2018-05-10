#include <string>
#include <iostream>
#include <vector>

#include "../include/Music.h"

using namespace GWRBRA001;

int main(int argc, char const *argv[])
{
  int samepleRate;
  int bitCount;
  int noChannels;
  std::string inputFileName1;
  std::string inputFileName2;
  std::string outputFileName = "out";

  MusicOperation musicOp = NONE;
  std::vector<float> operationValues;

  for(int i =0 ; i < argc; ++i)
  {
    std::string argument = argv[i];
    if(argument == "-r")
    {
      ++i;
      samepleRate = std::atoi(argv[i]);
    }
    else if(argument == "-b")
    {
      ++i;
      bitCount = std::atoi(argv[i]);
    }
    else if(argument == "-c")
    {
      ++i;
      noChannels = std::atoi(argv[i]);
    }
    else if(argument == "-o")
    {
      ++i;
      outputFileName = argv[i];
    }
    else if(argument == "-add")
    {
      if(musicOp == NONE)
      musicOp = ADD;
    }
    else if(argument == "-cut")
    {
      if(musicOp == NONE)
      {
        musicOp = CUT;
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 1
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 2
      }
    }
    else if(argument == "-radd")
    {
      if(musicOp == NONE)
      {
        musicOp = RANGEADD;
        //Clip 1
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 1
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 2
        //Clip 2
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 1
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 2
      }
    }
    else if(argument == "-cat")
    {
      if(musicOp == NONE)
      musicOp = CONCATENATE;
    }
    else if(argument == "-v")
    {
      if(musicOp == NONE)
      {
        musicOp = VOLUME;
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 1
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 2
      }
    }
    else if(argument == "-rev")
    {
      if(musicOp == NONE)
      musicOp = REVERSE;
    }
    else if(argument == "-rms")
    {
      if(musicOp == NONE)
      musicOp == RMS;
    }
    else if(argument == "-norm")
    {
      if(musicOp == NONE)
      {
        musicOp = NORMALIZE;
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 1
        ++i;
        operationValues.push_back(std::atof(argv[i])); //Range 2
      }
    }
    else if(argument == "-fadein")
    {
      if(musicOp == NONE)
      {
        musicOp = FADEIN;
        ++i;
        operationValues.push_back(std::atof(argv[i]));
      }
    }
    else if(argument == "-fadeout")
    {
      if(musicOp == NONE)
      {
        musicOp = FADEOUT;
        ++i;
        operationValues.push_back(std::atof(argv[i]));
      }

    }
    else
    {
      if(i == 0) continue;
      if(inputFileName1 == "") inputFileName1 = argv[i];
      else if(inputFileName2 == "") inputFileName2 = argv[i];
    }
  }
  std::cout << "***Music Details***" << '\n';
  std::cout << "Sample Rate:" << samepleRate << "\nSample Size: " << bitCount << '\n';
  if(noChannels == 1) std::cout << "Channel Type: MONO" << '\n';
  else if(noChannels == 2) std::cout << "Channel Type: STEREO" << '\n';
  std::cout << "***Operation Details***" << '\n';
  switch (musicOp)
  {
    case ADD:
      std::cout << "ADD" << '\n';
      break;
    case CUT:
      std::cout << "CUT" << '\n';
      std::cout << "Range: [" << operationValues[0] << ':' << operationValues[1] << ']' << '\n';
      break;
    case RANGEADD:
      std::cout << "RANGE ADD" << '\n';
      std::cout << "Range for clip 1: [" << operationValues[0] << ':' << operationValues[1] << ']' << '\n';
      std::cout << "Range for clip 2: [" << operationValues[2] << ':' << operationValues[3] << ']' << '\n';
      break;
    case CONCATENATE:
      std::cout << "CONCATENATE" << '\n';
      break;
    case VOLUME:
      std::cout << "VOLUME" << '\n';
      std::cout << "Left Volume: [" << operationValues[0] << "] <==> Right Volume: [" << operationValues[1] << ']' << '\n';
      break;
    case REVERSE:
      std::cout << "REVERSE" << '\n';
      break;
    case RMS:
      std::cout << "RMS" << '\n';
    case NORMALIZE:
      std::cout << "NORMALIZE" << '\n';
      std::cout << "Left RMS: [" << operationValues[0] << "] <==> Right RMS: [" << operationValues[1] << ']' << '\n';
      break;
    case FADEIN:
      std::cout << "FADEIN" << '\n';
      std::cout << "End: " << operationValues[0] << '\n';
      break;
    case FADEOUT:
      std::cout << "FADEOUT" << '\n';
      std::cout << "Start: " << operationValues[0] << '\n';
      break;
    case NONE:
      std::cout << "NO FUNCTION SPECIFIED!!!" << '\n';
      break;
  }
  if(inputFileName1 != "") std::cout << "File 1: " << inputFileName1 << '\n';
  if(inputFileName2 != "") std::cout << "File 2: " << inputFileName2 << '\n';
  std::cout << "Output File: " << outputFileName << '\n';
  return 0;
}
