#ifndef HERMITE_CURVE_H
#define HERMITE_CURVE_H

#include <vector>
#include <cmath>
#include <iostream>
#include <QObject>
#include <QVariant>
#include <QDebug>

class HermiteCurve : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList curvePointsQml READ getCurvePointsQml NOTIFY curvePointsChanged)

private:
    struct Point {
        double x, y;
        Point(double x_val, double y_val) : x(x_val), y(y_val) {}
    };

    std::vector<Point> landmarkPoints;
    double tension;
    int arrImageSize[2];
    std::vector<std::pair<std::vector<double>, std::vector<double>>> curvePoints;
    std::vector<Point> tangentPoints;

    std::pair<std::vector<double>, std::vector<double>> getCurve(const Point& p0, const Point& t0, 
                                                                 const Point& p1, const Point& t1);
    void createTangentPoints();
    void printCurvePoints();

public:
    explicit HermiteCurve(QObject *parent = nullptr, double tension = 0.5);

    Q_INVOKABLE void clearLamdmarkPoints();
    Q_INVOKABLE void clearCurvePoints();
    Q_INVOKABLE void removePoint(int index);
    
    Q_INVOKABLE void addPoint(double x, double y);
    Q_INVOKABLE void updatePoint(int index, double x, double y);
    Q_INVOKABLE void createCurve();
    int getCurvePointCount() const;
    QVariantList getCurvePointsQml() const;

signals:
    void curvePointsChanged();
};

#endif // HERMITE_CURVE_H
