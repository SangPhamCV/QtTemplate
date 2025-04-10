#include "virtualwall.h"

VirtualWall::VirtualWall(QObject *parent, ReadYaml* readYaml) : QObject(parent), readYaml(readYaml) {}
VirtualWall::~VirtualWall() {
}

void VirtualWall::addVirtualWallPoint(double x, double y) {
    QPair<double, double> meterPoint = readYaml->convertMeterToPixel(x, y);
    mVirtualWallPointsPixel.emplace_back(meterPoint.first, meterPoint.second);
    mVirtualWallPointsMeter.emplace_back(x, y);
    if (mVirtualWallPointsPixel.size() % 2 == 0) {
        std::vector<VirtualWall::Point> path = createVirtualWallPoints(mVirtualWallPointsPixel[mVirtualWallPointsPixel.size() - 2], 
                                                                        mVirtualWallPointsPixel.back());
        mVirtualWallPaths.emplace_back(path);
        emit virtualWallPathsChanged();
    }
}

void VirtualWall::clearVirtualWall() {
    mVirtualWallPointsPixel.clear();
    mVirtualWallPointsMeter.clear();
    mVirtualWallPaths.clear();
    emit virtualWallPathsChanged();
}

QVariantList VirtualWall::getVirtualWallPath(const int& index) const {
    if (mVirtualWallPaths.empty()) {
        return QVariantList();
    }
    QVariantList path;
    path.reserve(mVirtualWallPaths[index].size());
    for (const auto &point : mVirtualWallPaths[index]) {
        path.append(QVariant::fromValue(QVariantList{point.x, point.y}));
    }
    return path;
}

QVariantList VirtualWall::getVirtualWallPointsList() const {
    QVariantList virtualWallPointsList;
    virtualWallPointsList.reserve(mVirtualWallPointsPixel.size());
    for (const auto &point : mVirtualWallPointsPixel) {
        virtualWallPointsList.append(QVariant::fromValue(QVariantList{point.x, point.y}));
    }
    return virtualWallPointsList;
}

std::vector<VirtualWall::Point> VirtualWall::createVirtualWallPoints(const Point& p0, const Point& p1) {    
    std::vector<Point> virtualWallPath;
    int x1 = static_cast<int>(p0.x);
    int y1 = static_cast<int>(p0.y);
    int x2 = static_cast<int>(p1.x);
    int y2 = static_cast<int>(p1.y);

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        virtualWallPath.emplace_back(x1, y1);

        if (x1 == x2 && y1 == y2) break;

        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
    return virtualWallPath;
}