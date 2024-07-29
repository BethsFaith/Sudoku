//
// Created by nyanbanan on 25.03.24.
//

#ifndef SUDOKU_RECORDSTORAGE_HPP
#define SUDOKU_RECORDSTORAGE_HPP

#include <QObject>
#include <QtQml>
#include <QJsonObject>
#include <QFile>

#include "constants.hpp"

namespace Records {
    class RecordStorage : public QObject {
        Q_OBJECT
        QML_ELEMENT
    public:
        explicit RecordStorage(QObject *parent = nullptr);

        Q_INVOKABLE void parse(const QString& file);
        Q_INVOKABLE void save(const QString& file);

        Q_INVOKABLE void setRecord(QString level, int record);

        Q_INVOKABLE QList<unsigned int> getRecords(QString level);
    private:
        using list = QList<unsigned int>;

        const int limit = 10;

        std::map<std::string, list> _records;
    };
} // Records

#endif //SUDOKU_RECORDSTORAGE_HPP
