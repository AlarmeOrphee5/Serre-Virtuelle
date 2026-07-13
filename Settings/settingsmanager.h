#pragma once

#include <QString>
#include <QColor>

class SettingsManager
{
public:

    static QString theme();
    static void setTheme(const QString& theme);

    static QColor potEmptyColor();
    static void setPotEmptyColor(const QColor& color);

};
