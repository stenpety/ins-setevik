#ifndef INITSETEVIKDB_H
#define INITSETEVIKDB_H

#include <QtSql>
#include <iostream>

void addCompany(QSqlQuery &query, const QString &companyName, const QString &companyVK,
                const QString &companyKeyWord) {
    query.addBindValue(companyName);
    query.addBindValue(companyVK);
    query.addBindValue(companyKeyWord);
    query.exec();
}

void addSetevik(QSqlQuery &query, const QString &setevikName, const QString &setevikVK,
                const QString &setevikStory, const QVariant &companyId) {
    query.addBindValue(setevikName);
    query.addBindValue(setevikVK);
    query.addBindValue(setevikStory);
    query.addBindValue(companyId);
    query.exec();
}

void databaseConnect(const QString &dbFileName) {
    const QString DRIVER ("QSQLITE");

    if (QSqlDatabase::isDriverAvailable(DRIVER)) {
        QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);

        db.setDatabaseName(dbFileName);
        if (!db.open()) {
            qWarning() << "Database connect ERROR: " << db.lastError().text();
        }
    } else {
        qWarning() << "Database connect ERROR: no driver " << DRIVER << " available";
    }
}

void createTablesDb() {
    QSqlQuery query;

    query.prepare("CREATE TABLE setevik (id INTEGER PRIMARY KEY, name TEXT, vk TEXT, story TEXT, company INTEGER)");
    if (!query.exec()) {
        qWarning() << "Database create tables (setevik) ERROR: " << query.lastError().text();
    }

    query.prepare("CREATE TABLE companies (id INTEGER PRIMARY KEY, name TEXT, vk TEXT, keyword TEXT)");
    if (!query.exec()) {
        qWarning() << "Database create tables (companied) ERROR: " << query.lastError().text();
    }

    query.prepare("CREATE TABLE timers (id INTEGER PRIMARY KEY, name INTEGER, start_date INTEGER, duration INTEGER, description TEXT, penalty TEXT)");
    if (!query.exec()) {
        qWarning() << "Database create tables (timers) ERROR: " << query.lastError().text();
    }

}

void initiSetevikDB(const QString &dbFileName) {

    bool dbFileExists = (QFileInfo::exists(dbFileName) && QFileInfo(dbFileName).isFile());
    databaseConnect(dbFileName);

    // TODO: check tables, NOT file existense
    if (!dbFileExists) {
        createTablesDb();
        std::cout << "DB tables created" << std::endl;
    }
}

#endif // INITSETEVIKDB_H
