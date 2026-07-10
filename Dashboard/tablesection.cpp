#include "tablesection.h"

#include "legendbar.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QRandomGenerator>


constexpr int nombreTablesInitiales = 7;
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



    for(int i = 1; i <= nombreTablesInitiales; i++)
    {

        TableCultureData* data =
            new TableCultureData(
                "Alvéole A" + QString::number(i)
                );


        // Données temporaires
        bool active =
            QRandomGenerator::global()->bounded(2);


        data->setActive(active);



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



        int index = m_tablesWidgets.size()-1;


        m_tablesGrid->addWidget(
            widget,
            index / nombreColonnes,
            index % nombreColonnes,
            Qt::AlignCenter
            );
    }



    m_nextTableIndex =
        m_tablesData.size()+1;



    QWidget* gridWrap = new QWidget;

    gridWrap->setStyleSheet(
        "background:transparent;"
        );


    QHBoxLayout* wrapLayout =
        new QHBoxLayout(gridWrap);


    wrapLayout->setContentsMargins(
        0,0,0,0
        );


    wrapLayout->setAlignment(
        Qt::AlignCenter
        );


    wrapLayout->addLayout(
        m_tablesGrid
        );



    containerLayout->addWidget(
        gridWrap
        );


    scroll->setWidget(container);


    layout->addWidget(scroll);
}




void TableSection::setupLegend(QVBoxLayout* layout)
{
    layout->addWidget(
        new LegendBar
        );
}




void TableSection::deleteTable(TableCultureWidget* table)
{

    if(!table)
        return;

    int index =
        m_tablesWidgets.indexOf(table);

    if(index < 0)
        return;

    m_tablesGrid->removeWidget(table);

    m_tablesWidgets.removeAt(index);

    delete table;

    delete m_tablesData[index];

    m_tablesData.removeAt(index);

    // Repositionnement
    for(int i = 0; i < m_tablesWidgets.size(); i++)
    {

        m_tablesGrid->addWidget(
            m_tablesWidgets[i],
            i / nombreColonnes,
            i % nombreColonnes,
            Qt::AlignCenter
            );
    }

    onTableEtatChanged();
}




void TableSection::addTable(TableCultureData* source)
{

    TableCultureData* data = nullptr;



    if(source)
    {
        data = new TableCultureData(
            *source
            );
    }
    else
    {
        data =
            new TableCultureData(
                "Table A" +
                QString::number(
                    m_nextTableIndex++
                    )
                );
    }



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



    int index =
        m_tablesWidgets.size()-1;



    m_tablesGrid->addWidget(
        widget,
        index / nombreColonnes,
        index % nombreColonnes,
        Qt::AlignCenter
        );


    onTableEtatChanged();
}
