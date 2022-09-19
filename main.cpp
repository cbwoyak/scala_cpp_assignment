#include "parser.h"
#include "solver.h"

#include <iomanip>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char **argv) {

  // Make sure the input file is specified
  if (argc != 2) {
    cerr << "No input file specified." << endl;
    cerr << " Usage: ScalaCppAssignment <filename>" << endl;
    return -1;
  }

  std::string filename(argv[1]);
  std::setprecision(3);

  // parse the file to get the input data
  auto [hikers, bridges] = Parser::create(Parser::Type::TEXT)->parse(filename);
  Solver::Solution sln = Solver::create(Solver::Type::BFS)->solve(hikers, bridges);

  std::setprecision(3);
  for (int i = 0; i < sln.bridgeCrossingTimes.size(); ++i) {
    cout << "Minimum time for crossing bridge (" 
         << i << "): " << sln.bridgeCrossingTimes.at(i) << endl;
  }

  cout << "Total time: " << sln.totalCrossingTime << endl;

  return 0;
}
