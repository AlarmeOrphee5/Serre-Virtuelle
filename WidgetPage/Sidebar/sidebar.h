#pragma once

#include <QFrame>
#include <QString>

class QVBoxLayout;

/*
 * Barre de navigation latérale.
 *
 * Contient :
 * - le bloc brand (icône + titre + sous-titre)
 * - les boutons de navigation
 * - le label de version
 *
 * Signals :
 * - pageChanged(QString) — émis quand l'utilisateur clique sur un bouton
 */

class SideBar : public QFrame
{
    Q_OBJECT

public:
    explicit SideBar(QWidget* parent = nullptr);

signals:
    void pageChanged(const QString& page);

private:
    void setupBrand(QVBoxLayout* layout);
    void setupNav(QVBoxLayout* layout);
    void setupVersion(QVBoxLayout* layout);
};
