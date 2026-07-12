#include "mainwindow.h"
#include "sidebar.h"
#include "dashboardpage.h"
#include "tablespage.h"
#include "tablesection.h"
#include "topmodulebar.h"
#include "tableculturewidget.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1400, 900);

    QWidget* central = new QWidget;
    central->setAttribute(Qt::WA_StyledBackground, true);
    central->setStyleSheet("background-color:#0f1117;");
    setCentralWidget(central);

    QHBoxLayout* root = new QHBoxLayout(central);
    root->setContentsMargins(0,0,0,0);
    root->setSpacing(0);

    // =========================
    // SIDEBAR
    // =========================
    SideBar* sidebar = new SideBar;
    root->addWidget(sidebar);

    // =========================
    // STACK DE PAGES
    // =========================
    m_stack = new QStackedWidget;
    m_stack->setStyleSheet("background:transparent;");

    // Dashboard — on récupère ses membres pour les connexions
    DashboardPage* dashboard = new DashboardPage;
    m_topModulesBar = dashboard->topModulesBar();
    m_tableSection  = dashboard->tableSection();

    m_stack->addWidget(dashboard);   // index 0

    // TablesPage — créée une fois, rechargée via loadTable()
    m_tablesPage = new TablesPage;
    m_stack->addWidget(m_tablesPage); // index 1

    m_tablesPage->setTablesData(
        &m_tableSection->tablesData()
    );

    m_stack->setCurrentIndex(0);
    root->addWidget(m_stack, 1);

    // =========================
    // CONNEXIONS
    // =========================

    // Navigation sidebar
    connect(sidebar, &SideBar::pageChanged,
            this,    &MainWindow::onPageChanged);

    // Clic sur une table → TablesPage
    connect(m_tableSection, &TableSection::tableClicked,
            this,           &MainWindow::onTableClicked);

    // Retour depuis TablesPage → Dashboard
    connect(m_tablesPage, &TablesPage::backRequested,
            this, [this]() { m_stack->setCurrentIndex(0); });

    // Modules
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

    connect(m_tablesPage,  &TablesPage::deleteRequested,
            m_tableSection, &TableSection::deleteTable);

    connect(m_tablesPage,   &TablesPage::duplicateRequested,
            m_tableSection, &TableSection::addTable);

    connect(m_tablesPage,&TablesPage::tableUpdated,
            m_tableSection,&TableSection::refreshTable);
    // Valeurs initiales
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

    connect(dashboard,
            &DashboardPage::exportSerreRequested,
            this,
            &MainWindow::exportSerre);
}

void MainWindow::onPageChanged(const QString& page)
{
    if      (page == "Dashboard") m_stack->setCurrentIndex(0);
    else if (page == "Tables")    m_stack->setCurrentIndex(1);
    else if (page == "Stats")     m_stack->setCurrentIndex(2);
    else if (page == "Settings")  m_stack->setCurrentIndex(3);
}

void MainWindow::onTableClicked(TableCultureWidget* table)
{
    m_tablesPage->loadTable(table);
    m_stack->setCurrentIndex(1);
}

void MainWindow::exportSerre()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter la serre",
        "Serre.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty())
        return;

    bool ok = PdfExporter::exporterSerre(
        m_tableSection->tablesData(),
        fileName
        );

    if (ok)
    {
        QMessageBox::information(
            this,
            "Export terminé",
            "Le rapport de la serre a été exporté avec succès."
            );
    }
    else
    {
        QMessageBox::critical(
            this,
            "Erreur",
            "Impossible de générer le fichier PDF."
            );
    }
}
