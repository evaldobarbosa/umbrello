Umbrello (fork/download from official site)
==

###To install qt-sdk (ubuntu)

sudo apt-get install qt-sdk (complete package)

or

sudo apt-get install qt4-qmake

and

if KDEDirs are not found, run the command

sudo apt-get install kdelibs5-dev

### Compile

mkdir build
cd build
touch compile.sh
chmod +x compile.sh

put the content on compile.sh

``
#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=$HOME/umbrello -DCMAKE_BUILD_TYPE=Debug ../

make
make install

export KDEDIRS=$HOME/umbrello:$KDEDIRS
kbuildsycoca4
``

### Run
./compile.sh