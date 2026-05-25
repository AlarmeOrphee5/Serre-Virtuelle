#pragma once

#include <QWidget>
#include <QString>

class QVBoxLayout;

/*
 * Widget générique représentant une carte avec fond arrondi et bordure.
 *
 * Remplace les lambdas createTopCard et createSideCard de MainWindow.
 *
 * Utilisation :
 *   CardWidget* card = new CardWidget;
 *   card->setFixedHeight(80);
 *   card->innerLayout()->addWidget(myLabel);
 */

class CardWidget : public QWidget
{
public:
    explicit CardWidget(QWidget* parent = nullptr);

    // Accès au layout interne pour y ajouter des widgets
    QVBoxLayout* innerLayout() const;

private:
    QWidget*     m_card;
    QVBoxLayout* m_innerLayout;
};
