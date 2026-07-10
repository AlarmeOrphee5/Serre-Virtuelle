#pragma once
#include <QString>
#include "couleurconversion.h"

class PotData
{
public:

    explicit PotData(int numeroPot = 0,
                     EtatPot etat = EtatPot::Inactif);


    // Numéro du pot
    int numeroPot() const;
    void setNumeroPot(int numero);


    // Etat du pot
    EtatPot etat() const;
    void setEtat(EtatPot etat);


    // Plante
    QString nomPlante() const;
    void setNomPlante(const QString& nom);


    // Date plantation
    QString datePlantation() const;
    void setDatePlantation(const QString& date);

    QString toString() const;

private:

    int m_numeroPot = 0;

    EtatPot m_etat = EtatPot::Inactif;

    QString m_nomPlante;
    QString m_datePlantation;
};
