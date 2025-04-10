#include "hermitecurve.h"

HermiteCurve::HermiteCurve(QObject *parent, ReadYaml* readYaml, double tension) : QObject(parent), readYaml(readYaml), mtension(tension) {}

std::vector<HermiteCurve::Point> HermiteCurve::createTangentPoints(const std::vector<Point>& points) {
    std::vector<Point> tangentPoints;
    if (points.size() < 2) return {};

    for (size_t i = 0; i < points.size(); ++i) {
        double diffX = 0.0, diffY = 0.0;
        if (i == 0) {
            diffX = points[1].x - points[0].x;
            diffY = points[1].y - points[0].y;
        } else if (i == points.size() - 1) {
            diffX = points[i].x - points[i - 1].x;
            diffY = points[i].y - points[i - 1].y;
        } else {
            diffX = points[i + 1].x - points[i - 1].x;
            diffY = points[i + 1].y - points[i - 1].y;
        }
        tangentPoints.push_back({diffX * (1 - mtension), diffY * (1 - mtension)});
    }
    return tangentPoints;
}

std::vector<HermiteCurve::Point> HermiteCurve::getCurve(const Point& p0, const Point& t0, const Point& p1, const Point& t1) {
    double distance = std::hypot(p1.x - p0.x, p1.y - p0.y);
    int numPoints = static_cast<int>(distance / 0.1);

    std::vector<double> t(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        t[i] = static_cast<double>(i) / (numPoints - 1);
    }

    std::vector<Point> curvePoints;
    curvePoints.reserve(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        double h00 = 2 * std::pow(t[i], 3) - 3 * std::pow(t[i], 2) + 1;
        double h10 = std::pow(t[i], 3) - 2 * std::pow(t[i], 2) + t[i];
        double h01 = -2 * std::pow(t[i], 3) + 3 * std::pow(t[i], 2);
        double h11 = std::pow(t[i], 3) - std::pow(t[i], 2);

        double x = h00 * p0.x + h10 * t0.x + h01 * p1.x + h11 * t1.x;
        double y = h00 * p0.y + h10 * t0.y + h01 * p1.y + h11 * t1.y;

        curvePoints.push_back({x, y});
    }
    return curvePoints;
}

void HermiteCurve::createCurve() {
    mCurvePointsPixel.clear();
    mCurvePointsMeter.clear();
    if (mLandmarkPointsPixel.size() < 2) return;

    std::vector<HermiteCurve::Point> tangentPoints = createTangentPoints(mLandmarkPointsPixel);

    for (size_t i = 0; i < mLandmarkPointsPixel.size() - 1; ++i) {
        auto p0 = mLandmarkPointsPixel[i];
        auto t0 = tangentPoints[i];
        auto p1 = mLandmarkPointsPixel[i + 1];
        auto t1 = tangentPoints[i + 1];
        auto curveSegment = getCurve(p0, t0, p1, t1);
        mCurvePointsPixel.insert(mCurvePointsPixel.end(), curveSegment.begin(), curveSegment.end());
    }

    int step = static_cast<int>(mCurvePointsPixel.size() / 100); // reduce the number of points to 100

    for (size_t i = 0; i < mCurvePointsPixel.size(); i += step) {
        QPair<double, double> meterPoint = readYaml->convertPixelToMeter(mCurvePointsPixel[i].x, mCurvePointsPixel[i].y);
        mCurvePointsMeter.emplace_back(meterPoint.first, meterPoint.second);
    }
    mCurvePointsMeter.emplace_back(mCurvePointsMeter.back().x, mCurvePointsMeter.back().y);
    mCurvePointsMeter.shrink_to_fit();

    emit curvePointsChanged();    
}

void HermiteCurve::addPoint(double x, double y) {
    QPair<double, double> meterPoint = readYaml->convertMeterToPixel(x, y);
    mLandmarkPointsPixel.emplace_back(meterPoint.first, meterPoint.second);
}

void HermiteCurve::updatePoint(int index, double x, double y) {
    if (index < 0 || index >= static_cast<int>(mLandmarkPointsPixel.size())) return;
    QPair<double, double> meterPoint = readYaml->convertMeterToPixel(x, y);
    mLandmarkPointsPixel[index] = {meterPoint.first, meterPoint.second};
}

void HermiteCurve::clearLandmarkPoints(int index) {
    if (index < -1 || index >= static_cast<int>(mLandmarkPointsPixel.size())) return;
    else if (index == -1) {
        mCurvePointsPixel.clear();
        mCurvePointsMeter.clear();
        mLandmarkPointsPixel.clear();
    } else {
        mLandmarkPointsPixel.erase(mLandmarkPointsPixel.begin() + index);
    }
}

int HermiteCurve::getLandmarkPointCount() const {
    return mLandmarkPointsPixel.size();
}

QVariantList HermiteCurve::getLandmarkPointsList() const {
    QVariantList landmarkPointsList;
    landmarkPointsList.reserve(mLandmarkPointsPixel.size());
    for (const auto &point : mLandmarkPointsPixel) {
        landmarkPointsList.append(QVariant::fromValue(QVariantList{point.x, point.y}));
}
    return landmarkPointsList;
}

QVariantList HermiteCurve::getCurvePointsQml() const {
    QVariantList curvePointsList;
    curvePointsList.reserve(mCurvePointsPixel.size());
    for (const auto &point : mCurvePointsPixel) {
        curvePointsList.append(QVariant::fromValue(QVariantList{point.x, point.y}));
    }
    return curvePointsList;
}

std::vector<HermiteCurve::Point> HermiteCurve::getCurvePointsMeter() const {
    return mCurvePointsMeter;
}

void HermiteCurve::clearCurvePoints() {
    qDebug() << "Clearing curve points";
    mCurvePointsPixel.clear();
    mCurvePointsMeter.clear();
    emit curvePointsChanged();
}