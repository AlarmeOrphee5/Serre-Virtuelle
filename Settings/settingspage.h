#pragma once

#include <QWidget>

class QLabel;
class QComboBox;
class QPushButton;
class QLineEdit;
class QCheckBox;


class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);


private:

    void setupUI();

    void setupHeader();
    void setupAppearance();
    void setupData();
    void setupDashboard();
    void setupAbout();

    void setupConnections();

    void loadSettings();
    void saveSettings();


private:

    // Apparence
    QComboBox* m_themeCombo = nullptr;


    // Données
    QLineEdit* m_databasePath = nullptr;
    QPushButton* m_databaseBrowseButton = nullptr;


    // Export
    QLineEdit* m_exportPath = nullptr;
    QPushButton* m_exportBrowseButton = nullptr;
    QCheckBox* m_openPdfCheck = nullptr;


    // Dashboard
    QCheckBox* m_showStatsCheck = nullptr;
    QCheckBox* m_showInactiveCheck = nullptr;


    // Actions
    QPushButton* m_applyButton = nullptr;
    QPushButton* m_resetButton = nullptr;
};
