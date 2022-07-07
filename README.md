## QML Box2D plugin

The goal of the qml-box2d plugin is to expose the functionality of Box2D (C++)
as a QML plugin in order to make it easier to write physics based software in
QML.

This plugin is meant to be installed to your Qt/imports directory, or shipped
in a directory of which the parent is added as import path.

# Build Status
![Build Status](https://github.com/qml-box2d/qml-box2d/actions/workflows/compile.yml/badge.svg)

### Installing

    mkdir build
    cd build
    cmake ..
    make
    make install

Multiple CMake options exist:
* USE_QT6 (ON by default) to use Qt6 if it is installed. If set to OFF or Qt6 is not installed, it will look for Qt5 (5.12 minimal).
* USE_SYSTEM_BOX2D (OFF by default) to use the system box2D library if already installed. Note that it only works for Box2D 2.3.1.
* BUILD_EXAMPLES (ON by default) to build the examples along with the plugin. It will generate a binary `box2qml-examples` in the `bin` folder that you can run.
* BUILD_SHARED_LIBS (ON by default) to build either a STATIC or SHARED library.

### Installing on Debian

    debuild -uc -us -b
    sudo dpkg -i ../qml-box2d_*.deb

### Running the Examples

You can run the examples launcher from a Terminal/Cmd prompt with:

    qmlscene examples/ui.qml

(You need to be in the root folder of qml-box2d.)

### Deployment

The standard plugin (dynamically linked) runs well on Mac, Window and Linux.
The qml-box2d plugin can be linked statically to run on both iOS and Android.

### Using Qt Creator

For running you can use a "Custom Executable" configuration set to run
"qmlscene" with the right parameters.

When you have write permissions to Qt's import path, it can be convenient to
add a deployment step to your run settings:

 * Go to Projects -> box2d -> Run Settings
 * Choose Add Deploy Step -> Make
 * Enter "install" under "Make arguments"

This will make sure that before running, the version of the plugin is updated
in Qt's import path.

### Example Screenshots

(These screenshots have been done on an iPad Air)

<img src="./examples/screenshots/IMG_0645.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0647.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0648.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0653.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0656.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0657.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0658.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0661.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0666.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0669.PNG" width="800" height="600">

<img src="./examples/screenshots/IMG_0675.PNG" width="800" height="600">
