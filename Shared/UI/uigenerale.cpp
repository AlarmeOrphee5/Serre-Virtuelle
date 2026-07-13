#include "uigenerale.h"
#include "theme.h"

#include <QFrame>


void UIGenerale::applyPage(QWidget* widget)
{
    widget->setAttribute(
        Qt::WA_StyledBackground,
        true
        );

    widget->setStyleSheet(
        QString(
            "background:%1;"
            )
            .arg(
                Theme::pageBackground()
                )
        );
}


void UIGenerale::applyCard(QWidget* widget)
{
    widget->setAttribute(
        Qt::WA_StyledBackground,
        true
        );

    widget->setObjectName(
        "CardWidget"
        );

    widget->setStyleSheet(
        QString(R"(
            QWidget#CardWidget {
                background:%1;
                border-radius:%2px;
                border:1px solid %3;
            }
        )")
            .arg(
                Theme::cardBackground()
                )
            .arg(
                Theme::radiusCard()
                )
            .arg(
                Theme::border()
                )
        );
}


void UIGenerale::applyTransparent(QWidget* widget)
{
    widget->setAttribute(
        Qt::WA_StyledBackground,
        true
        );

    widget->setStyleSheet(
        "background:transparent;"
        );
}


void UIGenerale::applyText(QLabel* label,
                           TextStyle style)
{
    QString color;
    int size;


    switch(style)
    {
    case TextStyle::PageTitle:
        color = Theme::textPrimary();
        size = Theme::fontPageTitle();
        break;


    case TextStyle::SectionTitle:
        color = Theme::textPrimary();
        size = Theme::fontSectionTitle();
        break;


    case TextStyle::Value:
        color = Theme::textPrimary();
        size = Theme::fontValue();
        break;


    case TextStyle::Body:
        color = Theme::textPrimary();
        size = Theme::fontBody();
        break;


    case TextStyle::Description:
        color = Theme::textSecondary();
        size = Theme::fontDescription();
        break;


    case TextStyle::Muted:
        color = Theme::textMuted();
        size = Theme::fontMuted();
        break;
    }


    label->setStyleSheet(
        QString(
            "color:%1;"
            "font-size:%2px;"
            "background:transparent;"
            "border:none;"
            )
            .arg(color)
            .arg(size)
        );
}


void UIGenerale::applyButton(QPushButton* button,
                             ButtonStyle style)
{
    switch(style)
    {

    case ButtonStyle::Primary:

        button->setStyleSheet(
            QString(R"(
                QPushButton {
                    background:%1;
                    color:%2;
                    border:none;
                    border-radius:%3px;
                    padding:%4px %5px;
                    font-weight:600;
                }

                QPushButton:hover {
                    background:%6;
                }
            )")
                .arg(
                    Theme::success()
                    )
                .arg(
                    Theme::textPrimary()
                    )
                .arg(
                    Theme::radiusButton()
                    )
                .arg(
                    Theme::spacingSmall()
                    )
                .arg(
                    Theme::spacingLarge()
                    )
                .arg(
                    Theme::successHover()
                    )
            );

        break;



    case ButtonStyle::Secondary:

        button->setStyleSheet(
            QString(R"(
                QPushButton {
                    background:%1;
                    color:%2;
                    border:1px solid %3;
                    border-radius:%4px;
                    padding:%5px %6px;
                }

                QPushButton:hover {
                    background:%7;
                }
            )")
                .arg(
                    Theme::cardBackground()
                    )
                .arg(
                    Theme::textPrimary()
                    )
                .arg(
                    Theme::border()
                    )
                .arg(
                    Theme::radiusButton()
                    )
                .arg(
                    Theme::spacingSmall()
                    )
                .arg(
                    Theme::spacingLarge()
                    )
                .arg(
                    Theme::cardHoverBackground()
                    )
            );

        break;
    }
}


QWidget* UIGenerale::createSeparator()
{
    QFrame* line = new QFrame;

    line->setFrameShape(
        QFrame::HLine
        );

    line->setFixedHeight(
        1
        );

    line->setStyleSheet(
        QString(
            "background:%1;"
            )
            .arg(
                Theme::separator()
                )
        );

    return line;
}

void UIGenerale::applyCheckBox(QCheckBox* checkbox)
{
    checkbox->setStyleSheet(
        QString(R"(
            QCheckBox {
                color:%1;
                spacing:%2px;
            }

            QCheckBox::indicator {
                width:16px;
                height:16px;
            }
        )")
            .arg(
                Theme::textPrimary()
                )
            .arg(
                Theme::spacingSmall()
                )
        );
}

void UIGenerale::applyComboBox(QComboBox* combo)
{
    combo->setStyleSheet(
        QString(R"(
            QComboBox {
                background:%1;
                color:%2;
                border:1px solid %3;
                border-radius:%4px;
                padding:6px;
            }

            QComboBox QAbstractItemView {
                background:%5;
                color:%2;
                selection-background-color:%6;
            }
        )")
            .arg(
                Theme::inputBackground()
                )
            .arg(
                Theme::textPrimary()
                )
            .arg(
                Theme::border()
                )
            .arg(
                Theme::radiusButton()
                )
            .arg(
                Theme::cardBackground()
                )
            .arg(
                Theme::cardHoverBackground()
                )
        );
}

void UIGenerale::applyLineEdit(QLineEdit* edit)
{
    edit->setStyleSheet(
        QString(R"(
            QLineEdit {
                background:%1;
                color:%2;
                border:1px solid %3;
                border-radius:%4px;
                padding:8px;
            }

            QLineEdit:focus {
                border:1px solid %5;
            }
        )")
            .arg(
                Theme::inputBackground()
                )
            .arg(
                Theme::textPrimary()
                )
            .arg(
                Theme::border()
                )
            .arg(
                Theme::radiusButton()
                )
            .arg(
                Theme::success()
                )
        );
}
