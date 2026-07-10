#include "tableculturewidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QRandomGenerator>


TableCultureWidget::TableCultureWidget(TableCultureData& data,
                                       QWidget *parent)
    : QWidget(parent),
    m_data(data)
{
    setupUi();
    //setCursor(Qt::PointingHandCursor);
}

void TableCultureWidget::mousePressEvent(QMouseEvent* e)
{
    emit tableClicked(this);

    QWidget::mousePressEvent(e);
}


//--------------------------------------------------
// Activation / désactivation
//--------------------------------------------------
void TableCultureWidget::setEnabled(bool etat)
{
    m_data.setActive(etat);


    for (PotWidget* pot : std::as_const(m_potWidgets))
    {
        pot->setEnabled(m_data.estActive());
    }

    refresh();


    emit etatChanged();
}

//--------------------------------------------------
// Refresh des pots et des styles
//--------------------------------------------------
void TableCultureWidget::refresh()
{
    for(int i = 0; i < m_potWidgets.size(); i++)
    {
        m_potWidgets[i]->setEtat(
            m_data.pots()[i].etat()
            );
    }

    updateStyle();
}

//--------------------------------------------------
// Nombre de pots actifs
//--------------------------------------------------

int TableCultureWidget::nombrePotsActifs() const
{
    int count = 0;


    for (const PotData& pot : m_data.pots())
    {
        if (pot.etat() != EtatPot::Inactif &&
            pot.etat() != EtatPot::HorsService)
        {
            count++;
        }
    }


    return count;
}


//--------------------------------------------------
// Style de la carte
//--------------------------------------------------

void TableCultureWidget::updateStyle()
{
    if (m_data.estActive())
    {
        m_card->setStyleSheet(R"(
            QWidget#TableCard {
                background-color: #151922;
                border-radius: 14px;
                border: 1px solid rgba(255,255,255,0.08);
            }
        )");

        m_statusDot->setStyleSheet(
            "background:#5fbf66;"
            "border-radius:5px;"
            "border:none;"
            );

        m_statusLabel->setText("Actif");

        m_waterLabel->setVisible(true);
    }
    else
    {
        m_card->setStyleSheet(R"(
            QWidget#TableCard {
                background-color: #0f1318;
                border-radius: 14px;
                border: 1px solid rgba(255,255,255,0.02);
            }
        )");

        m_statusDot->setStyleSheet(
            "background:#910707;"
            "border-radius:5px;"
            "border:none;"
            );

        m_statusLabel->setText("Inactif");

        m_waterLabel->setVisible(false);
    }


    refreshPotCount();
}


//--------------------------------------------------
// Création interface
//--------------------------------------------------

void TableCultureWidget::setupUi()
{
    setMinimumSize(155, 252);
    setMaximumWidth(155);

    setSizePolicy(
        QSizePolicy::Preferred,
        QSizePolicy::Preferred
        );

    setAttribute(Qt::WA_StyledBackground, true);

    setStyleSheet(
        "TableCultureWidget {"
        "background: transparent;"
        "border: none;"
        "}"
        );


    QVBoxLayout* outerLayout =
        new QVBoxLayout(this);


    outerLayout->setContentsMargins(0,0,0,0);
    outerLayout->setSpacing(0);



    m_card = new QWidget(this);

    m_card->setSizePolicy(
        QSizePolicy::Fixed,
        QSizePolicy::Preferred
        );

    m_card->setFixedWidth(155);

    m_card->setAttribute(
        Qt::WA_StyledBackground,
        true
        );

    m_card->setObjectName("TableCard");



    QVBoxLayout* mainLayout =
        new QVBoxLayout(m_card);


    mainLayout->setContentsMargins(
        14,14,14,14
        );

    mainLayout->setSpacing(10);

    mainLayout->setAlignment(
        Qt::AlignCenter
        );


    outerLayout->addWidget(m_card);


    setupHeader(mainLayout);
    setupGrid(mainLayout);
    setupFooter(mainLayout);


    updateStyle();
}


//--------------------------------------------------
// Header
//--------------------------------------------------

void TableCultureWidget::setupHeader(QVBoxLayout* mainLayout)
{
    QFrame* header = new QFrame;


    header->setStyleSheet(
        "background:transparent;"
        "border:none;"
        );


    QVBoxLayout* headerLayout =
        new QVBoxLayout(header);


    headerLayout->setContentsMargins(0,0,0,0);
    headerLayout->setSpacing(4);



    QLabel* title =
        new QLabel(m_data.name());


    title->setAttribute(
        Qt::WA_OpaquePaintEvent,
        false
        );

    title->setAttribute(
        Qt::WA_NoSystemBackground,
        true
        );


    title->setStyleSheet(
        "color:white;"
        "font-weight:600;"
        "background:transparent;"
        "border:none;"
        );



    m_statusDot = new QFrame;

    m_statusDot->setFixedSize(10,10);



    m_statusLabel = new QLabel;


    m_statusLabel->setStyleSheet(
        "color:#9aa4b2;"
        "font-size:11px;"
        "background:transparent;"
        "border:none;"
        );



    QWidget* statusWidget =
        new QWidget;


    statusWidget->setStyleSheet(
        "background:transparent;"
        "border:none;"
        );



    QHBoxLayout* statusLayout =
        new QHBoxLayout(statusWidget);


    statusLayout->setContentsMargins(0,0,0,0);
    statusLayout->setSpacing(6);


    statusLayout->addWidget(m_statusDot);
    statusLayout->addWidget(m_statusLabel);



    headerLayout->addWidget(
        title,
        0,
        Qt::AlignCenter
        );

    headerLayout->addWidget(
        statusWidget,
        0,
        Qt::AlignCenter
        );


    mainLayout->addWidget(header);
}


//--------------------------------------------------
// Grille des pots
//--------------------------------------------------

void TableCultureWidget::setupGrid(QVBoxLayout* mainLayout)
{
    QWidget* gridBox =
        new QWidget(m_card);


    gridBox->setObjectName("GridBox");


    gridBox->setStyleSheet(R"(
        QWidget#GridBox {
            background-color: #101827;
            border-radius: 12px;
            border: 1px solid rgba(255,255,255,0.05);
        }
    )");



    QVBoxLayout* gridBoxLayout =
        new QVBoxLayout(gridBox);


    gridBoxLayout->setContentsMargins(
        8,8,8,8
        );



    m_gridLayout =
        new QGridLayout;


    m_gridLayout->setSpacing(6);


    m_gridLayout->setAlignment(
        Qt::AlignCenter
        );



    for (int i = 0; i < m_data.nombrePots(); i++)
    {
        PotWidget* pot =
            new PotWidget(
                m_data.pot(i),
                this
                );


        connect(
            pot,
            &PotWidget::etatChanged,
            this,
            &TableCultureWidget::refreshPotCount
            );


        pot->setEnabled(false);


        m_potWidgets.append(pot);


        m_gridLayout->addWidget(
            pot,
            i / 4,
            i % 4
            );
    }



    gridBoxLayout->addLayout(m_gridLayout);


    mainLayout->addWidget(
        gridBox,
        0,
        Qt::AlignCenter
        );
}


//--------------------------------------------------
// Compteur
//--------------------------------------------------

void TableCultureWidget::refreshPotCount()
{
    int actifs = nombrePotsActifs();


    m_potsLabel->setText(
        QString::number(actifs)
        + "/"
        + QString::number(m_data.nombrePots())
        + " pots utilisés"
        );
}


//--------------------------------------------------
// Footer
//--------------------------------------------------

void TableCultureWidget::setupFooter(QVBoxLayout* mainLayout)
{
    QWidget* footer =
        new QWidget;


    footer->setStyleSheet(
        "background:transparent;"
        "border:none;"
        );



    QVBoxLayout* footerLayout =
        new QVBoxLayout(footer);



    footerLayout->setContentsMargins(0,0,0,0);
    footerLayout->setSpacing(4);



    m_potsLabel =
        new QLabel(
            "0/"
            + QString::number(m_data.nombrePots())
            + " pots"
            );



    m_potsLabel->setStyleSheet(
        "color:#9aa4b2;"
        "font-size:11px;"
        "background:transparent;"
        "border:none;"
        );



    m_waterLabel =
        new QLabel(
            "Arrosé le : 21/05/2026"
            );



    m_waterLabel->setStyleSheet(
        "color:#9aa4b2;"
        "font-size:11px;"
        "background:transparent;"
        "border:none;"
        );



    footerLayout->addWidget(
        m_potsLabel,
        0,
        Qt::AlignCenter
        );


    footerLayout->addWidget(
        m_waterLabel,
        0,
        Qt::AlignCenter
        );


    mainLayout->addWidget(footer);
}


//--------------------------------------------------
// Accès widget pot
//--------------------------------------------------

PotWidget* TableCultureWidget::potWidget(int index) const
{
    if(index < 0 ||
        index >= m_potWidgets.size())
    {
        return nullptr;
    }


    return m_potWidgets[index];
}
