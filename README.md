[![Build Status](https://travis-ci.org/ihassin/cucumber-wire-c.svg?branch=master)](https://travis-ci.org/ihassin/cucumber-wire-c)

# What is this?

This is the start of a platform-independent implementation of the Cucumber Wire Protocol.
It's implemented in C to allow quick porting to different platforms. My goal is to have a single codebase for Linux (desktop, Raspberry Pi), ThreadX, Ardiuno, Mac and Windows.

# Cucumber Compatibility

The Wire will answer the Cucumber Gem's protocol as I have undertood it from code and the documentation.

# Platform Compatibility

* Mac OS X (Intel)
* iOS (Arm6/Arm7) - Thanks [Dan!](https://github.com/dingbat)

# XCode Compatibility

Open the wire.xcworkspace file to use XCode as your development platform. Thanks [Dan!](https://github.com/dingbat)

# Mileage

Currently:

* POSIX Thread compatibility
* Works in command-line mode for Intel
* Works on iOS as a server process
* Only one parameter per Feature line is supported. Obvioulsy, this will be improved.


# What's in the box?

'unity-master' is a clone of the C unit testing framework. I'll move it to be a reference in the future, but wanted an independent package to start working with.

'wire-c' contains implementations for the tests and the Wire Server.

'wire-features' contains a Cucumber to self-test the installation of needed modules.

There's a gem file to set up needed gems


# Code layout

wire-c/wire-server:

```
rake build  # Compiles and links the wire-server executable
rake clean  # Removes artefacts
rake run    # Runs the wire
```
Run it:

```
./bin/wire.out <port> <single> <logging>
```
* port = Port number to listen on. 3901, for example
* single = Quit after a single pass. Allows for better testing environment.
* logging = 1 to show console logging, 0 to supress

wire-c/tests:

```
rake build    # Compiles and links the test program
rake clean    # Removes artefacts
rake default  # Default task will build and run the tests
rake run      # Runs the test program
```

Please note that the tests code will link against the current library found in ../wire-server.

# Challenges

* Looking for a good, lightweight, JSON parser
* Getting the code to work with the ARM toolchain for Arduino and Raspberry Pi and other platforms.

# Collaborating

Come join the party, I am all alone here :(
Submit a PR, etc.

# License

None - feel free to use.
