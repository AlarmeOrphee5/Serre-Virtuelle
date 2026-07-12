#pragma once

#include <QWidget>
#include <QPushButton>
#include <QButtonGroup>
#include "tableculturewidget.h"
#include "potdata.h"
#include "Exporter/exportpdf.h"
#include "tableculturedata.h"

#include <QFileDialog>
#include <QMessageBox>


class QStackedWidget;
class QVBoxLayout;
class QLabel;
class QFrame;
class QGridLayout;

/*
 * Page détail d'une table de culture.
 *
 * Appelée via loadTable(TableCulture*) depuis MainWindow
 * quand l'utilisateur clique sur une table dans le Dashboard.
 */

class TablesPage : public QWidget
{
    Q_OBJECT

public:
    explicit TablesPage(QWidget* parent = nullptr);

    // Charge et affiche les données de la table cliquée
    void loadTable(TableCultureWidget* table);
    void setTablesData(QVector<TableCultureData*>* data);

signals:
    void backRequested(); // ← bouton retour → MainWindow revient au Dashboard
    void deleteRequested(TableCultureWidget* table);
    void duplicateRequested(TableCultureData* table);
    void tableUpdated(TableCultureWidget* table);

private slots :
    void exportPDF();

private:
    void setupHeader(QVBoxLayout* layout);
    void setupTabs(QVBoxLayout* layout);
    void setupBody(QVBoxLayout* layout);

    void refreshHeader();
    void refreshGrid();
    void refreshInfos();
    void clearPotSelection();

    TableCultureWidget* m_table = nullptr; // table courante

    // Widgets mis à jour par loadTable()
    QLabel*      m_titleLabel;
    QLabel*      m_badgeLabel;
    QLabel*      m_breadcrumbTable;
    QGridLayout* m_potGrid;
    QWidget*     m_potGridContainer;

    QLabel*      m_infoNom;
    QLabel*      m_infoStatut;
    QLabel*      m_infoPotsCount;

    QPushButton* m_toggleTableBtn;
    QPushButton* m_deleteTableBtn;
    QPushButton* m_duplicateTableBtn;
    void toggleTableState();

    // gestionPot
    QWidget* m_potDetailPanel = nullptr;

    QLabel* m_potDetailNumero = nullptr;
    QLabel* m_potDetailNom = nullptr;
    QLabel* m_potDetailDate = nullptr;
    QLabel* m_potDetailEtat = nullptr;

    QVector<QPushButton*> m_etatButtons;
    QButtonGroup* m_etatGroup = nullptr;
    PotData* m_currentPot = nullptr;
    QMap<QPushButton*, EtatPot> m_buttonToEtat;

    QPushButton* m_btnOk = nullptr;
    QPushButton* m_btnWarning = nullptr;
    QPushButton* m_btnDanger = nullptr;


    void showPotDetail(int index);
    void refreshPotPanel();
    QVector<TableCultureData*>* m_tablesData = nullptr;
};
