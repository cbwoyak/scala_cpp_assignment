#include "parser.h"

#include <numeric>
#include <algorithm>

#include <iomanip>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

// Calculates and returns the minimum time required for the hikers to cross the
// bridge.
//
// Given the constraints of the problem (only two hikers may cross at the same
// time and only one torch exists), the minimum amount of time requried for all
// hikers to cross is the sum of times for all but the fastest hiker, plus the
// time required for the fastest hiker to double back with the torch to guide
// each slower hiker.
//
// For example, given the following example:
// Hikers:  A (100 ft/min), B(50), C(20), D(10)
// Bridges: 1 (100 ft)
//
// The optimal solution is for hiker A to cross with each of the other hikers
// at their slower speed, then double back for the remainind hikers:
//
// Possible crossing sequence:
// A and B cross (2 minutes)
// A doubles back (1 minute)
// A and C cross (5 minutes)
// A doubles back (1 minute)
// A and D cross (10 minutes)
// Total crossing time: 19 minutes.
//
// Note that the order of the crossings does not matter (addition is
// commutative).
//
// This function calculates the minimum requried time to complete a crossing
// using the above approach.
//
// @pre hikers must be non-empty and sorted in descending order
// @pre length must be positive
//
// @param hikers The list of hikers looking to cross the bridge
// @param length The length of the bridge to cross
// @return The time (in minutes) for all hikers to cross the bridge
float getCrossingTime(Parser::HikerList &hikers, float length) {
  // enforce preconditions
  assert(hikers.size() > 0);
  assert(length > 0);
  assert(std::is_sorted(hikers.begin(), hikers.end(), std::greater<float>()));

  // handle simplest case of a single hiker
  if (hikers.size() == 1) {
    return length / hikers.at(0);
  }

  // The fastest hiker will guide slower hikers across the bridge, one at a
  // time. They must move at the pace of the slower hiker, and this must be
  // done for all other hikers to get everyone across the bridge. 
  float time = std::accumulate(hikers.begin()+1, hikers.end(), 0.0f, // O(n)
      [&length](const float &a, const float &b) {
        return a + length / b;
      });

  // Add the time required for the fastest hiker to double-back across the
  // bridge to fetch the remaining hikers. This is only required for 3 or
  // more hikers. Otherwise no doubling back is requried.
  if (hikers.size() > 2) {
    time += length / hikers.at(0) * (hikers.size() - 2); // O(1)
  }

  return time;
}

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "No input file specified." << endl;
    cerr << " Usage: ScalaCppAssignment <filename>" << endl;
    return -1;
  }

  std::string filename(argv[1]);
  std::setprecision(3);

  // parse the file to get the input data
  auto [hikers, bridges] = Parser::create(Parser::Type::TEXT)->parse(filename);

  // keep track of the total time required for all crossings
  float total_time = 0.0f;
  for (int i = 0; i < bridges.size(); ++i) {
    Parser::Bridge &b = bridges.at(i);

    // merge the initial hikers (who will cross all bridges) with new hikers
    // that will only cross this bridge. Ensure the hiker speeds are sorted in
    // descending order as required by getCrossingTime().
    Parser::HikerList allHikers(hikers.begin(), hikers.end());
    allHikers.insert(allHikers.end(), b.hikers.begin(), b.hikers.end());
    std::sort(allHikers.begin(), allHikers.end(), std::greater<float>());

    float time = getCrossingTime(allHikers, b.length);
    cout << "Time to cross bridge (" << i << "): " << time << endl;
    total_time += time;
  }
  cout << "Total time for all crossings: " << total_time << endl;
  return 0;
}
