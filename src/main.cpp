#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "game/Sudoku.hpp"

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/SudokuModule/src/main.qml")));

    return QGuiApplication::exec();
}
