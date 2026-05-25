#include "dashboardpage.h"
#include "topmodulebar.h"
#include "tablesection.h"
#include "rightpanel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

DashboardPage::DashboardPage(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20,25,20,20);
    layout->setSpacing(18);

    setupHeader(layout);

    m_topModulesBar = new TopModulesBar;
    layout->addWidget(m_topModulesBar);

    QWidget* bottomRow = new QWidget;
    bottomRow->setAttribute(Qt::WA_StyledBackground, true);
    bottomRow->setStyleSheet("background:transparent;");

    QHBoxLayout* bottomLayout = new QHBoxLayout(bottomRow);
    bottomLayout->setContentsMargins(0,0,0,0);
    bottomLayout->setSpacing(18);

    m_tableSection = new TableSection;
    bottomLayout->addWidget(m_tableSection, 1);
    bottomLayout->addWidget(m_rightPanel);

    layout->addWidget(bottomRow, 1);

    setupConnections();
}

TopModulesBar *DashboardPage::topModulesBar()
{
    return m_topModulesBar;
}

TableSection *DashboardPage::tableSection()
{
    return m_tableSection;
}

void DashboardPage::setupHeader(QVBoxLayout* layout)
{
    QFrame* header = new QFrame;
    header->setFrameShape(QFrame::NoFrame);
    header->setStyleSheet("background:transparent;");

    QVBoxLayout* headerLayout = new QVBoxLayout(header);
    headerLayout->setContentsMargins(0,0,0,10);
    headerLayout->setSpacing(4);

    QLabel* mainTitle = new QLabel("Dashboard");
    mainTitle->setStyleSheet("color:white; font-size:28px; font-weight:700; background:transparent;");

    QLabel* subtitle = new QLabel("Vue d'ensemble de vos serres");
    subtitle->setStyleSheet("color:#9aa4b2; font-size:13px; background:transparent;");

    headerLayout->addWidget(mainTitle);
    headerLayout->addWidget(subtitle);
    layout->addWidget(header);
}

void DashboardPage::setupConnections()
{
    connect(m_tableSection, &TableSection::tablesActivesChanged,
            m_topModulesBar, [this](int count) {
                m_topModulesBar->updateModule(
                    0,
                    QString::number(count),
                    "sur " + QString::number(m_tableSection->nombreTables()) + " tables"
                    );
            });

    connect(m_tableSection, &TableSection::potsActifsChanged,
            m_topModulesBar, [this](int actifs, int total) {
                m_topModulesBar->updateModule(
                    1,
                    QString::number(actifs),
                    "sur " + QString::number(total) + " pots"
                    );
            });

    connect(m_rightPanel, &RightPanel::ajouterTableClicked,
            m_tableSection, [this]() {
                m_tableSection->addTable(nullptr);
            });

    m_topModulesBar->updateModule(
        0,
        QString::number(m_tableSection->nombreTablesActives()),
        "sur " + QString::number(m_tableSection->nombreTables()) + " tables"
        );

    m_topModulesBar->updateModule(
        1,
        QString::number(m_tableSection->nombrePotsActifs()),
        "sur " + QString::number(m_tableSection->nombrePotsTotal()) + " pots"
        );
}
