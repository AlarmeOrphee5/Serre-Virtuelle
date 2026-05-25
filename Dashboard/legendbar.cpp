#include "legendbar.h"
#include "couleurconversion.h"

#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>

LegendBar::LegendBar(QWidget* parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::NoFrame);
    setStyleSheet("background:transparent;");

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,8,0,0);
    layout->setSpacing(14);

    for (EtatPot etat : tousLesEtats())
        addItem(layout, colorFromEtat(etat), labelFromEtat(etat));

    layout->addStretch();
}

void LegendBar::addItem(QHBoxLayout* layout,
                        const QString& color,
                        const QString& text)
{
    QWidget* item = new QWidget;
    item->setAttribute(Qt::WA_NoSystemBackground, true);

    QHBoxLayout* l = new QHBoxLayout(item);
    l->setContentsMargins(0,0,0,0);
    l->setSpacing(6);

    QFrame* dot = new QFrame;
    dot->setFixedSize(10,10);
    dot->setStyleSheet(QString("background:%1; border-radius:5px;").arg(color));

    QLabel* label = new QLabel(text);
    label->setStyleSheet("color:#9aa4b2; font-size:11px; background:transparent;");

    l->addWidget(dot);
    l->addWidget(label);

    layout->addWidget(item);
}
