# MessyEvents (messy-events)

An example implementation of a multithreaded events system for projects with messy data flow.

--------------------------------------------------------------------------------

This is a basic example of how to handle a generic case of "I'm stuck with someone's undocumented multithreaded code and I have to make it work with whatever I'm doing asap." Since pretty much everything can be serialized into std::string we use strings as keys for dividing messages into categories and since std::any can store pretty much anything copy constructible we use it to store the actual message/context. This has an advantage over the regular templating approach in that it's hilariously simple and has no major downsides.

# How To Build

Project is set up for CMake, Doxygen and Boost Unit Testing (default install location). See unit tests for example usage.

```bash

cd build
cmake ..
make
./test_boost

```

