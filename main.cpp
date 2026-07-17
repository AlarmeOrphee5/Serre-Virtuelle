#include "mainwindow.h"
#include "Core/Database/databasemanager.h"

#include "Core/Database/tableculturerepository.h"
#include "DataManager/TableCulture/tableculturedata.h"
#include "Core/Database/potrepository.h"

#include <QDateTime>
#include <QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(R"(
    QScrollArea, QAbstractScrollArea {
        border: none;
        background: transparent;
    }
    QScrollBar:vertical {
        background: #151922;
        width: 6px;
        border-radius: 3px;
    }
    QScrollBar::handle:vertical {
        background: #2e3a4a;
        border-radius: 3px;
        min-height: 30px;
    }
    QScrollBar::add-line:vertical,
    QScrollBar::sub-line:vertical {
        height: 0px;
    }
    QScrollBar::add-page:vertical,
    QScrollBar::sub-page:vertical {
        background: none;
    }

    QToolTip {
        background-color: #1f2633;
        color: white;
        border: 1px solid rgba(255,255,255,0.1);
        border-radius: 6px;
        padding: 6px;
        font-size: 11px;
    }
)");

    QString dbPath =
        QCoreApplication::applicationDirPath()
        + "/serre.db";

    if (!DatabaseManager::getInstance().initialize(dbPath))
    {
        return -1;
    }

    a.setStyle("Fusion");
    QCoreApplication::setOrganizationName("SerreVirtuelle");
    QCoreApplication::setApplicationName("SerreVirtuelle");
    MainWindow w;
    w.show();
    int result = a.exec();

    DatabaseManager::getInstance().close();

    return result;
}
