# anatreeloop

## To build on OSX 

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


When starting with a fresh login, setup everything with this:

```bash
source setup_homebrew.sh
```

## To build on the gpvm nodes

```bash
git clone git@github.com:bcarls/anatreeloop.git
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

### Running the code

To run the code using the AnaTreeLoopData module, do the following using python:

```bash
python scripts/run_AnaTreeLoopData.py -s anatreefile.root
```




