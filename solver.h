#pragma once

#include "parser.h"

#include <ostream>
#include <cmath>

// Abstract class for a solver object
class Solver {
  public:
    // This could be expanded as other approaches are implemented
    enum class Type {BFS};

    struct Solution {
      // Crossing times for each bridge
      std::vector<float> bridgeCrossingTimes;

      // Total time for crossing all bridges
      float totalCrossingTime = 0.0f;

      friend std::ostream& operator<< (std::ostream& stream, const Solution& sol) {
        stream << "{ ";
        for (const auto &val : sol.bridgeCrossingTimes) {
          stream << val << " ";
        }
        stream << "}, " << sol.totalCrossingTime;
        return stream;
      }

    };

    virtual ~Solver() {}

    // Solves the problem and returns solution data
    //
    // @param hikers Parsed hiker data
    // @param bridges Parsed bridge data
    // @return The solution data
    virtual Solution solve(
        const Parser::HikerList &hikers,
        const Parser::BridgeList &bridges) = 0;


    // Factory method for creating parser objects
    static std::unique_ptr<Solver> create(Type t);
};

static bool operator==(const Solver::Solution& s1, const Solver::Solution& s2) {
  if (s1.bridgeCrossingTimes.size() != s2.bridgeCrossingTimes.size()) {
    return false;
  }

  if (fabs(s1.totalCrossingTime - s2.totalCrossingTime) > 0.001) {
    return false;
  }

  for (int i = 0; i < s1.bridgeCrossingTimes.size(); ++i) {
    if (fabs(s1.bridgeCrossingTimes[i] - s2.bridgeCrossingTimes[i]) > 0.001) {
      return false;
    }
  }

  return true;
}
