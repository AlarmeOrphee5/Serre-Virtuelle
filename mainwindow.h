#pragma once
#include <QMainWindow>
#include "tableculture.h"

class QStackedWidget;
class TopModulesBar;
class TableSection;
class TablesPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onPageChanged(const QString& page);
    void onTableClicked(TableCulture* table);

private:
    QStackedWidget* m_stack;
    TopModulesBar*  m_topModulesBar;
    TableSection*   m_tableSection;
    TablesPage*     m_tablesPage;
};
