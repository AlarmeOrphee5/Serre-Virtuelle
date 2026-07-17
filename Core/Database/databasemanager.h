#pragma once

#include <QString>
#include <QSqlDatabase>

class DatabaseManager
{
public:

    static DatabaseManager& getInstance();
    bool initialize(const QString& databasePath);

    void close();

    bool isOpen() const;

    QSqlDatabase& database();
    bool beginTransaction();

    bool commit();

    bool rollback();

private:

    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    bool createTables();
    bool checkDatabaseVersion();
    int databaseVersion();

    QSqlDatabase m_database;
    static constexpr int CURRENT_SCHEMA_VERSION = 1;
};
