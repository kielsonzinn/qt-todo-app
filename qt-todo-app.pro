QT       += core gui
CONFIG   += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = todo-app
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    task.cpp

HEADERS  += mainwindow.h \
    task.h

FORMS    += mainwindow.ui \
    task.ui

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}

CONFIG(release, debug|release) {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u
