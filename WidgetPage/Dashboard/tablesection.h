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


signals:

    void tableClicked(TableCultureWidget* table);

    void tablesActivesChanged(int nombre);
    void potsActifsChanged(int actifs, int total);



public slots:

    void addTable(TableCultureData* source = nullptr);
    void deleteTable(TableCultureWidget* table);
    void refreshTable(TableCultureWidget* table);



private slots:

    void onTableEtatChanged();



private:

    void setupHeader(QVBoxLayout* layout);
    void setupScroll(QVBoxLayout* layout);
    void setupLegend(QVBoxLayout* layout);

    QGridLayout* m_tablesGrid = nullptr;


    QVector<TableCultureData*>
        m_tablesData;


    QVector<TableCultureWidget*>
        m_tablesWidgets;


    int m_nextTableIndex = 1;
};
