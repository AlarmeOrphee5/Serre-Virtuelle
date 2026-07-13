#include "sidebar.h"
#include "Core/Communs/appinfo.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>

SideBar::SideBar(QWidget* parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::NoFrame);
    setFixedWidth(220);
    setStyleSheet("background-color:#151922;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(12,12,12,12);
    layout->setSpacing(8);

    setupBrand(layout);

    QFrame* line = new QFrame;
    line->setFrameShape(QFrame::NoFrame);
    line->setFixedHeight(1);
    line->setStyleSheet("background:rgba(255,255,255,0.06);");
    layout->addWidget(line);

    setupNav(layout);

    layout->addStretch();

    setupVersion(layout);
}

void SideBar::setupBrand(QVBoxLayout* layout)
{
    QFrame* brand = new QFrame;
    brand->setFrameShape(QFrame::NoFrame);
    brand->setStyleSheet("background:transparent;");

    QVBoxLayout* brandLayout = new QVBoxLayout(brand);
    brandLayout->setContentsMargins(0,0,0,10);
    brandLayout->setSpacing(4);

    QLabel* icon = new QLabel("🌿");
    icon->setAlignment(Qt::AlignCenter);
    icon->setStyleSheet("font-size:22px; background:transparent;");

    QLabel* title = new QLabel("SERRE");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color:white; font-weight:700; font-size:14px; background:transparent;");

    QLabel* subtitle = new QLabel("VIRTUELLE");
    subtitle->setAlignment(Qt::AlignCenter);
    subtitle->setStyleSheet("color:#5fbf66; font-size:12px; font-weight:600; background:transparent;");

    brandLayout->addWidget(icon);
    brandLayout->addWidget(title);
    brandLayout->addWidget(subtitle);

    layout->addWidget(brand);
}

void SideBar::setupNav(QVBoxLayout* layout)
{
    QString btnStyle = R"(
        QPushButton {
            color:white;
            background:transparent;
            padding:10px;
            text-align:left;
            border-radius:8px;
        }
        QPushButton:hover {
            background-color:#1f2633;
        }
    )";

    QStringList pages = {"Dashboard", "Mes plateaux", "Stats", "Settings"};
    for (const QString& page : pages)
    {
        QPushButton* btn = new QPushButton(page);
        btn->setStyleSheet(btnStyle);

        connect(btn, &QPushButton::clicked, this, [this, page]() {
            emit pageChanged(page);
        });

        layout->addWidget(btn);
    }
}

void SideBar::setupVersion(QVBoxLayout* layout)
{
    QLabel* version = new QLabel(AppInfo::version()+"\n"+AppInfo::build()+"\nSuceptible d'être modifié");
    version->setAlignment(Qt::AlignCenter);
    version->setStyleSheet("color:#5c6370; font-size:11px; padding-top:8px; background:transparent;");
    layout->addWidget(version);
}
