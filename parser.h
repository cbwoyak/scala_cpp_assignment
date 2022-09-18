#pragma once

#include <tuple>
#include <vector>

// Abstract class for a parser object
class Parser {

  public:

    // We currently support three types of parsers:
    //  TEST -  Will generate hard-coded data to be used as POC.
    //  TEXT -  Parses a text file with the hiker and bridge data.
    //  YAML -  Parses a yaml file with the hiker and bridge data.
    //
    //  We do not know the expected yaml format, and parsing YAML will
    //  be difficult without the help of third party libraries. We settled on
    //  using flat text files for more involved testing.
    enum class Type { TEST, TEXT, YAML };

    // Public types
    using Hiker = float;
    using HikerList = std::vector<Hiker>;

    struct Bridge {
      // The length of the bridge
      float length = 0.0f;

      // The list of additional hikers encountered (may be empty)
      HikerList hikers;
    };

    // List of bridges (order matters)
    using BridgeList = std::vector<Bridge>;

    // Class destructor
    virtual ~Parser() {}

    // parses the specified file and returns the parsed data.
    virtual std::tuple<HikerList, BridgeList> parse(const std::string &path) = 0;

    // Factory method for creating parser objects
    static std::unique_ptr<Parser> create(Type t);

};
