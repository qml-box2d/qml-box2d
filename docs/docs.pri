## make all the files avilable for qtcreator
OTHER_FILES += \
        $$PWD/qmlbox2d.qdocconf \
        $$PWD/src/qml-qmlbox2d.qdoc \
        $$PWD/src/qml-overview.qdoc \
        $$PWD/src/qml-worldoverview.qdoc \
        $$PWD/src/qml-bodyoverview.qdoc \
        $$PWD/src/qml-shapesoverview.qdoc \
        $$PWD/src/qml-fixturesoverview.qdoc \
        $$PWD/src/qml-jointsoverview.qdoc \
        $$PWD/docs.pri

defineReplace(targetPath) {
    return($$replace(1, /, $$QMAKE_DIR_SEP))
}

qt:greaterThan(QT_MAJOR_VERSION, 4) {
    QDOC_BIN = $$targetPath($$[QT_INSTALL_BINS]/qdoc)
    QDOC_MAINFILE = $$PWD/qmlbox2d.qdocconf
} else {
    QDOC_BIN = $$targetPath($$[QT_INSTALL_BINS]/qdoc3)
    QDOC_MAINFILE = $$PWD/qmlbox2d.qdocconf

    # cheap replacement of the Qt5 shell_quote function
    defineReplace(shell_quote) {
        return("\"$$1\"")
    }
}

HELPGENERATOR = $$targetPath($$[QT_INSTALL_BINS]/qhelpgenerator)

VERSION_TAG = $$replace(QBS_VERSION, "[-.]", )

## for testing
HTML_DOC_PATH=$$OUT_PWD/doc/html

EXAMPLES_FILES=$$PWD/../examples/


equals(QMAKE_DIR_SEP, /) {   # unix, mingw+msys
    QDOC = SRCDIR=$$PWD OUTDIR=$$HTML_DOC_PATH QBS_VERSION=$$QBS_VERSION QBS_VERSION_TAG=$$VERSION_TAG QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS]  QT_INSTALL_ARCHDATA=$$[QT_INSTALL_ARCHDATA] QT_INSTALL_EXAMPLES=$$[QT_INSTALL_EXAMPLES]  $$QDOC_BIN
} else:win32-g++* {   # just mingw
    # The lack of spaces in front of the && is necessary!
    QDOC = set SRCDIR=$$PWD&& set OUTDIR=$$HTML_DOC_PATH&& set QBS_VERSION=$$QBS_VERSION&& set QBS_VERSION_TAG=$$VERSION_TAG&& set QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS]&& set QT_INSTALL_ARCHDATA=$$[QT_INSTALL_ARCHDATA]&& set QT_INSTALL_EXAMPLES=$$[QT_INSTALL_EXAMPLES]&& $$QDOC_BIN
} else {   # nmake
    QDOC = set SRCDIR=$$PWD $$escape_expand(\\n\\t) \
           set OUTDIR=$$HTML_DOC_PATH $$escape_expand(\\n\\t) \
           set QBS_VERSION=$$QBS_VERSION $$escape_expand(\\n\\t) \
           set QBS_VERSION_TAG=$$VERSION_TAG $$escape_expand(\\n\\t) \
           set QT_INSTALL_DOCS=$$[QT_INSTALL_DOCS] $$escape_expand(\\n\\t) \
           set QT_INSTALL_ARCHDATA=$$[QT_INSTALL_ARCHDATA] $$escape_expand(\\n\\t) \
           set QT_INSTALL_EXAMPLES=$$[QT_INSTALL_EXAMPLES] $$escape_expand(\\n\\t) \
           $$QDOC_BIN
}

QHP_FILE = $$HTML_DOC_PATH/qmlbox2d.qhp
QCH_FILE = $$OUT_PWD/doc/qmlbox2d.qch



HELP_DEP_FILES =  $$QDOC_MAINFILE

html_docs.commands = $$QDOC $$QDOC_MAINFILE
html_docs.depends += $$HELP_DEP_FILES

qch_docs.commands = $$HELPGENERATOR $$QHP_FILE -o $$QCH_FILE
qch_docs.depends += html_docs

inst_qch_docs.files = $$QCH_FILE
inst_qch_docs.path = $$[QT_INSTALL_DOCS]/
inst_qch_docs.CONFIG += no_check_exist no_default_install
INSTALLS += inst_qch_docs

inst_html_docs.files = $$HTML_DOC_PATH/*
inst_html_docs.path = $$[QT_INSTALL_DOCS]/qmlbox2d/
inst_html_docs.CONFIG += no_check_exist no_default_install directory
INSTALLS += inst_html_docs

install_docs.depends = install_inst_qch_docs install_inst_html_docs
QMAKE_EXTRA_TARGETS += install_docs

docs.depends = qch_docs
QMAKE_EXTRA_TARGETS += html_docs qch_docs docs



all_examples.files += $$PWD/../examples/*
all_examples.path = $$[QT_INSTALL_EXAMPLES]/qmlbox2d/
all_examples.CONFIG += no_check_exist no_default_install directory
INSTALLS += all_examples

