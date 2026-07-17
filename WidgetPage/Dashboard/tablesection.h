#pragma once

#include "WidgetPage/TableCulture/tableculturewidget.h"
#include "DataManager/TableCulture/tableculturedata.h"

#include <QWidget>
#include <QVector>


class QGridLayout;
class QVBoxLayout;


class TableSection : public QWidget
{
    Q_OBJECT

public:

    explicit TableSection(QWidget* parent = nullptr);


    int nombreTablesActives() const;
    int nombreTables() const;

    int nombrePotsActifs() const;
    int nombrePotsTotal() const;


    QVector<TableCultureData*>& tablesData();
    void refreshTables();


signals:
    void deleteRequested(int id);
    void duplicateRequested(int id);
    void tableUpdated(int id);
    void tableClicked(TableCultureWidget* table);

    void tablesActivesChanged(int nombre);
    void potsActifsChanged(int actifs, int total);



public slots:

    void addTable(TableCultureData* source = nullptr);
    void deleteTable(int id);
    void refreshTable(int id);

private slots:

    void onTableEtatChanged();

private:

    void setupHeader(QVBoxLayout* layout);
    void setupScroll(QVBoxLayout* layout);
    void setupLegend(QVBoxLayout* layout);
    bool removeByTableId(int tableId);

    QGridLayout* m_tablesGrid = nullptr;


    QVector<TableCultureData*>
        m_tablesData;


    QVector<TableCultureWidget*>
        m_tablesWidgets;


    int m_nextTableIndex = 1;
};
