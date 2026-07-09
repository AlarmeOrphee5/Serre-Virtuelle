#pragma once

#include "couleurconversion.h"
#include <QPushButton>

class PotWidget : public QPushButton
{
    Q_OBJECT
public:
    explicit PotWidget(int numero, EtatPot etat = EtatPot::Inactif, QWidget* parent = nullptr);

    void setEtat(EtatPot etat);
    EtatPot etat() const;

    QString nomPlante() const;
    void setNomPlante(const QString& newNomPlante);

    int numeroPot() const;
    void setNumeroPot(int newNumeroPot);

    QString datePlantation() const;
    void setDatePlantation(const QString& newDatePlantation);

    QString toString();

signals:
    void etatChanged();

private:
    void updateStyle();
    void updateTooltip();

    int     m_numeroPot     = 0;
    EtatPot m_etat          = EtatPot::Inactif;
    QString m_nomPlante;
    QString m_datePlantation;
};
