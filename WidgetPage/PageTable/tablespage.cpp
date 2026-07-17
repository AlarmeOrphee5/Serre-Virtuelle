#include "tablespage.h"
#include "Core/Communs/couleurconversion.h"
#include "Core/Database/tableculturerepository.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QScrollArea>

// =========================
// HELPERS
// =========================
static QLabel* makeLabel(const QString& text, const QString& style)
{
    QLabel* l = new QLabel(text);
    l->setStyleSheet(style + " background:transparent;");
    return l;
}

static QWidget* makeSeparator()
{
    QFrame* f = new QFrame;
    f->setFrameShape(QFrame::HLine);
    f->setFixedHeight(1);
    f->setStyleSheet("background:rgba(255,255,255,0.06); border:none;");
    return f;
}

static QWidget* makeCard(const QString& objectName)
{
    QWidget* w = new QWidget;
    w->setAttribute(Qt::WA_StyledBackground, true);
    w->setObjectName(objectName);
    w->setAutoFillBackground(true);
    w->setStyleSheet(QString("QWidget#%1 { background-color:#151922; border-radius:14px; border:1px solid rgba(255,255,255,0.07); }").arg(objectName));
    return w;
}

// =========================
// CONSTRUCTOR
// =========================
TablesPage::TablesPage(QWidget* parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("TablesPage { background:transparent; }");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(0);

    setupHeader(layout);
    setupTabs(layout);
    setupBody(layout);
}

// =========================
// loadTable — point d'entrée
// =========================

void TablesPage::loadTable(TableCultureWidget* widget)
{
    if(!widget)
        return;

    m_table = &widget->data();

    m_currentPot = nullptr;

    refreshInfos();
    refreshHeader();
    refreshGrid();
    refreshPotPanel();
}

void TablesPage::refreshHeader()
{
    if (!m_table) return;

    m_titleLabel->setText(m_table->name());
    m_breadcrumbTable->setText(m_table->name());

    if (m_table->estActive())
    {
        m_badgeLabel->setText("Active");
        m_badgeLabel->setStyleSheet(R"(
            color:#5fbf66;
            background:rgba(95,191,102,0.15);
            border:1px solid rgba(95,191,102,0.3);
            border-radius:6px;
            padding:2px 10px;
            font-size:11px;
            font-weight:600;
        )");
        m_toggleTableBtn->setText("⏸ Désactiver");
    }
    else
    {
        m_badgeLabel->setText("Inactive");
        m_badgeLabel->setStyleSheet(R"(
            color:#910707;
            background:rgba(145,7,7,0.15);
            border:1px solid rgba(145,7,7,0.3);
            border-radius:6px;
            padding:2px 10px;
            font-size:11px;
            font-weight:600;
        )");
        m_toggleTableBtn->setText("▶ Activer");
    }

}

void TablesPage::refreshPotPanel()
{
    // Aucun pot sélectionné -> on cache le panneau
    if (!m_currentPot || !m_table)
    {
        m_potDetailPanel->setVisible(false);
        return;
    }

    m_potDetailPanel->setVisible(true);

    // Activation / désactivation suivant l'état de la table
    bool enabled = m_table->estActive();
    m_potDetailPanel->setEnabled(enabled);

    for (QPushButton* btn : std::as_const(m_etatButtons))
    {
        btn->setEnabled(enabled);
        btn->setChecked(false);
    }

    // Remplissage des informations
    m_potDetailNumero->setText(
        "Détails du pot " + QString::number(m_currentPot->numeroPot()));

    m_potDetailNom->setText(
        m_currentPot->nomPlante().isEmpty()
            ? "Vide"
            : m_currentPot->nomPlante());

    m_potDetailDate->setText(
        m_currentPot->datePlantation().isEmpty()
            ? "—"
            : m_currentPot->datePlantation());

    // Sélection du bon état
    for (auto it = m_buttonToEtat.begin(); it != m_buttonToEtat.end(); ++it)
    {
        if (it.value() == m_currentPot->etat())
        {
            it.key()->setChecked(true);
            break;
        }
    }
}

void TablesPage::clearPotSelection()
{
    m_currentPot = nullptr;

    if (m_potDetailPanel)
        m_potDetailPanel->setVisible(false);

    for (QPushButton* btn : std::as_const(m_etatButtons))
        btn->setChecked(false);
}

void TablesPage::refreshGrid()
{
    if (!m_table)
        return;

    // Vider l'ancienne grille
    QLayoutItem* item;
    while ((item = m_potGrid->takeAt(0)) != nullptr)
    {
        if (item->widget())
            item->widget()->setParent(nullptr);

        delete item;
    }


    const QVector<PotData>& pots = m_table->pots();

    for (int i = 0; i < pots.size() && i < 24; i++)
    {
        QPushButton* potBtn = new QPushButton(
            QString("%1").arg(i + 1, 2, 10, QChar('0'))
            );


        connect(potBtn, &QPushButton::clicked, this, [this, i]()
                {
                    showPotDetail(i);
                });


        potBtn->setFixedSize(44, 44);

        potBtn->setStyleSheet(QString(R"(
            QPushButton {
                background:%1;
                border-radius:22px;
                border:2px solid rgba(255,255,255,0.1);
                color:white;
                font-size:10px;
                font-weight:600;
            }

            QPushButton:hover {
                border:2px solid white;
            }
        )")
                                  .arg(colorFromEtat(pots[i].etat())));


        potBtn->setToolTip(pots[i].toString());

        m_potGrid->addWidget(
            potBtn,
            i / 4,
            (i % 4) + 1
            );
    }
}

void TablesPage::refreshInfos()
{
    if (!m_table) return;

    m_infoNom->setText(m_table->name());
    m_infoStatut->setText(m_table->estActive() ? "● Active" : "● Inactive");
    m_infoStatut->setStyleSheet(QString("color:%1; background:rgba(%2,0.1); border:1px solid rgba(%2,0.25); border-radius:5px; padding:2px 8px; font-size:12px;")
                                    .arg(m_table->estActive() ? "#5fbf66" : "#910707")
                                    .arg(m_table->estActive() ? "95,191,102" : "145,7,7"));
    m_infoPotsCount->setText(QString("⊞  %1 (6x4)").arg(m_table->nombrePots()));
}

// =========================
// HEADER
// =========================
void TablesPage::setupHeader(QVBoxLayout* layout)
{
    QWidget* header = new QWidget;
    header->setAttribute(Qt::WA_StyledBackground, true);
    header->setStyleSheet("background:transparent;");

    QVBoxLayout* vl = new QVBoxLayout(header);
    vl->setContentsMargins(0,0,0,16);
    vl->setSpacing(6);

    // Breadcrumb
    QWidget* breadcrumb = new QWidget;
    breadcrumb->setStyleSheet("background:transparent;");
    QHBoxLayout* bl = new QHBoxLayout(breadcrumb);
    bl->setContentsMargins(0,0,0,0);
    bl->setSpacing(6);

    auto crumb = [](const QString& t, bool active = false) {
        QLabel* l = new QLabel(t);
        l->setStyleSheet(QString("color:%1; font-size:12px; background:transparent;")
                             .arg(active ? "#9aa4b2" : "#5c6370"));
        return l;
    };

    bl->addWidget(crumb("Dashboard"));
    bl->addWidget(crumb(" > "));
    bl->addWidget(crumb("Mes plateaux"));
    bl->addWidget(crumb(" > "));

    m_breadcrumbTable = crumb("—", true);
    bl->addWidget(m_breadcrumbTable);
    bl->addStretch();

    // Titre + badge + actions
    QWidget* titleRow = new QWidget;
    titleRow->setStyleSheet("background:transparent;");
    QHBoxLayout* tl = new QHBoxLayout(titleRow);
    tl->setContentsMargins(0,0,0,0);
    tl->setSpacing(12);

    // Bouton retour
    QPushButton* backBtn = new QPushButton("←");
    backBtn->setFixedSize(32, 32);
    backBtn->setStyleSheet(R"(
        QPushButton { background:#1f2633; color:white; border-radius:8px; border:none; font-size:14px; }
        QPushButton:hover { background:#2a3444; }
    )");
    connect(backBtn, &QPushButton::clicked, this, &TablesPage::backRequested);

    m_titleLabel = new QLabel("—");
    m_titleLabel->setStyleSheet("color:white; font-size:22px; font-weight:700; background:transparent;");

    m_badgeLabel = new QLabel;

    tl->addWidget(backBtn);
    tl->addWidget(m_titleLabel);
    tl->addWidget(m_badgeLabel);
    tl->addStretch();

    auto makeActionBtn = [this](const QString& icon, const QString& text, bool primary = false) {
        QPushButton* b = new QPushButton(icon + "  " + text);
        b->setStyleSheet(primary ? R"(
            QPushButton { background:#5fbf66; color:white; border:none; border-radius:8px; padding:8px 16px; font-weight:600; font-size:12px; }
            QPushButton:hover { background:#7ed68a; }
        )" : R"(
            QPushButton { background:#1f2633; color:white; border:1px solid rgba(255,255,255,0.1); border-radius:8px; padding:8px 16px; font-size:12px; }
            QPushButton:hover { background:#2a3444; }
        )");
        return b;
    };
    m_toggleTableBtn = makeActionBtn("", "Init");
    QObject::connect(m_toggleTableBtn, &QPushButton::clicked, m_toggleTableBtn, [=](){
        qDebug() << QString("Bouton %1 appuyé").arg(m_toggleTableBtn->text());
        toggleTableState();
    });
    tl->addWidget(m_toggleTableBtn);
    tl->addWidget(makeActionBtn("✓", "Enregistrer", true));

    vl->addWidget(breadcrumb);
    vl->addWidget(titleRow);

    layout->addWidget(header);
    layout->addWidget(makeSeparator());
}

// =========================
// ONGLETS
// =========================
void TablesPage::setupTabs(QVBoxLayout* layout)
{
    QWidget* tabBar = new QWidget;
    tabBar->setStyleSheet("background:transparent;");
    QHBoxLayout* tl = new QHBoxLayout(tabBar);
    tl->setContentsMargins(0, 12, 0, 0);
    tl->setSpacing(0);

    //QStringList tabs  = {"Vue d'ensemble", "Configuration", "Nutrition / Eau", "Historique", "Notes"};
    //QStringList icons = {"⊞", "⚙", "💧", "📋", "📝"};

    QStringList tabs  = {"Vue d'ensemble", "Historique", "Notes"};
    QStringList icons = {"⊞", "📋", "📝"};

    for (int i = 0; i < tabs.size(); i++)
    {
        QPushButton* tab = new QPushButton(icons[i] + "  " + tabs[i]);
        bool active = (i == 0);
        tab->setStyleSheet(active ? R"(
            QPushButton { color:white; background:transparent; border:none; border-bottom:2px solid #5fbf66; padding:10px 18px; font-size:13px; font-weight:600; }
        )" : R"(
            QPushButton { color:#5c6370; background:transparent; border:none; border-bottom:2px solid transparent; padding:10px 18px; font-size:13px; }
            QPushButton:hover { color:#9aa4b2; }
        )");
        tl->addWidget(tab);
    }
    tl->addStretch();

    layout->addWidget(tabBar);
    layout->addWidget(makeSeparator());
    layout->addSpacing(16);
}

// =========================
// CORPS
// =========================
void TablesPage::setupBody(QVBoxLayout* layout)
{
    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("border:none; background:transparent;");
    scroll->viewport()->setStyleSheet("background:transparent;");
    scroll->viewport()->setAttribute(Qt::WA_NoSystemBackground, true);

    QWidget* body = new QWidget;
    body->setAttribute(Qt::WA_NoSystemBackground, true);
    body->setStyleSheet("background:transparent;");

    QHBoxLayout* bodyLayout = new QHBoxLayout(body);
    bodyLayout->setContentsMargins(0,0,0,0);
    bodyLayout->setSpacing(16);

    // =========================
    // COLONNE GAUCHE
    // =========================
    QWidget* leftCol = new QWidget;
    leftCol->setStyleSheet("background:transparent;");
    QVBoxLayout* leftLayout = new QVBoxLayout(leftCol);
    leftLayout->setContentsMargins(0,0,0,0);
    leftLayout->setSpacing(16);

    // Carte grille de pots
    QWidget* gridCard = makeCard("GridCard");
    QVBoxLayout* gcl = new QVBoxLayout(gridCard);
    gcl->setContentsMargins(16,16,16,16);
    gcl->setSpacing(12);

    QWidget* gcHeader = new QWidget;
    gcHeader->setStyleSheet("background:transparent;");
    QHBoxLayout* gchl = new QHBoxLayout(gcHeader);
    gchl->setContentsMargins(0,0,0,0);
    gchl->addWidget(makeLabel("Aperçu de la table", "color:white; font-size:15px; font-weight:600;"));
    gchl->addWidget(makeLabel("24 pots (6x4)", "color:#5c6370; font-size:11px;"));

    //essaie non pertinant pour mettre a jour le nombre de pots via lz donnée stocké et non ecrite en dur.
    gchl->addStretch();

    QPushButton* modBtn = new QPushButton("✎  Modifier");
    modBtn->setStyleSheet(R"(
        QPushButton { background:#1f2633; color:#9aa4b2; border:1px solid rgba(255,255,255,0.1); border-radius:7px; padding:6px 12px; font-size:11px; }
        QPushButton:hover { background:#2a3444; }
    )");
    gchl->addWidget(modBtn);
    gcl->addWidget(gcHeader);

    // Grille — sera remplie par refreshGrid()
    m_potGridContainer = new QWidget;
    m_potGridContainer->setStyleSheet("background:transparent;");
    m_potGrid = new QGridLayout(m_potGridContainer);
    m_potGrid->setSpacing(8);
    m_potGrid->setContentsMargins(0,0,0,0);

    gcl->addWidget(m_potGridContainer);

    // Légende
    QWidget* legendRow = new QWidget;
    legendRow->setStyleSheet("background:transparent;");
    QHBoxLayout* ll = new QHBoxLayout(legendRow);
    ll->setContentsMargins(0,4,0,0);
    ll->setSpacing(16);

    auto addLegItem = [&](const QString& color, const QString& text) {
        QWidget* item = new QWidget;
        item->setStyleSheet("background:transparent;");
        QHBoxLayout* il = new QHBoxLayout(item);
        il->setContentsMargins(0,0,0,0);
        il->setSpacing(5);
        QFrame* dot = new QFrame;
        dot->setFixedSize(8,8);
        dot->setStyleSheet(QString("background:%1; border-radius:4px;").arg(color));
        il->addWidget(dot);
        il->addWidget(makeLabel(text, "color:#9aa4b2; font-size:11px;"));
        ll->addWidget(item);
    };

    QList<EtatPot> etats = tousLesEtats();
    for (EtatPot etat : tousLesEtats())
        addLegItem(colorFromEtat(etat), labelFromEtat(etat));
    ll->addStretch();
    gcl->addWidget(legendRow);

    // =========================
    // DETAIL DU POT CADRE
    // =========================
    m_potDetailPanel = makeCard("PotDetailCard");
    m_potDetailPanel->setMinimumWidth(320);
    m_potDetailPanel->setMaximumWidth(500);
    m_potDetailPanel->setVisible(false); // caché au départ

    QVBoxLayout* detailsLayout = new QVBoxLayout(m_potDetailPanel);
    detailsLayout->setContentsMargins(20, 20, 20, 20);
    detailsLayout->setSpacing(14);

    // =====================
    // TITRE
    // =====================
    m_potDetailNumero = new QLabel("Détails du pot");
    m_potDetailNumero->setObjectName("detailsTitle");

    detailsLayout->addWidget(m_potDetailNumero);
    detailsLayout->addSpacing(20);

    // =====================
    // PLANTE
    // =====================
    QLabel* planteLabel = new QLabel("Plante");
    planteLabel->setObjectName("sectionLabel");

    m_potDetailNom = new QLabel("—");
    m_potDetailNom->setObjectName("valueLabel");

    detailsLayout->addWidget(planteLabel);
    detailsLayout->addWidget(m_potDetailNom);

    // =====================
    // DATE
    // =====================
    QLabel* dateLabel = new QLabel("Date plantation");
    dateLabel->setObjectName("sectionLabel");

    m_potDetailDate = new QLabel("—");
    m_potDetailDate->setObjectName("valueLabel");

    detailsLayout->addWidget(dateLabel);
    detailsLayout->addWidget(m_potDetailDate);

    // =====================
    // ETAT (optionnel mais utile)
    // =====================
    QLabel* etatLabel = new QLabel("État");
    etatLabel->setObjectName("sectionLabel");
    detailsLayout->addWidget(etatLabel);

    // Mise en forme de l'UI
    m_potDetailPanel->setStyleSheet(R"(
QWidget#PotDetailCard {
    background-color:#151922;
    border:1px solid rgba(255,255,255,0.07);
    border-radius:14px;
}

QLabel#detailsTitle {
    color: white;
    font-size: 20px;
    font-weight: bold;
}

QLabel#sectionLabel {
    color: #8B949E;
    font-size: 13px;
    font-weight: 600;
}

QLabel#valueLabel {
    color: white;
    font-size: 17px;
    font-weight: 500;
    background-color: #2B2D31;
    border-radius: 10px;
    padding: 10px;
}
)");

    // reset
    m_etatButtons.clear();
    m_buttonToEtat.clear();

    m_etatGroup = new QButtonGroup(this);
    m_etatGroup->setExclusive(true);

    QGridLayout* etatLayout = new QGridLayout();
    etatLayout->setSpacing(8);
    etatLayout->setContentsMargins(0, 0, 0, 0);

    // FACTORY bouton
    auto makeBtn = [](const QString& text, const QString& color) {
        QPushButton* b = new QPushButton(text);
        b->setCheckable(true);
        b->setStyleSheet(QString(R"(
        QPushButton {
            background: rgba(255,255,255,0.04);
            border: 1px solid rgba(255,255,255,0.08);
            border-radius: 10px;
            padding: 10px;
            color: white;
            font-size: 12px;
        }
        QPushButton:checked {
            background: %1;
            border: 2px solid white;
            font-weight: bold;
        }
        QPushButton:hover {
            border: 1px solid rgba(255,255,255,0.25);
        }
    )").arg(color));
        return b;
    };

    // création dynamique depuis ton enum
    int id = 0;
    for (const EtatPot& etat : etats)
    {
        QString label = labelFromEtat(etat);
        QString color = colorFromEtat(etat);

        QPushButton* btn = makeBtn(label, color);

        m_etatGroup->addButton(btn, id);
        m_buttonToEtat[btn] = etat;

        m_etatButtons.push_back(btn);
        //etatLayout->addWidget(btn);

        id++;
    }

    int row = 0;
    int col = 0;

    for (int i = 0; i < m_etatButtons.size(); i++)
    {
        QPushButton* btn = m_etatButtons[i];

        etatLayout->addWidget(btn, row, col);

        col++;
        if (col >= 4)
        {
            col = 0;
            row++;
        }
    }

    detailsLayout->addLayout(etatLayout);

    // =========================
    // CONNECT (UNE SEULE FOIS)
    // =========================
    connect(m_etatGroup, &QButtonGroup::idClicked, this, [=](int id)
            {
                if (!m_currentPot)
                    return;


                QPushButton* btn = m_etatButtons.value(id);

                if (!btn)
                    return;


                EtatPot newEtat =
                    m_buttonToEtat[btn];


                m_currentPot->setEtat(newEtat);


                PotRepository repository;


                if(!repository.save(*m_currentPot, m_table->id()))
                {
                    qDebug()
                    << "[BDD] Impossible de sauvegarder le pot";

                    return;
                }


                refreshGrid();
                refreshPotPanel();


                emit tableUpdated(
                    m_table->id()
                    );
            });

    detailsLayout->addStretch();

    // =========================
    // EMPILEMENT DES COUCHES D'OBJECT
    // =========================
    leftLayout->addWidget(gridCard);
    leftLayout->addWidget(m_potDetailPanel);
    leftLayout->addStretch();

    // =========================
    // COLONNE DROITE
    // =========================
    QWidget* rightCol = new QWidget;
    rightCol->setFixedWidth(340);
    rightCol->setStyleSheet("background:transparent;");
    QVBoxLayout* rightLayout = new QVBoxLayout(rightCol);
    rightLayout->setContentsMargins(0,0,0,0);
    rightLayout->setSpacing(16);

    // Carré infos de la table
    QWidget* infoCard = makeCard("InfoCard");
    QVBoxLayout* infl = new QVBoxLayout(infoCard);
    infl->setContentsMargins(16,16,16,16);
    infl->setSpacing(14);

    infl->addWidget(makeLabel("Informations de la table", "color:white; font-size:15px; font-weight:600;"));

    // Nom + statut
    QWidget* nomRow = new QWidget;
    nomRow->setStyleSheet("background:transparent;");
    QHBoxLayout* nrl = new QHBoxLayout(nomRow);
    nrl->setContentsMargins(0,0,0,0);
    nrl->setSpacing(8);

    QWidget* nomLeft = new QWidget;
    nomLeft->setStyleSheet("background:transparent;");
    QVBoxLayout* nll = new QVBoxLayout(nomLeft);
    nll->setContentsMargins(0,0,0,0);
    nll->setSpacing(3);
    nll->addWidget(makeLabel("Nom", "color:#5c6370; font-size:11px;"));
    m_infoNom = makeLabel("—", "color:white; font-size:13px;");
    nll->addWidget(m_infoNom);
    nrl->addWidget(nomLeft, 1);

    QWidget* statRight = new QWidget;
    statRight->setStyleSheet("background:transparent;");
    QVBoxLayout* srl = new QVBoxLayout(statRight);
    srl->setContentsMargins(0,0,0,0);
    srl->setSpacing(3);
    srl->addWidget(makeLabel("Statut", "color:#5c6370; font-size:11px;"));
    m_infoStatut = new QLabel("—");
    srl->addWidget(m_infoStatut);
    nrl->addWidget(statRight, 1);
    infl->addWidget(nomRow);

    // Nombre de pots
    QWidget* potsRow = new QWidget;
    potsRow->setStyleSheet("background:transparent;");
    QVBoxLayout* prl = new QVBoxLayout(potsRow);
    prl->setContentsMargins(0,0,0,0);
    prl->setSpacing(3);
    prl->addWidget(makeLabel("Nombre de pots", "color:#5c6370; font-size:11px;"));
    m_infoPotsCount = makeLabel("—", "color:white; font-size:13px;");
    prl->addWidget(m_infoPotsCount);
    infl->addWidget(potsRow);

    rightLayout->addWidget(infoCard);

    //Carré Actions rapides
    QWidget* actCard = makeCard("ActCard");
    QVBoxLayout* actl = new QVBoxLayout(actCard);
    actl->setContentsMargins(16,16,16,16);
    actl->setSpacing(10);

    actl->addWidget(makeLabel("Actions rapides", "color:white; font-size:15px; font-weight:600;"));

    QGridLayout* actGrid = new QGridLayout;
    actGrid->setSpacing(8);

    auto makeActBtn = [](const QString& icon, const QString& text, bool danger = false) {
        QPushButton* b = new QPushButton(icon + "  " + text);
        b->setStyleSheet(danger ? R"(
            QPushButton { background:rgba(231,76,60,0.1); color:#e74c3c; border:1px solid rgba(231,76,60,0.2); border-radius:8px; padding:10px; font-size:12px; }
            QPushButton:hover { background:rgba(231,76,60,0.2); }
        )" : R"(
            QPushButton { background:rgba(255,255,255,0.04); color:white; border:1px solid rgba(255,255,255,0.08); border-radius:8px; padding:10px; font-size:12px; }
            QPushButton:hover { background:rgba(255,255,255,0.08); }
        )");
        return b;
    };

    //actGrid->addWidget(makeActBtn("+",  "Ajouter des pots"),    0, 0);
    //actGrid->addWidget(makeActBtn("💧", "Planifier irrigation"), 0, 1);
    //actGrid->addWidget(makeActBtn("⧉",  "Dupliquer la table"),  1, 0);
    QPushButton* exportBtn = makeActBtn("↓", "Exporter les données");
    connect(exportBtn, &QPushButton::clicked,
            this, &TablesPage::exportPDF);

    actGrid->addWidget(exportBtn, 1, 1);
    actl->addLayout(actGrid);

    this->m_duplicateTableBtn = makeActBtn("⧉", "Dupliquer la table", true);
    QObject::connect(m_duplicateTableBtn, &QPushButton::clicked, m_duplicateTableBtn, [=](){
        qDebug() << QString("Bouton %1 appuyé").arg(m_duplicateTableBtn->text());
        emit duplicateRequested(m_table);
        emit backRequested();
    });
    actl->addWidget(m_duplicateTableBtn);

    this->m_deleteTableBtn = makeActBtn("🗑", "Supprimer la table", true);
    m_deleteTableBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QObject::connect(m_deleteTableBtn, &QPushButton::clicked, m_deleteTableBtn, [=](){
        qDebug() << QString("Bouton %1 appuyé").arg(m_deleteTableBtn->text());
        emit deleteRequested(m_table->id());
        emit backRequested();  // ← retour automatique au dashboard
    });
    actl->addWidget(m_deleteTableBtn);

    //Montage de la view
    rightLayout->addWidget(actCard);
    rightLayout->addStretch();

    bodyLayout->addWidget(leftCol, 1); //Affichage complet pots
    bodyLayout->addWidget(rightCol); //action et infos rapides

    scroll->setWidget(body);
    layout->addWidget(scroll, 1);
}

//Fonction pour le bouton activer/désactiver et les changements de states
void TablesPage::toggleTableState()
{
    if (!m_table)
        return;

    TableCultureRepository repository;

    m_table->setActive(!m_table->estActive());

    if(!repository.save(*m_table))
    {
        qDebug() << "[BDD] Impossible de sauvegarder la table";
        return;
    }

    emit tableUpdated(m_table->id());

    refreshGrid();
    refreshInfos();
    refreshHeader();
    refreshPotPanel();
}

void TablesPage::showPotDetail(int index)
{
    if (!m_table)
        return;


    QVector<PotData>& pots = m_table->pots();


    if (index < 0 || index >= pots.size())
        return;


    m_currentPot = &pots[index];

    refreshPotPanel();
}

void TablesPage::exportPDF()
{
    if (!m_tablesData)
    {
        QMessageBox::warning(
            this,
            "Erreur",
            "Aucune donnée disponible pour l'export."
            );
        return;
    }


    QString chemin = QFileDialog::getSaveFileName(
        this,
        "Exporter la table",
        m_table->name() + ".pdf",
        "PDF (*.pdf)");


    if(!chemin.isEmpty())
    {
        PdfExporter::exporterTable(
            *m_table,
            chemin);
    }
    else
    {
        QMessageBox::warning(
            window(),
            "Erreur",
            "Impossible de créer le PDF."
            );
    }
}
void TablesPage::setTablesData(QVector<TableCultureData*>* data)
{
    m_tablesData = data;
}
