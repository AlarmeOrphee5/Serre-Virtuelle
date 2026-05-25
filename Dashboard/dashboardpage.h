#pragma once

#include "rightpanel.h"
#include <QWidget>
#include <QVBoxLayout>

class TopModulesBar;
class TableSection;

/*
 * Page Dashboard — première page de l'application.
 *
 * Contient :
 * - le header (titre + sous-titre)
 * - la TopModulesBar
 * - la TableSection
 * - le RightPanel
 */

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget* parent = nullptr);
    TopModulesBar* topModulesBar();
    TableSection* tableSection();

private:
    void setupHeader(QVBoxLayout* layout);
    void setupConnections();

    TopModulesBar* m_topModulesBar;
    TableSection*  m_tableSection;
    RightPanel* m_rightPanel = new RightPanel;
};
