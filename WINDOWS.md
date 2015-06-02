# Notes for building on windows

I am in the process of porting RethinkDB to Windows. These
notes may or may not help you reproduce the failing builds
that I have managed to run so far.

## Visual Studio

* Install Visual Studio 2015 RC

## boost

* downlaod boost 1.58.0 into `..\boost_1_58_0`
* in the boost directory, run

```
.\bootstrap.bat
.\b2 -j 24 runtime-link=static address-model=64
```

## gtest

* install cmake and python. add both to your PATH.
* in `external\gtest_1.7.0`, run

```
cmake -G"Visual Studio 14 Win64"
```

* Open `gtest.sln` in visual studio.
* Build the `gtest` project.

## Protobuf

The dependency on Protobuf will hopefully go away soon.

* Download protobuf into `..\protobuf-2.5.0`
* Open `vsprojects\protobuf.sln`
* Open Build -> Configuration Manager and add an x64 configuration based on Win32
* For each project in `libprotobuf` `libprotoc` and `protoc`:
  - Open Properties -> C/C++ -> All Options
  - Set Runtime Library to `/MTd`

## RethinkDB

* Open `RethinkDB.sln`
* Make sure you are in the Debug/x64 configuration
* Press F7 to build
* Press F5 to run
* Some unit tests should run.

## To do

* Compile with and fix all warnings
* Support mingw64
* Clean up the ifdefs, and use feature macros
* Command line build using msbuild
* Consider not using the pthread API on windows
* Backtraces on crash, with addr2line
* Clean up the arch hierachy
* Check for misnamed linux_ prefixess
* Thouroughly test clock time and ticks
* Test the timers
* sizeof int and sizeof long differences
* Generate web assets
* Generate protobuf
* Pass all unit tests
* death tests with exceptions seem to fail
* web assets literal size > 65535
* Check all RSI ATN TODO _MSC_VER and _WIN32 tags
* re-implement sockets.cc
* Handle ^C
* no more named VA_ARGS
* test blocker pool, maybe use windowswindows-specific pool
* make sure it still builds on linux
* keep up-to-date with next/raft/sunos
* build without /force:unresolved LDFLAG