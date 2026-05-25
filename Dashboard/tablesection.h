#pragma once

#include <QWidget>
#include <QVector>

class QGridLayout;
class QVBoxLayout;
class TableCulture;

class TableSection : public QWidget
{
    Q_OBJECT

public:
    explicit TableSection(QWidget* parent = nullptr);

    int nombreTablesActives() const;
    int nombreTables() const;
    int nombrePotsActifs() const;
    int nombrePotsTotal() const;

    void deleteTable(TableCulture* table);
    void addTable(TableCulture* source = nullptr); // si source != nullptr → copie les pots et l'état

signals:
    void tablesActivesChanged(int count);
    void potsActifsChanged(int actifs, int total);
    void tableClicked(TableCulture* table);  // ← propagé depuis TableCulture
private slots:
    void onTableEtatChanged();

private:
    void setupHeader(QVBoxLayout* layout);
    void setupScroll(QVBoxLayout* layout);
    void setupLegend(QVBoxLayout* layout);

    QGridLayout*           m_tablesGrid;
    QVector<TableCulture*> m_tables;
    int m_nextTableIndex = 1; // ← compteur global, ne redescend jamais
};
