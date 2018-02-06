# Download and Install the Latest Updates for the OS
sudo apt-get update && sudo apt-get upgrade -y

# Install essential packages
sudo apt-get -y install \
gcc g++ autoconf automake make git zip unzip \
qt4-qmake libqt4-dev build-essential libboost-dev libboost-system-dev libboost-filesystem-dev \
libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libminiupnpc-dev libprotobuf-dev \
protobuf-compiler libqrencode-dev \
\

# Get latest BitQuark source
git clone https://github.com/bitquarkcoin/BitQuark-0.8.3r19.git BTQ-r19
cd BTQ-r19

# Install libpng (Used for PHP GD Library Extension)
wget -O- http://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.10/libpng-1.6.10.tar.gz | tar -zxf -
cd libpng-1.6.10
./configure && make && sudo make install
cd ..

# Now building bitquarkd
cd src/leveldb
chmod +x build_detect_platform
cd ..
make -f makefile.unix

# Now building bitquark-qt
cd ..
qmake "USE_QRCODE=1" "USE_UPNP=1" "USE_IPV6=1" bitquark-qt.pro
make
