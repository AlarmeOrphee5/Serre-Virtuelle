#include "tablesection.h"

#include "Core/Communs/legendbar.h"
#include "Core/Database/tableculturerepository.h"
#include "Core/Database/databasemanager.h"
#include "qdatetime.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>

constexpr int nombreColonnes = 4;



TableSection::TableSection(QWidget* parent)
    : QWidget(parent)
{

    setAttribute(Qt::WA_StyledBackground, true);

    setObjectName("TableSection");

    setStyleSheet(R"(
        QWidget#TableSection {
            background-color:#151922;
            border-radius:18px;
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


    for(const TableCultureData* table : m_tablesData)
    {
        if(table->estActive())
            count++;
    }


    return count;
}

int TableSection::nombreTables() const
{
    return m_tablesData.size();
}

int TableSection::nombrePotsActifs() const
{
    int count = 0;


    for(const TableCultureData* table : m_tablesData)
    {
        count += table->nombrePotsActifs();
    }


    return count;
}

int TableSection::nombrePotsTotal() const
{
    int count = 0;


    for(const TableCultureData* table : m_tablesData)
    {
        count += table->nombrePots();
    }


    return count;
}

QVector<TableCultureData*>& TableSection::tablesData()
{
    return m_tablesData;
}

void TableSection::refreshTables()
{
    qDeleteAll(m_tablesWidgets);
    m_tablesWidgets.clear();

    qDeleteAll(m_tablesData);
    m_tablesData.clear();

    while(QLayoutItem* item = m_tablesGrid->takeAt(0))
    {
        delete item;
    }

    TableCultureRepository repository;

    QVector<TableCultureData> tables =
        repository.loadAll();

    for(const TableCultureData& table : tables)
    {
        TableCultureData* data =
            new TableCultureData(table);

        TableCultureWidget* widget =
            new TableCultureWidget(*data);

        m_tablesData.append(data);
        m_tablesWidgets.append(widget);

        connect(widget,
                &TableCultureWidget::etatChanged,
                this,
                &TableSection::onTableEtatChanged);

        connect(widget,
                &TableCultureWidget::tableClicked,
                this,
                &TableSection::tableClicked);

        int index = m_tablesWidgets.size() - 1;

        m_tablesGrid->addWidget(
            widget,
            index / nombreColonnes,
            index % nombreColonnes,
            Qt::AlignCenter
            );
    }

    m_nextTableIndex = m_tablesData.size() + 1;
}

void TableSection::onTableEtatChanged()
{
    emit tablesActivesChanged(
        nombreTablesActives()
        );


    emit potsActifsChanged(
        nombrePotsActifs(),
        nombrePotsTotal()
        );
}

void TableSection::setupHeader(QVBoxLayout* layout)
{

    QLabel* title = new QLabel(
        "🌱 Tables de cultures"
        );


    title->setStyleSheet(
        "color:white;"
        "font-size:18px;"
        "font-weight:600;"
        "background:transparent;"
        );


    layout->addWidget(title);

    layout->addSpacing(8);
}

void TableSection::setupScroll(QVBoxLayout* layout)
{
    QScrollArea* scroll = new QScrollArea;

    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet(
        "border:none;"
        "background:transparent;"
        );

    QWidget* container = new QWidget;

    container->setStyleSheet(
        "background:transparent;"
        );

    QVBoxLayout* containerLayout =
        new QVBoxLayout(container);

    m_tablesGrid = new QGridLayout;
    m_tablesGrid->setSpacing(15);

    QWidget* gridWrap = new QWidget;

    gridWrap->setStyleSheet(
        "background:transparent;"
        );

    QHBoxLayout* wrapLayout =
        new QHBoxLayout(gridWrap);

    wrapLayout->setContentsMargins(0,0,0,0);
    wrapLayout->setAlignment(Qt::AlignCenter);
    wrapLayout->addLayout(m_tablesGrid);

    containerLayout->addWidget(gridWrap);

    scroll->setWidget(container);

    layout->addWidget(scroll);

    // Chargement des données
    refreshTables();
}

void TableSection::setupLegend(QVBoxLayout* layout)
{
    layout->addWidget(
        new LegendBar
        );
}

void TableSection::deleteTable(int id)
{
    TableCultureRepository tableRepository;
    PotRepository potRepository;

    TableCultureData table;

    if(!tableRepository.findById(id, table))
        return;

    DatabaseManager& db =
        DatabaseManager::getInstance();

    if(!db.beginTransaction())
        return;

    if(!potRepository.removeByTableId(id))
    {
        db.rollback();
        return;
    }

    if(!tableRepository.remove(table))
    {
        db.rollback();
        return;
    }

    if(!db.commit())
    {
        db.rollback();
        return;
    }

    refreshTables();
    onTableEtatChanged();
}

void TableSection::addTable(TableCultureData* source)
{
    TableCultureRepository tableRepository;
    PotRepository potRepository;

    TableCultureData table;

    if(source)
    {
        table = *source;
    }
    else
    {
        table.setName(
            "Table A" +
            QString::number(m_nextTableIndex)
            );
    }

    table.setNumero(m_nextTableIndex);
    table.setActive(false);

    if(table.dateCreation().isEmpty())
    {
        table.setDateCreation(
            QDateTime::currentDateTime().toString("dd/MM/yy-hh:mm")
            );
    }

    DatabaseManager& db =
        DatabaseManager::getInstance();

    if(!db.beginTransaction())
        return;

    if(!tableRepository.save(table))
    {
        db.rollback();
        return;
    }

    for(PotData& pot : table.pots())
    {
        if(!potRepository.save(pot, table.id()))
        {
            db.rollback();
            return;
        }
    }

    if(!db.commit())
    {
        db.rollback();
        return;
    }

    refreshTables();
}

void TableSection::refreshTable(int id)
{
    for(TableCultureWidget* widget : m_tablesWidgets)
    {
        if(widget->data().id() == id)
        {
            widget->refresh();

            onTableEtatChanged();

            return;
        }
    }
}
/*void TableSection::refreshTable(int id)
{
    TableCultureRepository repository;

    TableCultureData updated;

    if(!repository.findById(id, updated))
        return;


    for(TableCultureWidget* widget : m_tablesWidgets)
    {
        if(widget->data().id() == id)
        {
            widget->data() = updated;
            widget->refresh();
            break;
        }
    }
}*/
