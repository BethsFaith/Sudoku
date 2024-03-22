//
// Created by nyanbanan on 25.03.24.
//

#include "LabelStorage.hpp"

LabelStorage::LabelStorage(QObject *parent) : QObject(parent) {}

void LabelStorage::parse(QString file, QString language) {
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
    if (jsonObject.contains(language)) {
        auto array = jsonObject.value(language).toArray();
        for (int i{}; i < array.count(); ++i) {
            auto labelObj = array[i].toObject();

            if (!labelObj.contains("name") || !labelObj.contains("value")) {
                std::cerr << "Uncorrected json element at label json array" << std::endl;
            } else {
                _labels[labelObj["name"].toString()] = labelObj["value"].toString();
            }
        }
    }
}

QString LabelStorage::getText(QString name) {
    return _labels[name];
}
