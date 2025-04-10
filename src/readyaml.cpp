#include "readyaml.h"

ReadYaml::ReadYaml(QObject *parent) : QObject(parent) {}

void ReadYaml::readYaml(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file from resource";
        return;
    }

    QByteArray fileData = file.readAll();
    YAML::Node node = YAML::Load(fileData.toStdString());

    mYamlData["image"] = QString::fromStdString(node["image"].as<std::string>());
    mYamlData["resolution"] = node["resolution"].as<double>();
    mYamlData["negate"] = node["negate"].as<int>();
    mYamlData["occupied_thresh"] = node["occupied_thresh"].as<double>();
    mYamlData["free_thresh"] = node["free_thresh"].as<double>();

    YAML::Node origin = node["origin"];
    QVariantList originList;
    for (std::size_t i = 0; i < origin.size(); i++) {
        originList.append(origin[i].as<double>());
    }
    mYamlData["origin"] = originList;
}

QVariantMap ReadYaml::getYamlValue() const {
    return mYamlData;
}

void ReadYaml::onImageLoader(const int& width, const int& height, const int& sourcesizeWidth, const int& sourcesizeHeight, const int& shapeWidth, const int& shapeHeight) {
    displaySize = {width, height};
    sourceSize = {sourcesizeWidth, sourcesizeHeight};
    shapeSize = {shapeWidth, shapeHeight};
}

QPair<double, double> ReadYaml::convertPixelToMeter(const double &x, const double &y) const {
    if (mYamlData.isEmpty()) {
        qDebug() << "Warning: mYamlData is empty";
        return {0.0, 0.0};
    }

    double xMeter = (x - shapeSize.width) / (displaySize.width / sourceSize.width);
    double yMeter = (displaySize.height - y - shapeSize.height) / (displaySize.height / sourceSize.height);

    xMeter = xMeter * mYamlData["resolution"].toDouble() + mYamlData["origin"].toList()[0].toDouble();
    yMeter = yMeter * mYamlData["resolution"].toDouble() + mYamlData["origin"].toList()[1].toDouble();

    return qMakePair(xMeter, yMeter);
}

QPair<double, double> ReadYaml::convertMeterToPixel(const double &x, const double &y) const {
    if (mYamlData.isEmpty()) {
        qDebug() << "Warning: mYamlData is empty";
        return {0.0, 0.0};
    }

    double xPixel = (x - mYamlData["origin"].toList()[0].toDouble()) / mYamlData["resolution"].toDouble();
    double yPixel = (y - mYamlData["origin"].toList()[1].toDouble()) / mYamlData["resolution"].toDouble();

    xPixel = xPixel * (displaySize.width / sourceSize.width) + shapeSize.width;
    yPixel = displaySize.height - (yPixel * (displaySize.height / sourceSize.height)) - shapeSize.height;

    return qMakePair(xPixel, yPixel);
}

QVariantList ReadYaml::getConvertPixelToMeter(const double &x, const double &y) const {
    QPair<double, double> point = convertPixelToMeter(x, y);
    return QVariantList{point.first, point.second};
}
