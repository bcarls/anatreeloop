source /grid/fermiapp/products/uboone/setup_uboone.sh
setup root v6_04_02 -q e7:prof
setup cmake v3_3_2
export ROOTINCLUDE=$ROOTSYS"/include/"
export ROOTLIB=$ROOTSYS"/lib/"
export ROOTCMAKE=$ROOTSYS"/etc/cmake"
export CC=`which gcc`
export CXX=`which g++`
