# scala_cpp_assignment

## How to Build
This project can be built using cmake:
```
> git clone git@github.com:cbwoyak/scala_cpp_assignment.git
> cd scala_cpp_assignment
> mkdir build
> cd build
> cmake ..
...
> make
...
> ./ScalaExercise ../input.txt
Minimum time for crossing bridge (0): 19
Minimum time for crossing bridge (1): 150
Minimum time for crossing bridge (2): 47.5
Total time: 216.5
> ./ScalaExerciseTest
> echo $? # test program returns 0 if all tests passed
```

## Assumptions
Our solution assumes that additional hikers waiting for help only cross the
bridge they are found at. In other words, they cross only that bridge where they
were found and do not continue with the original "party" to the end. Should this
assumption prove incorrect, the method can be ammended so that found hikers
become permanent members of the initial party.

## Strategy
We implemented a single strategy for this problem which involved finding the
minimum crossing time for each bridge crossing in isolation (i.e. all hikers
must cross the current bridge before moving on to the next). This can be
considered a sort of "breadth-first" approach. We thought this approach would
simplify the problem of handling additional found hikers according to the
previously stated assumption.

The constraints of the problem specify that no more than two hikers may cross a
bridge at once, and only one torch exists. This means that in order for the
other hikers to cross, the torch must be brought back across the bridge to fetch
another hiker. Because this must be done or each additional hiker, it is best
for the fastest hiker to double-back with the torch.

Trivial cases include when only a single hiker or two hikers exist. In the first
case, the time to cross is simply the length of the bridge divided by the speed
of the hiker. In the case of two hikers, the time would be the length of the
bridge divided by the slowest hiker's pace. In all other cases, the fastest
hiker must double-back at least once to fetch the remaining hikers.

## Architecture
Our solution is split into two main components: Parser and Solver. Both of these
are abstractions of an input file parser, 
The solution that we implemented is relatively simple, and did not require any
excessive architecting([See Potential Improvements](#potential-improvements)).
However, because we were not given details about the expected input file format,
we decided to abstract the parser interface to support multiple file formats and
data sources.

The Parser class provides a very simple interface for specifying a file and
returning the parsed data requried to solve the problem given our algorithm.
Initially we created specializations for YAML parsing and hard-coded testing. To
facilitate better testing while prototypeing we also implemented a text file
interface which requires no third-party libraries.

The Solver class represents an algorithm that will return a solution set,
combining a list of individual bridge crossing times and an overall time for the
entire crossing. Again, the base class provides a very simple interface that can
be overridden by subclasses. In both cases, we use a factory method to allow
clients to choose a parser and solver algorithm at runtime.

## Testing
For testing, we created a separate test driver that checks the implementation
against small examples that are easy enough to calculate by hand. The test data
is hard-coded into the driver for simplicity. This decision was made for
convenience, and allowed us to quickly write test cases without requireing more
complicated test infrastructure.
