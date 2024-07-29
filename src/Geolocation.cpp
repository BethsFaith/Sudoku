//
// Created by nyanbanan on 25.03.24.
//

#include "Geolocation.hpp"

Geolocation::Geolocation(QObject *parent) : QObject(parent) {
    connect(&_network, &QNetworkAccessManager::finished,
            this, &Geolocation::handleReply);

    _network.get(QNetworkRequest(QUrl("http://ip-api.com/json/?fields=country")));
}

void Geolocation::handleReply(QNetworkReply *reply) {
    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        std::cerr << reply->errorString().toStdString() << std::endl;
        return;
    }
    auto code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (code != 200) {
        std::cerr << reply->errorString().toStdString() << std::endl;
        return;
    }
    auto body = reply->readAll();
    QJsonDocument body_doc = QJsonDocument::fromJson(body);
    QJsonObject body_json = body_doc.object();
    if(!body_json.contains("country")){
        std::cerr << "Bad reply" << std::endl;
        return;
    }
    _country = body_json.value("country").toString();

    emit countryUpdated(_country);
}

QString Geolocation::getCountry() {
    return _country;
}
