#pragma once

#include "moduleinfo.h"

#include <QFrame>
#include <QVector>

class ModuleCard;

/*
 * Rangée des 5 modules en haut du dashboard.
 *
 * Chaque module est une ModuleCard construite à partir d'un ModuleInfo.
 * Appeler updateModule() pour mettre à jour une valeur dynamiquement.
 */

class TopModulesBar : public QFrame
{
public:
    explicit TopModulesBar(QWidget* parent = nullptr);

    // Met à jour la valeur d'un module par son index (0-4)
    void updateModule(int index, const QString& value, const QString& subtitle = "");

private:
    void addModule(const ModuleInfo& info);

    QVector<ModuleCard*> m_cards;
};
