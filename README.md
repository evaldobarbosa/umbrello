Umbrello (fork/download from official site)
==

####To install qt-sdk (ubuntu)
>> sudo apt-get install qt-sdk (complete package)

or

>> sudo apt-get install qt4-qmake

and

####if KDEDirs is not found, run the command

>> sudo apt-get install kdelibs5-dev

####If your build is complete, run the command

>> export KDEDIRS=$HOME/umbrello:$KDEDIRS

>> kbuildsycoca4

####Export these paths

>> export KDEDIRS=$HOME/umbrello:$KDEDIRS

>> export PATH=$HOME/umbrello/bin:$PATH
