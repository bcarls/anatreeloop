# AnaTreeLoop

This is a simple set of macros for looking at AnalysisTree files. It is currently configured to use ROOT 6 and relies on CMake for building. Compilation is not necessary though. Details on avoiding it appear below. 

## To build on OSX 

The easy way to get going is to install ROOT6 via [Homebrew](http://brew.sh/) using the following steps:

```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install homebrew/science/root6
git clone https://github.com/bcarls/anatreeloop.git
cd anatreeloop
source setup_homebrew.sh
mkdir build
cd build
cmake ..
make
```


When starting with a fresh login, setup everything with this:

```bash
source setup_homebrew.sh
```

## To build on the gpvm nodes

```bash
git clone https://github.com/bcarls/anatreeloop.git
cd anatreeloop
source setup_gpvm.sh
mkdir build
cd build
cmake ..
make
```

When starting with a fresh login, setup everything with this:

```bash
source setup_gpvm.sh
```

## Subsequent compiling

If you make a change, recompile the library with this:

```bash
cd build
make
```

## Running the code

To run the code using the AnaTreeLoopData module and the compiled library, do the following using python:

```bash
python scripts/run_AnaTreeLoopData.py -s anatreefile.root
```

To run the code without compilation, the Python script needs slight modification, replacing this line in run_AnaTreeLoopData.py:

```python
ROOT.gSystem.Load("build/AnaTreeLoop/libAnaTreeLoop")
```

with these:

```python
ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeTracks.cxx");
ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeFlash.cxx");
ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeVertex.cxx");
ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeTruth.cxx");
ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeAlgs.cxx");
ROOT.gROOT.ProcessLine(".L AnaTreeLoop/AnaTreeLoopData.cxx");
```

I also have an example Python script that does not need compilation here:

```bash
scripts/run_AnaTreeLoopDataNoCompile.py
```










