#include "theme.h"


// =========================
// BACKGROUNDS
// =========================

QString Theme::pageBackground()
{
    return "#0f141b";
}


QString Theme::sidebarBackground()
{
    return "#121720";
}


QString Theme::cardBackground()
{
    return "#151922";
}


QString Theme::inputBackground()
{
    return "#151922";
}


QString Theme::cardHoverBackground()
{
    return "#1f2633";
}



// =========================
// TEXTES
// =========================

QString Theme::textPrimary()
{
    return "#ffffff";
}


QString Theme::textSecondary()
{
    return "#9aa4b2";
}


QString Theme::textMuted()
{
    return "#5c6370";
}



// =========================
// ELEMENTS UI
// =========================

QString Theme::border()
{
    return "rgba(255,255,255,0.08)";
}


QString Theme::separator()
{
    return "rgba(255,255,255,0.08)";
}



// =========================
// ETATS
// =========================

QString Theme::success()
{
    return "#5fbf66";
}


QString Theme::successHover()
{
    return "#7ed68a";
}


QString Theme::danger()
{
    return "#910707";
}


QString Theme::warning()
{
    return "#d99b32";
}



// =========================
// DIMENSIONS
// =========================

int Theme::radiusCard()
{
    return 14;
}


int Theme::radiusButton()
{
    return 8;
}


int Theme::spacingSmall()
{
    return 6;
}


int Theme::spacingNormal()
{
    return 12;
}


int Theme::spacingLarge()
{
    return 18;
}



// =========================
// TAILLES TEXTE
// =========================

int Theme::fontPageTitle()
{
    return 26;
}


int Theme::fontSectionTitle()
{
    return 16;
}


int Theme::fontValue()
{
    return 22;
}


int Theme::fontBody()
{
    return 13;
}


int Theme::fontDescription()
{
    return 13;
}


int Theme::fontMuted()
{
    return 11;
}
