#pragma once

#include "moduleinfo.h"

#include <QWidget>

class QLabel;

/*
 * Carte affichant un ModuleInfo dans le dashboard.
 *
 * Affiche :
 * - une icône
 * - une valeur principale (grosse)
 * - un titre
 * - un sous-titre discret
 *
 * Utilisation :
 *   ModuleCard* card = new ModuleCard({ "🌿", "Tables actives", "12", "sur 17 tables" });
 */

class ModuleCard : public QWidget
{
public:
    explicit ModuleCard(const ModuleInfo& info, QWidget* parent = nullptr);

    // Met à jour la valeur affichée dynamiquement
    void setValue(const QString& value);

    void setSubtitle(const QString &subtitle);
private:
    QLabel* m_valueLabel;
    QLabel* m_subtitleLabel;
};
