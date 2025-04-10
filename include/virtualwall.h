#ifndef VIRTUALWALL_H
#define VIRTUALWALL_H

#include <readyaml.h>

class VirtualWall : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int virtualWallPathSize READ getVirtualWallPathSize NOTIFY virtualWallPathsChanged)

public:
    struct Point {
        double x, y;
        Point(double _x, double _y) : x(_x), y(_y) {}  // Point Constructor
    };

    explicit VirtualWall(QObject *parent = nullptr, ReadYaml* readYaml = nullptr);
    ~VirtualWall();

    int getVirtualWallPathSize() const { return mVirtualWallPaths.size(); }

    Q_INVOKABLE void addVirtualWallPoint(double x, double y);
    Q_INVOKABLE void clearVirtualWall();
    Q_INVOKABLE QVariantList getVirtualWallPointsList() const;
    Q_INVOKABLE QVariantList getVirtualWallPath(const int& index) const;
    std::vector<Point> getVirtualWallPointsMeter() const { return mVirtualWallPointsMeter; }

private:
    std::vector<Point> mVirtualWallPointsPixel;
    std::vector<Point> mVirtualWallPointsMeter;
    std::vector<std::vector<Point>> mVirtualWallPaths;
    ReadYaml* readYaml;
    std::vector<Point> createVirtualWallPoints(const Point& p0, const Point& p1);


signals:
    void virtualWallPathsChanged();
};

#endif // VIRTUALWALL_H