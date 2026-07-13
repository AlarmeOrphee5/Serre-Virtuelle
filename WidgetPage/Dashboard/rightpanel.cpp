#include "rightpanel.h"
#include "Core/Communs/cardwidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

RightPanel::RightPanel(QWidget* parent)
    : QWidget(parent)
{
    setFixedWidth(320);
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("background:transparent;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(12);
    layout->setContentsMargins(0,0,0,0);

    auto createCard = [](const QString& cardTitle)
    {
        CardWidget* c = new CardWidget;

        QLabel* t = new QLabel(cardTitle);
        t->setStyleSheet("color:white; font-weight:600; background:transparent;");

        c->innerLayout()->addWidget(t);
        c->innerLayout()->addStretch();

        return c;
    };

    layout->addWidget(createCard("⚠ Alertes"));
    layout->addWidget(createCard("📋 Tâches"));
    CardWidget* gestionCard = new CardWidget;

    QLabel* gestionTitle = new QLabel("Gestion");
    gestionTitle->setStyleSheet("color:white; font-weight:600; background:transparent;");

    QPushButton* addBtn = new QPushButton("+ Ajouter une table");
    addBtn->setStyleSheet(R"(
    QPushButton {
        background:#5fbf66;
        color:white;
        border:none;
        border-radius:8px;
        padding:10px;
        font-weight:600;
        font-size:12px;
    }
    QPushButton:hover { background:#7ed68a; }
)");

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        emit ajouterTableClicked();
    });

    QPushButton* ExportAllBtn = new QPushButton("Exporter la Serre");
    ExportAllBtn->setStyleSheet(R"(
    QPushButton {
        background:#5fbf66;
        color:white;
        border:none;
        border-radius:8px;
        padding:10px;
        font-weight:600;
        font-size:12px;
    }
    QPushButton:hover { background:#7ed68a; }
)");

    connect(ExportAllBtn, &QPushButton::clicked,
            this, &RightPanel::exportSerreRequested);

    gestionCard->innerLayout()->addWidget(gestionTitle);
    gestionCard->innerLayout()->addWidget(addBtn);
    gestionCard->innerLayout()->addWidget(ExportAllBtn);

    layout->addWidget(gestionCard);
    layout->addStretch();
}
