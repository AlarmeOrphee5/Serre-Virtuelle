#include "topmodulebar.h"
#include "modulecard.h"

#include <QHBoxLayout>

TopModulesBar::TopModulesBar(QWidget* parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::NoFrame);
    setStyleSheet("background:transparent;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,10,0,10);
    layout->setSpacing(12);

    // Définition des 5 modules
    addModule({ "🌿", "Tables actives",  "12",  "sur 17 tables"   });
    addModule({ "🪴", "Pots utilisés",   "87",  "sur 204 pots"    });
    addModule({ "💧", "Taux germination",       "80%",   ""     });
    addModule({ "⚠️",  "Alertes",         "2",   "en attente"      });
    addModule({ "📋", "Meteo",          "25.0 C",   ""         });
}

void TopModulesBar::addModule(const ModuleInfo& info)
{
    ModuleCard* card = new ModuleCard(info);
    m_cards.append(card);

    static_cast<QHBoxLayout*>(layout())->addWidget(card, 1);
}

void TopModulesBar::updateModule(int index, const QString& value, const QString& subtitle)
{
    if (index >= 0 && index < m_cards.size())
    {
        m_cards[index]->setValue(value);
        if (!subtitle.isEmpty())
            m_cards[index]->setSubtitle(subtitle);
    }
}
