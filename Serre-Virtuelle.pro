QT += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Core/Communs/appinfo.cpp \
    Core/Communs/cardwidget.cpp \
    Core/Communs/legendbar.cpp \
    Core/Export/exportpdf.cpp \
    Core/UI/theme.cpp \
    Core/UI/uigenerale.cpp \
    DataManager/Pot/potdata.cpp \
    DataManager/Settings/settingsmanager.cpp \
    DataManager/TableCulture/tableculturedata.cpp \
    WidgetPage/Dashboard/dashboardpage.cpp \
    WidgetPage/Dashboard/modulecard.cpp \
    WidgetPage/Dashboard/rightpanel.cpp \
    WidgetPage/Dashboard/tablesection.cpp \
    WidgetPage/Dashboard/topmodulebar.cpp \
    WidgetPage/PageTable/tablespage.cpp \
    WidgetPage/Pot/potwidget.cpp \
    WidgetPage/Settings/settingspage.cpp \
    WidgetPage/Sidebar/sidebar.cpp \
    WidgetPage/TableCulture/tableculturewidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Core/Communs/appinfo.h \
    Core/Communs/cardwidget.h \
    Core/Communs/couleurconversion.h \
    Core/Communs/legendbar.h \
    Core/Export/exportpdf.h \
    Core/UI/theme.h \
    Core/UI/uigenerale.h \
    DataManager/Pot/potdata.h \
    DataManager/Settings/settingsmanager.h \
    DataManager/TableCulture/tableculturedata.h \
    WidgetPage/Dashboard/dashboardpage.h \
    WidgetPage/Dashboard/modulecard.h \
    WidgetPage/Dashboard/moduleinfo.h \
    WidgetPage/Dashboard/rightpanel.h \
    WidgetPage/Dashboard/tablesection.h \
    WidgetPage/Dashboard/topmodulebar.h \
    WidgetPage/PageTable/tablespage.h \
    WidgetPage/Pot/potwidget.h \
    WidgetPage/Settings/settingspage.h \
    WidgetPage/Sidebar/sidebar.h \
    WidgetPage/TableCulture/tableculturewidget.h \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
