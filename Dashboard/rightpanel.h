#pragma once

#include <QWidget>
#include <QVBoxLayout>

/*
 * Panneau latéral droit du dashboard.
 *
 * Contient :
 * - la carte Alertes
 * - la carte Tâches
 *
 * Largeur fixe : 320px
 */

class RightPanel : public QWidget
{
    Q_OBJECT
public:
    explicit RightPanel(QWidget* parent = nullptr);

signals:
    void ajouterTableClicked();
};
