#pragma once

#include "DataManager/TableCulture/tableculturedata.h"
#include "WidgetPage/Pot/potwidget.h"

#include <QWidget>
#include <QMouseEvent>

class QLabel;
class QGridLayout;
class QVBoxLayout;
class QFrame;


class TableCultureWidget : public QWidget
{
    Q_OBJECT

public:

    explicit TableCultureWidget(TableCultureData& data,
                                QWidget *parent = nullptr);

    // Active/désactive la table (avec randomisation)
    void setEnabled(bool etat);

    bool estActive() const { return m_data.estActive(); }
    int  nombrePots() const { return m_data.nombrePots(); }
    int  nombrePotsActifs() const;

    // Relit m_data et met à jour tous les widgets
    void refresh();

    // Met à jour uniquement le style visuel (carte + labels)
    void updateStyle();

    // Accès données
    TableCultureData& data() const { return m_data; }

    QString name() const { return m_data.name(); }

    QVector<PotWidget*> potWidgets() const { return m_potWidgets; }

    PotWidget* potWidget(int index) const;

signals:

    void etatChanged();
    void tableClicked(TableCultureWidget* self);
    void potClicked(PotWidget* pot);       // ← émis quand un pot est cliqué

protected:

    void mousePressEvent(QMouseEvent* e) override;

private slots:

    void refreshPotCount();

private:

    void setupUi();
    void setupHeader(QVBoxLayout* mainLayout);
    void setupGrid(QVBoxLayout* mainLayout);
    void setupFooter(QVBoxLayout* mainLayout);

    TableCultureData& m_data;

    QWidget* m_card;
    QFrame*  m_statusDot;
    QLabel*  m_statusLabel;
    QLabel*  m_potsLabel;
    QLabel*  m_waterLabel;

    QGridLayout*        m_gridLayout;
    QVector<PotWidget*> m_potWidgets;
};
