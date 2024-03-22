//
// Created by nyanbanan on 25.03.24.
//

#ifndef SUDOKU_LABELSTORAGE_HPP
#define SUDOKU_LABELSTORAGE_HPP

#include <QObject>
#include <QtQml>
#include <QJsonObject>
#include <QFile>

#include <iostream>

class LabelStorage : public QObject {
Q_OBJECT
QML_ELEMENT
public:
    explicit LabelStorage(QObject* parent = nullptr);

    Q_INVOKABLE void parse(QString file, QString language = "ru");

    Q_INVOKABLE QString getText(QString name);
private:
    std::map<QString, QString> _labels;
};

#endif //SUDOKU_LABELSTORAGE_HPP
