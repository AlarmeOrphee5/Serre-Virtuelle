#pragma once

#include "potwidget.h"

#include <QWidget>
#include <QMouseEvent>

class QLabel;
class QPushButton;
class QGridLayout;
class QVBoxLayout;
class QFrame;

class TableCulture : public QWidget
{
    Q_OBJECT

public:
    explicit TableCulture(const QString& name,
                          QWidget *parent = nullptr);
    void setEnabled(bool etat);
    bool estActive() const { return m_enabled; }
    int  nombrePots() const { return m_nombrePot; }
    int  nombrePotsActifs() const;
    void updateStyle();

    // Getters pour TablesPage
    QString         name()  const { return m_name; }
    QVector<PotWidget*> pots() const { return m_pots; }

signals:
    void etatChanged();
    void tableClicked(TableCulture* self);

protected:
    void mousePressEvent(QMouseEvent* e) override;

private:
    void setupUi();
    void setupHeader(QVBoxLayout* mainLayout);
    void setupGrid(QVBoxLayout* mainLayout);
    void setupFooter(QVBoxLayout* mainLayout);

    PotWidget* pot(int index) const;

    QString  m_name;
    QWidget* m_card;
    QFrame*  m_statusDot;
    QLabel*  m_statusLabel;
    QLabel*  m_potsLabel;
    QLabel*  m_waterLabel;

    bool m_enabled;
    int  m_nombrePot;

    QGridLayout*        m_gridLayout;
    QVector<PotWidget*> m_pots;
};
