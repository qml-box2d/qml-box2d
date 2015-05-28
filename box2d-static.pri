# Include this file in your .pro file to statically compile the Box2D QML
# bindings into your project.
#
# Basic usage instructions:
#
#  #include <box2dplugin.h>
#
#  int main(int argc, char *argv[])
#  {
#      QApplication app(argc, argv);
#
#      Box2DPlugin plugin;
#      plugin.registerTypes("Box2D");
#
#      ...
#  }

include(box2d_lib.pri)

DEFINES += STATIC_PLUGIN_BOX2D
