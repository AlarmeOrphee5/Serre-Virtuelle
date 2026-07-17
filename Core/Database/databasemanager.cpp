#include "databasemanager.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager& DatabaseManager::getInstance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager()
{
}

DatabaseManager::~DatabaseManager()
{
}

bool DatabaseManager::initialize(const QString& databasePath)
{
    if (m_database.isOpen())
        return true;


    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName(databasePath);


    if (!m_database.open())
    {
        qDebug()
        << "Impossible d'ouvrir la base :"
        << m_database.lastError().text();

        return false;
    }


    qDebug() << "Base ouverte :" << databasePath;

    QSqlQuery query(m_database);

    if(!query.exec("PRAGMA foreign_keys = ON"))
    {
        qDebug()
        << "[BDD] Impossible d'activer les clés étrangères :"
        << query.lastError().text();

        return false;
    }


    if (!createTables())
        return false;


    if (!checkDatabaseVersion())
        return false;



    return true;
}

void DatabaseManager::close()
{
    if (!m_database.isOpen())
        return;

    QString connectionName = m_database.connectionName();

    m_database.close();
    m_database = QSqlDatabase();

    QSqlDatabase::removeDatabase(connectionName);

    qDebug() << "Connexion SQLite fermée";
}

bool DatabaseManager::isOpen() const
{
    return m_database.isOpen();
}

QSqlDatabase& DatabaseManager::database()
{
    return m_database;
}

bool DatabaseManager::createTables()
{
    QSqlQuery query(m_database);

    //
    // ============================================================
    // Table : app_info
    // ============================================================
    //

    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS app_info
        (
            id INTEGER PRIMARY KEY,
            schema_version INTEGER NOT NULL,
            created_at TEXT NOT NULL
        )
    )"))
    {
        qDebug() << "[BDD] Impossible de créer la table app_info :"
                 << query.lastError().text();

        return false;
    }

    query.exec(QString(R"(
        INSERT INTO app_info(schema_version, created_at)
        SELECT %1, datetime('now')
        WHERE NOT EXISTS
        (
            SELECT 1 FROM app_info
        )
    )").arg(CURRENT_SCHEMA_VERSION));

    qDebug() << "[BDD] Table app_info vérifiée.";


    //
    // ============================================================
    // Table : table_culture
    // ============================================================
    //

    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS table_culture
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,

            numero INTEGER NOT NULL,

            nom TEXT NOT NULL,

            active INTEGER NOT NULL,

            date_creation TEXT NOT NULL
        )
    )"))
    {
        qDebug() << "[BDD] Impossible de créer la table table_culture :"
                 << query.lastError().text();

        return false;
    }

    qDebug() << "[BDD] Table table_culture vérifiée.";


    //
    // ============================================================
    // Table : pot
    // ============================================================
    //

    if (!query.exec(R"(
CREATE TABLE IF NOT EXISTS pot
        (
            id INTEGER PRIMARY KEY AUTOINCREMENT,

            table_id INTEGER NOT NULL,

            numero_pot INTEGER NOT NULL,

            etat INTEGER NOT NULL DEFAULT 0,

            nom_plante TEXT,

            date_plantation TEXT,

            FOREIGN KEY(table_id)
            REFERENCES table_culture(id)
            ON DELETE CASCADE
        )
    )"))
    {
        qDebug() << "[BDD] Impossible de créer la table pot :"
                 << query.lastError().text();

        return false;
    }

    qDebug() << "[BDD] Table pot vérifiée.";

    return true;
}

int DatabaseManager::databaseVersion()
{
    QSqlQuery query(m_database);


    if (!query.exec(
            "SELECT schema_version FROM app_info LIMIT 1"
            ))
    {
        qDebug()
        << "Impossible de lire la version BDD :"
        << query.lastError().text();

        return -1;
    }


    if (query.next())
    {
        return query.value(0).toInt();
    }


    return -1;
}

bool DatabaseManager::checkDatabaseVersion()
{
    int version = databaseVersion();


    if (version == -1)
        return false;


    qDebug()
        << "Version BDD actuelle :"
        << version;


    if (version < CURRENT_SCHEMA_VERSION)
    {
        qDebug()
        << "Migration nécessaire";

        // migrations plus tard
    }


    return true;
}

bool DatabaseManager::beginTransaction()
{
    if(!m_database.transaction())
    {
        qDebug()
        << "[BDD] Impossible de démarrer la transaction";

        return false;
    }


    qDebug()
        << "[BDD] Transaction démarrée";

    return true;
}

bool DatabaseManager::commit()
{
    if(!m_database.commit())
    {
        qDebug()
        << "[BDD] Impossible de valider la transaction";

        return false;
    }


    qDebug()
        << "[BDD] Transaction validée";

    return true;
}

bool DatabaseManager::rollback()
{
    if(!m_database.rollback())
    {
        qDebug()
        << "[BDD] Impossible d'annuler la transaction";

        return false;
    }


    qDebug()
        << "[BDD] Transaction annulée";

    return true;
}
