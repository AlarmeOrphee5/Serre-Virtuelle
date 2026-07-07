#include "tablesection.h"
#include "tableculture.h"
#include "legendbar.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QRandomGenerator>
#include <QTimer>

constexpr int nombreTablesInitiales = 7;
constexpr int nombreColonnes = 4;

TableSection::TableSection(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("TableSection");
    setStyleSheet(R"(
        QWidget#TableSection {
            background-color: #151922;
            border-radius: 18px;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(16,16,16,16);
    layout->setSpacing(12);

    setupHeader(layout);
    setupScroll(layout);
    setupLegend(layout);
}

int TableSection::nombreTablesActives() const
{
    int count = 0;
    for (TableCulture* t : m_tables)
        if (t->estActive()) count++;
    return count;
}

int TableSection::nombreTables() const
{
    return m_tables.size();
}

int TableSection::nombrePotsActifs() const
{
    int count = 0;
    for (TableCulture* t : m_tables)
        count += t->nombrePotsActifs();
    return count;
}

int TableSection::nombrePotsTotal() const
{
    int count = 0;
    for (TableCulture* t : m_tables)
        count += t->nombrePots();
    return count;
}

void TableSection::onTableEtatChanged()
{
    emit tablesActivesChanged(nombreTablesActives());
    emit potsActifsChanged(nombrePotsActifs(), nombrePotsTotal());
}

void TableSection::setupHeader(QVBoxLayout* layout)
{
    QLabel* title = new QLabel("🌱 Tables de cultures");
    title->setStyleSheet("color:white; font-size:18px; font-weight:600; background:transparent;");
    layout->addWidget(title);
    layout->addSpacing(8);
}

void TableSection::setupScroll(QVBoxLayout* layout)
{
    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("border:none; background:transparent;");
    scroll->viewport()->setStyleSheet("background:transparent;");
    scroll->viewport()->setAttribute(Qt::WA_NoSystemBackground, true);

    QWidget* container = new QWidget;
    container->setAttribute(Qt::WA_NoSystemBackground, true);
    container->setStyleSheet("background:transparent;");

    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(5,5,5,5);
    containerLayout->setSpacing(12);

    m_tablesGrid = new QGridLayout;
    m_tablesGrid->setSpacing(15);

    for (int i = 1; i <= nombreTablesInitiales; i++)
    {
        TableCulture* table = new TableCulture("Alvéole A" + QString::number(i));

        m_tables.append(table);

        // Propagation état
        connect(table, &TableCulture::etatChanged,
                this,  &TableSection::onTableEtatChanged);

        // Propagation clic ← nouveau
        connect(table, &TableCulture::tableClicked,
                this,  &TableSection::tableClicked);

        bool r = QRandomGenerator::global()->bounded(2);
        table->setEnabled(r);

        m_tablesGrid->addWidget(table,(i - 1) / nombreColonnes,(i - 1) % nombreColonnes,Qt::AlignCenter);
    }
    m_nextTableIndex = m_tables.size() + 1; // démarre à 8 si tu crées 7 tables

    QFrame* gridWrap = new QFrame;
    gridWrap->setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Preferred
        );
    gridWrap->setFrameShape(QFrame::NoFrame);
    gridWrap->setAttribute(Qt::WA_NoSystemBackground, true);
    gridWrap->setStyleSheet("background:transparent;");

    QHBoxLayout* wrapLayout = new QHBoxLayout(gridWrap);
    wrapLayout->setContentsMargins(0,0,0,0);
    wrapLayout->setAlignment(Qt::AlignCenter);
    wrapLayout->addLayout(m_tablesGrid);

    containerLayout->addWidget(gridWrap, 0, Qt::AlignHCenter);
    scroll->setWidget(container);
    layout->addWidget(scroll);
}

void TableSection::setupLegend(QVBoxLayout* layout)
{
    layout->addWidget(new LegendBar);
}


void TableSection::deleteTable(TableCulture* table)
{
    if (!table) return;

    // Retirer du vecteur
    m_tables.removeOne(table);

    // Retirer de la grille
    m_tablesGrid->removeWidget(table);

    // Détruire le widget
    table->deleteLater();

    // Remettre à jour les positions dans la grille
    for (int i = 0; i < m_tables.size(); i++)
        m_tablesGrid->addWidget(m_tables[i], i / nombreColonnes, i % nombreColonnes);

    // Mettre à jour les compteurs
    onTableEtatChanged();
}

void TableSection::addTable(TableCulture* source)
{
    TableCulture* table = new TableCulture("Table A" + QString::number(m_nextTableIndex++));

    if (source != nullptr)
    {
        table->setEnabled(source->estActive());

        for (int i = 0; i < source->pots().size(); i++)
            table->pots()[i]->setEtat(source->pots()[i]->etat());
    }
    table->updateStyle(); // ← recalcule le compteur avec les vrais états
    m_tables.append(table);
    int index = m_tables.size() - 1;
    table->setVisible(false);
    m_tablesGrid->addWidget(table, index / nombreColonnes, index % nombreColonnes);
    QTimer::singleShot(0, this, [this, table]()
                       {
                           m_tablesGrid->invalidate();
                           m_tablesGrid->activate();
                           table->setVisible(true);
                       });

    connect(table, &TableCulture::etatChanged,
            this,  &TableSection::onTableEtatChanged);
    connect(table, &TableCulture::tableClicked,
            this,  &TableSection::tableClicked);
    onTableEtatChanged();
}
