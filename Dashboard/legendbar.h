#pragma once

#include <QFrame>

class QHBoxLayout;

/*
 * Barre de légende des couleurs de pots.
 *
 * Affiche une rangée de points colorés avec leur label.
 * Utilisable partout où une TableSection est affichée.
 */

class LegendBar : public QFrame
{
public:
    explicit LegendBar(QWidget* parent = nullptr);

private:
    void addItem(QHBoxLayout* layout,
                 const QString& color,
                 const QString& text);
};
