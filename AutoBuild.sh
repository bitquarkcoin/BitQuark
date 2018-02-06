# Download and Install the Latest Updates for the OS
sudo apt-get update && sudo apt-get upgrade -y

# Install essential packages
sudo apt-get -y install \
gcc g++ autoconf automake make git zip unzip \
qt4-qmake libqt4-dev build-essential libboost-dev libboost-system-dev libboost-filesystem-dev \
libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libminiupnpc-dev libprotobuf-dev \
protobuf-compiler libqrencode-dev apache2 apt-cacher-ng python-vm-builder qemu-kvm ruby qemu-utils curl \
\

# Get latest BitQuark source
git clone https://github.com/bitquarkcoin/BitQuark-0.8.3r20.git BTQ-r20
cd BTQ-r20

# Install libpng (Used for PHP GD Library Extension)
wget -O- http://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.10/libpng-1.6.10.tar.gz | tar -zxf -
cd libpng-1.6.10
./configure && make && sudo make install
cd ..

# Install BDB4.8, here we create a directory within the bitquark directory
BITQUARK_ROOT=$(pwd)
BDB_PREFIX="${BITQUARK_ROOT}/db4"
mkdir -p $BDB_PREFIX
wget -O- http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz | tar -xzvf -
#tar -xzvf db-4.8.30.NC.tar.gz
cd db-4.8.30.NC/build_unix/
#  Note: Do a static build so that it can be embedded into the executable, instead of having to find a .so at runtime
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX && make install
cd ${BITQUARK_ROOT}
rm -f -r db-4.8.30.NC

# Now building bitquarkd
cd src/leveldb
chmod +x build_detect_platform
cd ..
make -f makefile.unix LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/"

# Now building bitquark-qt
cd ..
qmake "USE_QRCODE=1" "USE_UPNP=1" "USE_IPV6=1" bitquark-qt.pro LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/" && make
