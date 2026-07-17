#pragma once
#include <QString>
#include "Core/Communs/couleurconversion.h"

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

    int id() const;
    void setId(int id);

    QString toString() const;

private:

    int m_numeroPot = 0;

    EtatPot m_etat = EtatPot::Inactif;
    int m_id = -1;

    QString m_nomPlante;
    QString m_datePlantation;
};
