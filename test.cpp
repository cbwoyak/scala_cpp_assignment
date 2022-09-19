#include "parser.h"
#include "solver.h"

#include <iostream>
using std::cerr;
using std::endl;

// Bridge test data. Each row corresponds to a test case
const Parser::BridgeList BRIDGE_TEST_DATA [] = {
  {{100.f, {}}}, // single bridge, 100ft long with no additional hikers
  {{100.f, {}}, {200.f, {}}}, // two bridges, 100ft and 200ft, no other hikers
  {{100.f, {}}, {200.f, {}}, {15.f, {}}},
  {{100.f, {}}},
  {{100.f, {}}},
  {{100.f, {}}, {200.f, {}}},
  {{100.f, {}}, {200.f, {40.f}}}, // two bridges, 100ft and 200ft with hiker 40ft/min
  {{100.f, {}}, {200.f, {40.f}}, {150.f, {}}},
  {{100.f, {}}, {200.f, {5.f}}, {150.f, {}}}
};

// Hiker test data. Each row corresponds to a test case
const Parser::HikerList HIKER_TEST_DATA [] = {
  {5.f}, // single hiker 5ft/min
  {5.f},
  {5.f},
  {10.f},
  {5.f, 10.f}, // two hikers, 5ft/min and 10ft/min
  {5.f, 10.f},
  {5.f, 10.f},
  {10.f},
  {10.f}
};

// Expected results test data. Each row corresponds to a test case
const Solver::Solution RESULTS_TEST_DATA [] = {
  { {20.f}, 20.f},
  { {20.f, 40.f}, 60.f},
  { {20.f, 40.f, 3.f}, 63.f},
  { {10.f}, 10.f},
  { {20.f}, 20.f},
  { {20.f, 40.f}, 60.f},
  { {20.f, 65.f}, 85.f},
  { {10.f, 20.f, 15.f}, 45.f},
  { {10.f, 40.f, 15.f}, 65.f}
};


// Tests the Bfs solver against the available test data
//
// @return 0 If all tests passed, else 1
int testBfsSolver() {
  auto solver = Solver::create(Solver::Type::BFS);
  for (int i = 0; i < std::size(RESULTS_TEST_DATA); ++i) {
    const auto result = solver->solve(HIKER_TEST_DATA[i], BRIDGE_TEST_DATA[i]);
    if (result == RESULTS_TEST_DATA[i]) {
      // no problem
    } else {
      // Result did not match expected, test failure
      cerr << "Test Failure: " << i << "\n"
           << " ACTUAL:       " << result << "\n"
           << " EXPECTED:     " << RESULTS_TEST_DATA[i] << endl;
      return 1;
    }
  }

  return 0;
}


// Test driver program
int main(int argc, char **argv) {
  assert(std::size(BRIDGE_TEST_DATA) == std::size(HIKER_TEST_DATA));
  assert(std::size(BRIDGE_TEST_DATA) == std::size(RESULTS_TEST_DATA));

  return testBfsSolver();
}
