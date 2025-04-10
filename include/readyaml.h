#ifndef READYAML_H
#define READYAML_H

#include <QObject>
#include <QVariant>
#include <yaml-cpp/yaml.h>
#include <QDebug>
#include <QFile>

struct ImageSize {
    int width, height;
};

class ReadYaml : public QObject {
    Q_OBJECT

public:
    explicit ReadYaml(QObject *parent = nullptr);

    Q_INVOKABLE void readYaml(const QString &filePath);
    Q_INVOKABLE QVariantMap getYamlValue() const;
    Q_INVOKABLE QVariantList getConvertPixelToMeter(const double &x, const double &y) const;

    QPair<double, double> convertPixelToMeter(const double &x, const double &y) const;
    QPair<double, double> convertMeterToPixel(const double &x, const double &y) const;

public slots:
    void onImageLoader(const int& width, const int& height, const int& sourcesizeWidth, const int& sourcesizeHeight, const int& shapeWidth, const int& shapeHeight);

private:
    QVariantMap mYamlData;
    ImageSize displaySize;
    ImageSize sourceSize;
    ImageSize shapeSize;

};

#endif // READYAML_H

