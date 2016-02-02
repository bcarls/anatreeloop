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
