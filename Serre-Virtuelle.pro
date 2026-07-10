QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dashboard/cardwidget.cpp \
    Dashboard/legendbar.cpp \
    Dashboard/dashboardpage.cpp \
    Exporter/exportpdf.cpp \
    PageTable/tablespage.cpp \
    Shared/potdata.cpp \
    Shared/tableculture.cpp \
    Shared/tableculturedata.cpp \
    Shared/tableculturewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    Dashboard/modulecard.cpp \
    Shared/potwidget.cpp \
    Dashboard/rightpanel.cpp \
    sidebar.cpp \
    Dashboard/tablesection.cpp \
    Dashboard/topmodulebar.cpp

HEADERS += \
    Dashboard/cardwidget.h \
    Exporter/exportpdf.h \
    PageTable/tablespage.h \
    Shared/couleurconversion.h \
    Dashboard/legendbar.h \
    Dashboard/dashboardpage.h \
    Shared/potdata.h \
    Shared/tableculture.h \
    Shared/tableculturedata.h \
    Shared/tableculturewidget.h \
    mainwindow.h \
    Dashboard/modulecard.h \
    Dashboard/moduleinfo.h \
    Shared/potwidget.h \
    Dashboard/rightpanel.h \
    sidebar.h \
    Dashboard/tablesection.h \
    Dashboard/topmodulebar.h

INCLUDEPATH += Dashboard \
               PageTable \
               Shared

QT += network

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
