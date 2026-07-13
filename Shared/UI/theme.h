#pragma once

#include <QString>


class Theme
{

public:

    // =========================
    // BACKGROUNDS
    // =========================

    static QString pageBackground();

    static QString sidebarBackground();

    static QString cardBackground();

    static QString inputBackground();

    static QString cardHoverBackground();


    // =========================
    // TEXTES
    // =========================

    static QString textPrimary();

    static QString textSecondary();

    static QString textMuted();


    // =========================
    // ELEMENTS UI
    // =========================

    static QString border();

    static QString separator();


    // =========================
    // ETATS
    // =========================

    static QString success();

    static QString successHover();

    static QString danger();

    static QString warning();


    // =========================
    // DIMENSIONS
    // =========================

    static int radiusCard();

    static int radiusButton();

    static int spacingSmall();

    static int spacingNormal();

    static int spacingLarge();


    // =========================
    // TAILLES TEXTE
    // =========================

    static int fontPageTitle();

    static int fontSectionTitle();

    static int fontValue();

    static int fontBody();

    static int fontDescription();

    static int fontMuted();

};
