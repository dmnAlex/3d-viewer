QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl

# To use with Windows uncomment:
# QT += openglwidgets

CONFIG += c++17 warn_off

include(libs/gifimagelib/gifimage/qtgifimage.pri)

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# To use with Windows uncomment:
# LIBS   += -lopengl32
# LIBS   += -lglu32

SOURCES += \
    src/main.cc \
    src/model/facade.cc \
    src/model/file_reader.cc \
    src/model/qt_scene_drawer.cc \
    src/model/settings_store.cc \
    src/model/transform_matrix.cc \
    src/model/transform_matrix_builder.cc \
    src/model/scene.cc \
    src/model/transformation_handler.cc \
    src/view/mainwindow.cc \
    src/view/oglwidget.cc

HEADERS += \
    src/model/face_element.h \
    src/model/normalization_parametes.h \
    src/model/qt_gif_maker.h \
    src/model/scene.h \
    src/model/settings.h \
    src/model/settings_store.h \
    src/model/transformation_handler.h \
    src/model/transformations.h \
    src/view/mainwindow.h \
    src/model/base_file_reader.h \
    src/model/base_scene_drawer.h \
    src/model/edge.h \
    src/model/facade_operation_result.h \
    src/model/facade.h \
    src/model/figure.h \
    src/model/file_reader.h \
    src/model/point_3d.h \
    src/model/qt_scene_drawer.h \
    src/model/transform_matrix_builder.h \
    src/model/transform_matrix.h \
    src/model/vertex.h \
    src/controller/controller.h \
    src/view/oglwidget.h

FORMS += \
    src/view/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
