#include "parser.h"

#include <deque>
#include <fstream>
#include <memory>
#include <sstream>

// Parses a yaml file. Not currently supported as the exact YAML format is
class YamlParser : public Parser {
  public:
    YamlParser() = default;

    virtual ~YamlParser() {}

    [[deprecated("YamlParser::parse not yet implemented")]]
    virtual std::tuple<HikerList, BridgeList> parse(const std::string &path) override {
      return { {}, {} };
    }

};

// Returns a set of hard-coded data for POC.
class TestParser : public Parser {
  public:
    TestParser() = default;

    virtual ~TestParser() {}

    virtual std::tuple<HikerList, BridgeList> parse(const std::string &path) override {
      return { {100, 50, 20, 10 },
        //{ { 100.0f, {} } } };
        { { 100.0f, {} }, {250, {2.5} }, {150, {25, 15}}}};
    }
};

// Parses a flag text file to facilitate faster prototyping and testing.
//
// Expects a file of the format:
// H 100
// H 50
// H 20
// H 10
// B 100
// B 250 2.5
// B 150 25 15
//
// Each line shall be a distinct record labelled 'H' (hiker) or 'B' (bridge)
//
// When 'H' is specified, the following number is the hiker's speed (ft/min).
// When 'B' is specified, the first number is the length of the bridge. Any
// subsequent numbers (there may be zero) represent the speeds of additional
// hikers.
class TextParser : public Parser {
  public:
    TextParser() = default;

    virtual ~TextParser() {}

    virtual std::tuple<HikerList, BridgeList> parse(const std::string &path) override {
      HikerList hikers;
      BridgeList bridges;

      std::ifstream f;
      f.open(path);
      if (f.is_open()) {
        std::string line;
        while(std::getline(f, line)) {
          if (line.size() > 0) {
            if (line[0] == 'H') {
              processHikerLine(hikers, line);
            } else if (line[0] == 'B') {
              processBridgeLine(bridges, line);
            }
          }
        }
      }
      return {hikers, bridges};
    }

  private:

    // Splits the specified text into individual space-separated tokens
    //
    // @param text The text to process
    // @return List of parsed tokens
    std::deque<std::string> getTokens(const std::string &text) {
      std::deque<std::string> tokens;
      std::istringstream ss(text.c_str());
      std::string token;
      while(getline(ss, token, ' ')) {
        tokens.push_back(token);
      }

      // Note: NRVO is not guaranteed in c++17, so would need to investigate
      // further whether this would incur a copy based on the target compiler.
      return tokens;
    }

    // Parses the specified text and appends the data to the hiker list
    //
    // @pre text is a non-empty space-separated string that begins with 'H'
    //
    // @param hikers The list of hikers to append to
    // @param text The text to parse for new hiker data
    void processHikerLine(Parser::HikerList &hikers, const std::string &text) {
      auto tokens = getTokens(text);
      assert(tokens.size() > 0 && tokens.front() == "H");

      tokens.pop_front(); // We don't care about the 'H' token at this point
      if (tokens.size() > 0) {
        // store the speed of the new hiker
        hikers.push_back(std::stof(tokens.at(0)));
      }
    }

    // Parses the specified text and appends the data to the bridge list
    //
    // @pre text is a non-empty space-separated string that begins with 'B'
    //
    // @param bridges The list of bridges to append to
    // @param text The text to parse for new bridge data
    void processBridgeLine(Parser::BridgeList &bridges, const std::string &text) {
      auto tokens = getTokens(text);
      assert(tokens.size() > 0 && tokens.front() == "B");

      Parser::Bridge b;
      tokens.pop_front(); // We don't care about the 'B' token at this point
      if (tokens.size() > 0) {
        // store the length of the bridge
        b.length = std::stof(tokens.at(0));
        tokens.pop_front();
      }

      while(tokens.size() > 0) {
        // if there are additional hikers here, store their speeds
        b.hikers.push_back(std::stof(tokens.at(0)));
        tokens.pop_front();
      }

      bridges.push_back(b);
    }
};

std::unique_ptr<Parser> Parser::create(Parser::Type t) {
  switch (t) {
    case Parser::Type::TEST:
      return std::make_unique<TestParser>();
    case Parser::Type::TEXT:
      return std::make_unique<TextParser>();
    case Parser::Type::YAML:
      return std::make_unique<YamlParser>();
  }
}
