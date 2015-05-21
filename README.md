kqtquickcharts
==============

Beautiful and interactive charts for Qt Quick 1.0

## Installation

### Prerequesites

**kqtquicharts** depends on the following libaries:

 * Qt >= 5.2
 * CMake >= 2.8.12
 * CMake Extra Modules >= 1.1
 
### Building

Once the required libaries are installed **kqtquickcharts** can be built with:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

To be usable the components have to be installed:

    # make install

## Try it out

There are a few example projects in the `demo` folder. They are directly
runable in **qmlviewer**. Make sure to pass the required import folders
to it:

    $ cd demo/minimal
    $ qml -I /usr/lib64/qt5/qml main.qml

