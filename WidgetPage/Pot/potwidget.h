#pragma once

#include "DataManager/Pot/potdata.h"
#include "Core/Communs/couleurconversion.h"

#include <QPushButton>


class PotWidget : public QPushButton
{
    Q_OBJECT

public:

    explicit PotWidget(PotData& data, QWidget* parent = nullptr);


    // Accès aux données
    PotData& data();
    const PotData& data() const;


    // Raccourcis pratiques
    void setEtat(EtatPot etat);
    EtatPot etat() const;


    QString nomPlante() const;
    void setNomPlante(const QString& nom);


    QString datePlantation() const;
    void setDatePlantation(const QString& date);


    int numeroPot() const;
    void setNumeroPot(int numero);


signals:

    void etatChanged();


private:

    void updateStyle();
    void updateTooltip();


private:

    PotData& m_data;
};
