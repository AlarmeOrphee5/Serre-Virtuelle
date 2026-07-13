#include "settingsmanager.h"

#include <QSettings>


QString SettingsManager::theme()
{
    QSettings settings;

    return settings.value(
                       "appearance/theme",
                       "dark"
                       ).toString();
}


void SettingsManager::setTheme(const QString& theme)
{
    QSettings settings;

    settings.setValue(
        "appearance/theme",
        theme
        );
}


QColor SettingsManager::potEmptyColor()
{
    QSettings settings;

    return settings.value(
                       "colors/potEmpty",
                       QColor("#808080")
                       ).value<QColor>();
}


void SettingsManager::setPotEmptyColor(const QColor& color)
{
    QSettings settings;

    settings.setValue(
        "colors/potEmpty",
        color
        );
}
