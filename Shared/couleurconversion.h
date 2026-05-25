#pragma once

#include <QString>
#include <QList>

/*
 * Définition centralisée des états de pot et de leurs conversions.
 *
 * Toutes les classes qui ont besoin d'une couleur ou d'un label
 * associé à un état importent uniquement ce fichier.
 *
 * Utilisation :
 *   EtatPot etat = EtatPot::Actif;
 *   QString hex   = colorFromEtat(etat);   // "#5fbf66"
 *   QString label = labelFromEtat(etat);   // "Actif"
 */

enum class EtatPot
{
    Inactif,
    Semis,
    Croissance,
    Repiquage,
    Stress,
    Hydrate,
    Actif,
    HorsService
};

inline QString colorFromEtat(EtatPot etat)
{
    switch (etat)
    {
    case EtatPot::Inactif:      return "#9aa4b2";//0
    case EtatPot::Semis:        return "#f1c40f";//1
    case EtatPot::Croissance:   return "#7be082";//2
    case EtatPot::Repiquage:    return "#e67e22";//3
    case EtatPot::Stress:       return "#e74c3c";//4
    case EtatPot::Hydrate:      return "#3498db";//5
    case EtatPot::Actif:        return "#5fbf66";//6
    case EtatPot::HorsService:  return "#000000";//7
    }
    return "#9aa4b2";
}

inline QString labelFromEtat(EtatPot etat)
{
    switch (etat)
    {
    case EtatPot::Inactif:      return "Inactif";
    case EtatPot::Semis:        return "Semis";
    case EtatPot::Croissance:   return "Croissance";
    case EtatPot::Repiquage:    return "Repiquage";
    case EtatPot::Stress:       return "Stress";
    case EtatPot::Hydrate:      return "Hydraté";
    case EtatPot::Actif:        return "Actif";
    case EtatPot::HorsService:  return "Hors service";
    }
    return "Inconnu";
}

inline QList<EtatPot> tousLesEtats()
{
    return {
        EtatPot::Inactif,
        EtatPot::Semis,
        EtatPot::Croissance,
        EtatPot::Repiquage,
        EtatPot::Stress,
        EtatPot::Hydrate,
        EtatPot::Actif,
        EtatPot::HorsService
    };
}

inline EtatPot etatFromColor(const QString& color)
{
    if (color == "#9aa4b2") return EtatPot::Inactif;
    if (color == "#f1c40f") return EtatPot::Semis;
    if (color == "#7be082") return EtatPot::Croissance;
    if (color == "#e67e22") return EtatPot::Repiquage;
    if (color == "#e74c3c") return EtatPot::Stress;
    if (color == "#3498db") return EtatPot::Hydrate;
    if (color == "#5fbf66") return EtatPot::Actif;
    if (color == "#000000") return EtatPot::HorsService;

    return EtatPot::Inactif; // fallback
}
