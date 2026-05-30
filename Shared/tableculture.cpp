#include "tableculture.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QRandomGenerator>

TableCulture::TableCulture(const QString& name, QWidget *parent)
    : QWidget(parent),
    m_name(name),
    m_enabled(false),
    m_nombrePot(24)
{
    setupUi();
    setCursor(Qt::PointingHandCursor);
}

void TableCulture::mousePressEvent(QMouseEvent* e)
{
    emit tableClicked(this);
    QWidget::mousePressEvent(e);
}

void TableCulture::setEnabled(bool etat)
{
    m_enabled = etat;

    QList<EtatPot> etats = tousLesEtats();
    for (PotWidget* pot : std::as_const(m_pots))
    {
        if(pot->etat() == EtatPot::HorsService)   continue;
        if (m_enabled)
        {
            int r = QRandomGenerator::global()->bounded(etats.size());
            pot->setEtat(etats[r]);
        }
        else
        {
            pot->setEtat(EtatPot::Inactif);
        }
        pot->setEnabled(m_enabled);
    }

    updateStyle();
    emit etatChanged();
}

int TableCulture::nombrePotsActifs() const
{
    int count = 0;
    for (PotWidget* p : m_pots)
        if (p->etat() != EtatPot::Inactif && p->etat() != EtatPot::HorsService)
            count++;
    return count;
}

void TableCulture::updateStyle()
{
    if (m_enabled)
    {
        m_card->setStyleSheet(R"(
            QWidget#TableCard {
                background-color: #151922;
                border-radius: 14px;
                border: 1px solid rgba(255,255,255,0.08);
            }
        )");
        m_statusDot->setStyleSheet("background:#5fbf66; border-radius:5px; border:none;");
        m_statusLabel->setText("Actif");
        m_waterLabel->setVisible(true);
    }
    else
    {
        m_card->setStyleSheet(R"(
            QWidget#TableCard {
                background-color: #0f1318;
                border-radius: 14px;
                border: 1px solid rgba(255,255,255,0.02);
            }
        )");
        m_statusDot->setStyleSheet("background:#910707; border-radius:5px; border:none;");
        m_statusLabel->setText("Inactif");
        m_waterLabel->setVisible(false);
    }

    int nombrePotActif = 0;
    for (PotWidget* pot : std::as_const(m_pots))
        if (pot->etat() != EtatPot::Inactif && pot->etat() != EtatPot::HorsService)
            nombrePotActif++;

    m_potsLabel->setText(QString::number(nombrePotActif) + "/" + QString::number(m_nombrePot) + " pots");
}

void TableCulture::setupUi()
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("TableCulture { background: transparent; border: none; }");

    QVBoxLayout* outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->setSpacing(0);

    m_card = new QWidget(this);
    m_card->setAttribute(Qt::WA_StyledBackground, true);
    m_card->setObjectName("TableCard");

    QVBoxLayout* mainLayout = new QVBoxLayout(m_card);
    mainLayout->setContentsMargins(14, 14, 14, 14);
    mainLayout->setSpacing(10);

    outerLayout->addWidget(m_card);

    setupHeader(mainLayout);
    setupGrid(mainLayout);
    setupFooter(mainLayout);

    updateStyle();
}

void TableCulture::setupHeader(QVBoxLayout* mainLayout)
{
    QFrame* header = new QFrame;
    header->setStyleSheet("background:transparent; border:none;");

    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    headerLayout->setContentsMargins(0,0,0,0);

    QLabel* title = new QLabel(m_name);
    title->setAttribute(Qt::WA_OpaquePaintEvent, false);
    title->setAttribute(Qt::WA_NoSystemBackground, true);
    title->setStyleSheet("color:white; font-weight:600; background:transparent; border:none;");

    m_statusDot = new QFrame;
    m_statusDot->setFixedSize(10, 10);

    m_statusLabel = new QLabel;
    m_statusLabel->setAttribute(Qt::WA_OpaquePaintEvent, false);
    m_statusLabel->setAttribute(Qt::WA_NoSystemBackground, true);
    m_statusLabel->setStyleSheet("color:#9aa4b2; font-size:11px; background:transparent; border:none;");

    QWidget* statusWidget = new QWidget;
    statusWidget->setAttribute(Qt::WA_StyledBackground, true);
    statusWidget->setStyleSheet("background:transparent; border:none;");

    QHBoxLayout* statusLayout = new QHBoxLayout(statusWidget);
    statusLayout->setContentsMargins(0,0,0,0);
    statusLayout->setSpacing(6);
    statusLayout->addWidget(m_statusDot);
    statusLayout->addWidget(m_statusLabel);

    headerLayout->addWidget(title);
    headerLayout->addStretch();
    headerLayout->addWidget(statusWidget);

    mainLayout->addWidget(header);
}

void TableCulture::setupGrid(QVBoxLayout* mainLayout)
{
    QWidget* gridBox = new QWidget;
    gridBox->setAttribute(Qt::WA_StyledBackground, true);
    gridBox->setObjectName("GridBox");
    gridBox->setStyleSheet(R"(
        QWidget#GridBox {
            background-color: #101827;
            border-radius: 12px;
            border: 1px solid rgba(255,255,255,0.05);
        }
    )");

    QVBoxLayout* gridBoxLayout = new QVBoxLayout(gridBox);
    gridBoxLayout->setContentsMargins(8,8,8,8);

    m_gridLayout = new QGridLayout;
    m_gridLayout->setSpacing(6);
    m_gridLayout->setAlignment(Qt::AlignCenter);

    for (int i = 0; i < m_nombrePot; i++)
    {
        PotWidget* pot = new PotWidget(i + 1, EtatPot::Inactif);
        pot->setEnabled(false);
        m_pots.append(pot);
        //m_gridLayout->addWidget(pot, i / 6, i % 6);
        m_gridLayout->addWidget(pot, i / 4, i % 4);
    }

    gridBoxLayout->addLayout(m_gridLayout);
    mainLayout->addWidget(gridBox);
}

void TableCulture::setupFooter(QVBoxLayout* mainLayout)
{
    QWidget* footer = new QWidget;
    footer->setAttribute(Qt::WA_StyledBackground, true);
    footer->setStyleSheet("background:transparent; border:none;");

    QHBoxLayout* footerLayout = new QHBoxLayout(footer);
    footerLayout->setContentsMargins(0,0,0,0);

    m_potsLabel = new QLabel("0/" + QString::number(m_nombrePot) + " pots");
    m_potsLabel->setAttribute(Qt::WA_OpaquePaintEvent, false);
    m_potsLabel->setAttribute(Qt::WA_NoSystemBackground, true);
    m_potsLabel->setStyleSheet("color:#9aa4b2; font-size:11px; background:transparent; border:none;");

    m_waterLabel = new QLabel("Arrosé le : 21/05/2026");
    m_waterLabel->setAttribute(Qt::WA_OpaquePaintEvent, false);
    m_waterLabel->setAttribute(Qt::WA_NoSystemBackground, true);
    m_waterLabel->setStyleSheet("color:#9aa4b2; font-size:11px; background:transparent; border:none;");

    footerLayout->addWidget(m_potsLabel);
    footerLayout->addStretch();
    footerLayout->addWidget(m_waterLabel);

    mainLayout->addWidget(footer);
}

PotWidget* TableCulture::pot(int index) const
{
    if (index < 0 || index >= m_pots.size())
        return nullptr;
    return m_pots[index];
}
