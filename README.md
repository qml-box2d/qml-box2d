## QML Box2D plugin
----------------

This plugin is meant to be installed to your Qt/imports directory, or shipped
in a directory of which the parent is added as import path.

The goal is to expose the functionality of Box2D as QML components, in order
to make it easy to write physics based games in QML.


#### INSTALLING
-----------

If running into permissions issues please use sudo with sudo if necessary

By default everything gets insalled to your qt examples and plugin directory's

```bash
 qmake
 make
 make install
```


#### RUNNING THE EXAMPLES
-----------

After building all the examples will be located in your $$[QT_INSTALL_EXAMPLE]
 directory. But one can also use qtcreator to pick which example they would like
to run.  See the section below [using qt creator](#USING-QT-CREATOR)


#### DEPLOYMENT
-----------

Support for deployment to mobile devices like the N900 and N8 is being worked
on.


#### USING QT CREATOR
-----------

Open the box2d pro file and selcet which example project you would like to run
note there is a all-examples example applicaiton that allows one to view all
the examples.

When you have write permissions to Qt's import path, it can be convenient to
add a deployment step to your run settings:

 * Go to Projects -> box2d -> Run Settings
 * Choose Add Deploy Step -> Make
 * Enter "install" under "Make arguments"

This will make sure that before running, the version of the plugin is updated
in Qt's import path.


#### OPTIONAL QML TOOLING
-----------

If you would like to get Syntax highlighting for the Qml Elements/Objects

 * Go to Projects -> box2d -> Run Settings
 * Choose Add Deploy Step -> Make
 * Enter "qmltypes" under "Make arguments"


#### DOCS
-----------
  Coming soon.
