//
// Created by nyanbanan on 25.03.24.
//

#include "RecordStorage.hpp"

namespace Records {
    RecordStorage::RecordStorage(QObject *parent) : QObject(parent) {}

    void RecordStorage::parse(const QString& file) {
        QFile fileStream{file};
        if (!fileStream.open(QIODevice::ReadOnly)) {
            std::cerr << "Uncorrected file" << std::endl;
            return;
        }
        auto jsonDoc = QJsonDocument::fromJson(fileStream.readAll());
        if (jsonDoc.isNull()) {
            std::cerr << "Uncorrected json format" << std::endl;
            return;
        }
        auto jsonObject = jsonDoc.object();
        auto levels = {Constants::EASY.c_str(), Constants::MEDIUM.c_str(), Constants::HARD.c_str(),
                       Constants::EXTREME.c_str()};
        for (const auto level: levels) {
            if (jsonObject.contains(level)) {
                list records;

                auto array = jsonObject.value(level).toArray();
                for (int i{}; i < array.count(); ++i) {
                    records.push_back(array[i].toInt());
                }

                _records[level] = records;
            }
        }
    }

    void RecordStorage::save(const QString& file) {
        QFile fileStream{file};
        if (!fileStream.open(QIODevice::WriteOnly)) {
            std::cerr << "Uncorrected file" << std::endl;
            return;
        }
        QJsonObject obj;
        for (const auto keyValue : _records) {
            QJsonArray array;

            for (int record : keyValue.second) {
                array.push_back(QJsonValue(record));
            }

            obj.insert(keyValue.first.c_str(), array);
        }

        QJsonDocument doc(obj);
        fileStream.write(doc.toJson());
    }

    void RecordStorage::setRecord(QString level, int record) {
        auto levelStr = level.toStdString();
        if (!_records.contains(levelStr)) {
            _records[levelStr] = list{};
            _records[levelStr].push_back(record);
        } else {
            auto& records = _records[levelStr];
            if (records.empty()) {
                records.push_back(record);
            } else if (records.back() < record) {
                if (records.size() < limit) {
                    records.push_back(record);
                } else {
                    return;
                }
            } else {
                for (int i{}; i < records.size(); ++i) {
                    if (records[i] > record) {
                        records.insert(i, record);
                        break;
                    }
                }
            }
            if (records.size() > limit) {
                records.remove(records.size()-1);
            }
        }
    }

    QList<unsigned int> RecordStorage::getRecords(QString level) {
        return _records[level.toStdString()];
    }
} // Records