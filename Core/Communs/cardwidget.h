#pragma once

#include <QWidget>


class QVBoxLayout;


class CardWidget : public QWidget
{
public:

    explicit CardWidget(QWidget* parent = nullptr);


    QVBoxLayout* innerLayout() const;


private:

    QWidget* m_card;
    QVBoxLayout* m_innerLayout;
};
