BitQuark 0.8.3.19
====================

Copyright (c) 2009-2015 Bitcoin Developers

Copyright (c) 2013-2015 Quarkcoin Developers

Copyright (c) 2014-2015 BitQuark Developers

Distributed under the MIT/X11 software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](http://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), UPnP software written by Thomas Bernard and
sphlib 3.0 by Thomas Pornin.

BitQuark Dev Team ([bitquarkcoin@gmail.com](mailto:bitquarkcoin@gmail.com))


Intro
---------------------
BitQuark is a free open source peer-to-peer electronic cash system that is
completely decentralized, without the need for a central server or trusted
parties.  Users hold the crypto keys to their own money and transact directly
with each other, with the help of a P2P network to check for double-spending.


Setup
---------------------
You need the Qt4 run-time libraries to run BitQuark-Qt. On Debian or Ubuntu:

`sudo apt-get -y install gcc g++ autoconf automake make git zip unzip qt4-qmake libqt4-dev build-essential libboost-dev libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev libdb++-dev libminiupnpc-dev libprotobuf-dev protobuf-compiler libqrencode-dev`

`cd BitQuark-0.8.3r19`

` wget -O- http://sourceforge.net/projects/libpng/files/libpng16/older-releases/1.6.10/libpng-1.6.10.tar.gz | tar -zxf -`

`cd libpng-1.6.10`

`./configure && make && sudo make install`

`cd ..`

`cd src/leveldb`

`chmod +x build_detect_platform`

`cd ..`

`make -f makefile.unix`

`cd ..`

` qmake "USE_QRCODE=1" "USE_UPNP=1" "USE_IPV6=1" bitquark-qt.pro`

`make`


Other Pages
---------------------
- [Unix Build Notes](build-unix.md)
- [OSX Build Notes](build-osx.md)
- [Windows Build Notes](build-msw.md)
- [Coding Guidelines](coding.md)
- [Release Process](release-process.md)
- [Release Notes](release-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Unit Tests](unit-tests.md)
- [Translation Process](translation_process.md)
