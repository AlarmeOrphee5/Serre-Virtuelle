#pragma once

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class UIGenerale
{
public:

    enum class TextStyle
    {
        PageTitle,
        SectionTitle,
        Value,
        Body,
        Description,
        Muted
    };

    enum class ButtonStyle
    {
        Primary,
        Secondary
    };

    static void applyPage(QWidget* widget);

    static void applyCard(QWidget* widget);

    static void applyTransparent(QWidget* widget);

    static void applyText(
        QLabel* label,
        TextStyle style);

    static void applyButton(
        QPushButton* button,
        ButtonStyle style);

    static QWidget* createSeparator();

    static void applyCheckBox(
        QCheckBox* checkbox
        );


    static void applyComboBox(
        QComboBox* combo
        );


    static void applyLineEdit(
        QLineEdit* edit
        );
};
