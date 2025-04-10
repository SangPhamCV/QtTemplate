#ifndef HERMITE_CURVE_H
#define HERMITE_CURVE_H

#include <cmath>
#include <readyaml.h>

class HermiteCurve : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList curvePointsQml READ getCurvePointsQml NOTIFY curvePointsChanged)

public:
    struct Point {
        double x, y;
        Point(double _x, double _y) : x(_x), y(_y) {}  // Point Constructor
    };

    explicit HermiteCurve(QObject *parent = nullptr, ReadYaml* readYaml = nullptr, double tension = 0.5);

    Q_INVOKABLE void addPoint(double x, double y);
    Q_INVOKABLE void updatePoint(int index, double x, double y);
    Q_INVOKABLE void clearLandmarkPoints(int index);

    Q_INVOKABLE int getLandmarkPointCount() const;
    Q_INVOKABLE QVariantList getLandmarkPointsList() const;
    Q_INVOKABLE void createCurve();

    QVariantList getCurvePointsQml() const;
    std::vector<Point> getCurvePointsMeter() const;
    void  clearCurvePoints();
    ReadYaml* getReadYaml() const { return readYaml; }

private:
    ReadYaml* readYaml;
    std::vector<Point> mLandmarkPointsPixel;
    std::vector<Point> mCurvePointsPixel;
    std::vector<Point> mCurvePointsMeter;

    double mtension;

    std::vector<Point> getCurve(const Point& p0, const Point& t0, const Point& p1, const Point& t1);
    std::vector<Point> createTangentPoints(const std::vector<Point>& points);
signals:
    void curvePointsChanged();
};

#endif // HERMITE_CURVE_H
