# anatreeloop

## To build and run on OSX 

The easy way to get going is to install ROOT6 via [Homebrew](http://brew.sh/) using the following steps:

```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew install homebrew/science/root6
git clone git@github.com:bcarls/anatreeloop.git
cd anatreeloop
source setup_homebrew.sh
mkdir build
cd build
cmake ..
make
```

To make changes subsequently:

```bash
cd build
make
```

To run the code using the AnaTreeLoopData module, do the following using python:

```bash
python scripts/run_AnaTreeLoopData.py -s anatreefile.root
```

When starting with a fresh login, setup everything with this:

```bash
source setup_homebrew.sh
```

## To build and run on the gpvm nodes







