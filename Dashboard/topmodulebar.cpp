#include "topmodulebar.h"
#include "modulecard.h"
#include "../Shared/UI/uigenerale.h"

#include <QHBoxLayout>
#include <QDebug>

TopModulesBar::TopModulesBar(QWidget* parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::NoFrame);
    UIGenerale::applyTransparent(this);
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

    recupererMeteo();
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

void TopModulesBar::recupererMeteo()
{
    const double latitude  = 48.862725;
    const double longitude = 2.287592;

    QString url =
        QString("https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&current=temperature_2m,relative_humidity_2m")
        .arg(latitude)
        .arg(longitude)
        ;

    QNetworkReply* reply =
        m_networkManager.get(QNetworkRequest(QUrl(url)));

    connect(reply,
            &QNetworkReply::finished,
            this,
            [this, reply]()
            {
                QByteArray data = reply->readAll();

                QJsonDocument doc =
                    QJsonDocument::fromJson(data);

                QJsonObject current =
                    doc.object()["current"].toObject();

                double temperature =
                    current["temperature_2m"].toDouble();

                int humidite =
                    current["relative_humidity_2m"].toInt();

                updateModule(4,QString("%1 °C").arg(temperature, 0, 'f', 1),QString("%1 % humidité").arg(humidite));
                qDebug() << QString("%1 °C").arg(temperature, 0, 'f', 1);

                reply->deleteLater();
            });
}
