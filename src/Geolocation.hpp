//
// Created by nyanbanan on 25.03.24.
//

#ifndef SUDOKU_GEOLOCATION_HPP
#define SUDOKU_GEOLOCATION_HPP

#include <QObject>
#include <QtQml>
#include <QNetworkAccessManager>
#include <QFile>

#include <iostream>

class Geolocation : public QObject {
Q_OBJECT
QML_ELEMENT
public:
    explicit Geolocation(QObject* parent = nullptr);

    Q_PROPERTY(QString country READ getCountry NOTIFY countryUpdated)

    QString getCountry();

signals:
    void countryUpdated(QString country);

private:
    void handleReply(QNetworkReply *reply);

    QNetworkAccessManager _network;
    QString _country;
};


#endif //SUDOKU_GEOLOCATION_HPP
