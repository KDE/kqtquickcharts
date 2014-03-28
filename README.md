kqtquickcharts
==============

Beautiful and interactive charts for Qt Quick 1.0

## Installation

### Prerequesites

**kqtquicharts** depends on the following libaries:

 * KDElibs >= 4.10.0
 * Qt >= 4.8 (but not Qt 5.x)
 * CMake >= 2.8.9

### Building

Once the required libaries are installed **kqtquickcharts** can be built with:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make

To be usable the components have to be installed:

    # make install

### Runtime dependencies

At runtime, the following additional libaries have to be present:

 * KDE-runtime >= 4.10.0

## Try it out

There are a few example projects in the `demo` folder. They are directly
runable in **qmlviewer**. Make sure to pass the required import folders
to it:

    $ cd demo/minimal
    $ qmlviewer -I /usr/lib64/kde4/imports/ main.qml

Replace the last line on 32-bit systems with:

    $ qmlviewer -I /usr/lib/kde4/imports/ main.qml
