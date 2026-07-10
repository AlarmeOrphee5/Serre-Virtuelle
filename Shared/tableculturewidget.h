#pragma once

#include "tableculturedata.h"
#include "potwidget.h"

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


    void setEnabled(bool etat);


    bool estActive() const
    {
        return m_data.estActive();
    }


    int nombrePots() const
    {
        return m_data.nombrePots();
    }


    int nombrePotsActifs() const;


    void updateStyle();
    void refresh();


    // Accès données
    TableCultureData& data()
    {
        return m_data;
    }


    const TableCultureData& data() const
    {
        return m_data;
    }


    // Compatibilité Dashboard / Pages
    QString name() const
    {
        return m_data.name();
    }


    QVector<PotWidget*> potWidgets() const
    {
        return m_potWidgets;
    }


signals:

    void etatChanged();
    void tableClicked(TableCultureWidget* self);


private slots:

    void refreshPotCount();


protected:

    void mousePressEvent(QMouseEvent* e) override;


private:

    void setupUi();
    void setupHeader(QVBoxLayout* mainLayout);
    void setupGrid(QVBoxLayout* mainLayout);
    void setupFooter(QVBoxLayout* mainLayout);


    PotWidget* potWidget(int index) const;



private:

    TableCultureData& m_data;


    QWidget* m_card;

    QFrame* m_statusDot;

    QLabel* m_statusLabel;
    QLabel* m_potsLabel;
    QLabel* m_waterLabel;


    QGridLayout* m_gridLayout;


    QVector<PotWidget*> m_potWidgets;
};
