#include "hermitecurve.h"
#include <iostream>

HermiteCurve::HermiteCurve(QObject *parent, double tension) : QObject(parent), tension(tension) {
    // landmarkPoints.emplace_back(1, 2);
    // std::cout << "x: " << landmarkPoints.at(0).x << ", y: " << landmarkPoints.at(0).y << std::endl;
}

std::pair<std::vector<double>, std::vector<double>> HermiteCurve::getCurve(const Point& p0, const Point& t0, 
                                                                           const Point& p1, const Point& t1) {
    double distance = std::hypot(p1.x - p0.x, p1.y - p0.y);
    int numPoints = static_cast<int>(distance / 0.1);

    std::vector<double> t(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        t[i] = static_cast<double>(i) / (numPoints - 1);
    }

    std::vector<double> x(numPoints), y(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        double h00 = 2 * std::pow(t[i], 3) - 3 * std::pow(t[i], 2) + 1;
        double h10 = std::pow(t[i], 3) - 2 * std::pow(t[i], 2) + t[i];
        double h01 = -2 * std::pow(t[i], 3) + 3 * std::pow(t[i], 2);
        double h11 = std::pow(t[i], 3) - std::pow(t[i], 2);

        x[i] = h00 * p0.x + h10 * t0.x + h01 * p1.x + h11 * t1.x;
        y[i] = h00 * p0.y + h10 * t0.y + h01 * p1.y + h11 * t1.y;
    }

    return {x, y};
}

void HermiteCurve::createTangentPoints() {
    tangentPoints.clear();
    if (landmarkPoints.size() < 2) return;

    for (size_t i = 0; i < landmarkPoints.size(); ++i) {
        double diffX = 0.0, diffY = 0.0;

        if (i == 0) {
            diffX = landmarkPoints[1].x - landmarkPoints[0].x;
            diffY = landmarkPoints[1].y - landmarkPoints[0].y;
        } else if (i == landmarkPoints.size() - 1) {
            diffX = landmarkPoints[i].x - landmarkPoints[i - 1].x;
            diffY = landmarkPoints[i].y - landmarkPoints[i - 1].y;
        } else {
            diffX = landmarkPoints[i + 1].x - landmarkPoints[i - 1].x;
            diffY = landmarkPoints[i + 1].y - landmarkPoints[i - 1].y;
        }

        tangentPoints.push_back({diffX * (1 - tension), diffY * (1 - tension)});
    }
}

void HermiteCurve::addPoint(double x, double y) {
    landmarkPoints.emplace_back(x, y);
}

void HermiteCurve::updatePoint(int index, double x, double y) {
    if (index < 0 || index >= static_cast<int>(landmarkPoints.size())) return;
    landmarkPoints[index] = {x, y};
}

void HermiteCurve::createCurve() {
    curvePoints.clear();
    if (landmarkPoints.size() < 2) return;

    createTangentPoints();

    for (size_t i = 0; i < landmarkPoints.size() - 1; ++i) {
        auto p0 = landmarkPoints[i];
        auto t0 = tangentPoints[i];
        auto p1 = landmarkPoints[i + 1];
        auto t1 = tangentPoints[i + 1];

        auto curve = getCurve(p0, t0, p1, t1);
        curvePoints.push_back(curve);
    }

    emit curvePointsChanged();    
}

int HermiteCurve::getCurvePointCount() const {
    int totalPoints = 0;
    for (const auto& segment : curvePoints) {
        totalPoints += segment.first.size();
    }
    return totalPoints;
}

void HermiteCurve::printCurvePoints() {
    for (const auto& segment : curvePoints) {
        for (size_t i = 0; i < segment.first.size(); ++i) {
            std::cout << "x: " << segment.first[i] << ", y: " << segment.second[i] << std::endl;
        }
    }
}

QVariantList HermiteCurve::getCurvePointsQml() const {
    QVariantList qmlList;
    for (const auto& segment : curvePoints) {
        QVariantMap segmentMap;
        QVariantList xList, yList;

        for (double x : segment.first) {
            xList.append(x);
        }
        for (double y : segment.second) {
            yList.append(y);
        }

        segmentMap["x"] = xList;
        segmentMap["y"] = yList;
        qmlList.append(segmentMap);
    }

    return qmlList;
}

void HermiteCurve::clearLamdmarkPoints() {
    landmarkPoints.clear();
}

void HermiteCurve::clearCurvePoints() {
    curvePoints.clear();
}

void HermiteCurve::removePoint(int index) {
    if (index < 0 || index >= static_cast<int>(landmarkPoints.size())) return;
    landmarkPoints.erase(landmarkPoints.begin() + index);
}
