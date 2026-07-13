#pragma once

#include <QString>

/*
 * Données d'un module du dashboard.
 *
 * Exemple :
 *   ModuleInfo info { "🌿", "Tables actives", "12", "sur 17 tables" };
 */

struct ModuleInfo
{
    QString icon;
    QString title;
    QString value;
    QString subtitle;
};
