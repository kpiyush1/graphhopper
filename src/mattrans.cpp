
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "mat.h"
#include "matrix.h"
using namespace std;


int transform(const char *file){
  cout << "Input file: " << file << "\n";

  MATFile *matFile = matOpen(file, "r");
  if(matFile == NULL){
    std::cout << "Error opening file: " << file << "\n";
    return 1;
  }

  mxArray *data;
  const char *name;
  data = matGetNextVariable(matFile, &name);
  if(data == NULL){
    cout << "File empty\n";
    return 1;
  }

  cout << "Data header name: " << name << "\n";

  mwSize nGraphs = (mwSize) mxGetNumberOfElements(data);

  cout << "Number of graphs: " << nGraphs << "\n";

  ofstream outputFile;
  outputFile.open("output/output.dat");
  if(!outputFile.is_open()){
    cout << "Could not open output file!\n";
    return 1;
  }

  const mxArray *am;
  const double *m;
  mxArray *row;
  for(int i=0; i<nGraphs; i++){
    mxArray *am = mxGetField(data, i, "am");
    mwSize nNodes = (mwSize) mxGetM(am);

    outputFile << nNodes << "\n";

    m = mxGetPr(am);
    for(int x=0; x<nNodes; x++){
      for(int y=0; y<nNodes; y++){
        double v = m[x + y * nNodes];
        if(v > 0){
          outputFile << x << "," << y << "," << v << "\n";
        }
      }
    }
  }
  outputFile.close();
  cout << "Data written!\n";
  return 0;
}

int main(int argc, char **argv){

  cout << "MAT-file translator for <GraphHopper>\n";
  int result = 0;
  if(argc > 1){
    result = transform(argv[1]);
  }else{
    cout << "Usage: mattrans <matfile>\n";
    result = 1;
  }

  return result;
}
