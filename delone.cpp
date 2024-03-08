
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>
#include <limits>

class Point {
public:
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < std::numeric_limits<double>::epsilon() &&
               std::abs(y - other.y) < std::numeric_limits<double>::epsilon();
    }

    bool operator<(const Point& other) const {
        return x < other.x || (!(other.x < x) && y < other.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

class Triangle {
public:
    Point p0, p1, p2;

    Triangle(Point p0, Point p1, Point p2) : p0(p0), p1(p1), p2(p2) {}

    bool operator==(const Triangle& other) const {
        // Check if all vertices are the same, ignoring order
        return (p0 == other.p0 || p0 == other.p1 || p0 == other.p2) &&
               (p1 == other.p0 || p1 == other.p1 || p1 == other.p2) &&
               (p2 == other.p0 || p2 == other.p1 || p2 == other.p2);
    }

    bool isPointInsideCircumcircle(const Point& D) const {
        double ax = p0.x - D.x, ay = p0.y - D.y, az = ax * ax + ay * ay;
        double bx = p1.x - D.x, by = p1.y - D.y, bz = bx * bx + by * by;
        double cx = p2.x - D.x, cy = p2.y - D.y, cz = cx * cx + cy * cy;
        double dx = 0, dy = 0, dz = dx * dx + dy * dy; // D is relative to itself, so differences are 0

        double det = ax * (by * cz - bz * cy) -
                     ay * (bx * cz - bz * cx) +
                     az * (bx * cy - by * cx) -
                     1 * (bx * (cy * dz - cz * dy) - by * (cx * dz - cz * dx) + bz * (cx * dy - cy * dx));

        return det > 0;
    }
    bool isColl() const {
        double det = p0.x * (p1.y - p2.y) + p1.x * (p2.y - p0.y) + p2.x * (p0.y - p1.y);
        return std::abs(det) < std::numeric_limits<double>::epsilon();
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& t) {
        os << "Triangle: " << t.p0 << ", " << t.p1 << ", " << t.p2;
        return os;
    }
};



class DelaunayTriangulation {
public:
    std::vector<Triangle> triangulate(const std::vector<Point>& points) {
        std::vector<Triangle> triangles;
        
        // Створення супертрикутника, який охоплює всі точки.
        Point p0(-1e4, -1e4);
        Point p1(1e4, -1e4);
        Point p2(0, 1e4);
        triangles.emplace_back(p0, p1, p2);
        
        // Додавання кожної точки до триангуляції.
        for (const auto& point : points) {
            // Визначення "поганих" трикутників, які порушують умови Делоне через додавання точки.
            std::vector<Triangle> badTriangles;
            std::set<std::pair<Point, Point>> polygonEdges;
            
            for (const auto& triangle : triangles) {
                if (triangle.isPointInsideCircumcircle(point)) {
                    badTriangles.push_back(triangle);
                    polygonEdges.insert({triangle.p0, triangle.p1});
                    polygonEdges.insert({triangle.p1, triangle.p2});
                    polygonEdges.insert({triangle.p2, triangle.p0});
                }
            }
            
            // Видалення "поганих" трикутників.
            triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
                                           [&](const Triangle& t) {
                return std::find(badTriangles.begin(), badTriangles.end(), t) != badTriangles.end();
            }),
                            triangles.end());
            
            // Створення нових трикутників з кожним ребром полігону та доданою точкою.
            for (const auto& edge : polygonEdges) {
                triangles.emplace_back(edge.first, edge.second, point);
            }
        }
        
        // Видалення трикутників, пов'язаних із вершинами супертрикутника.
        triangles.erase(std::remove_if(triangles.begin(), triangles.end(),
                                       [p0, p1, p2](const Triangle& t) {
            return t.p0 == p0 || t.p1 == p1 || t.p2 == p2 ||
            t.p0 == p1 || t.p1 == p2 || t.p2 == p0;
        }),
                        triangles.end());
        
        return triangles;
    }
};

int main() {
    int N;
    std::cout << "Введіть кількість точок: ";
    std::cin >> N;

    std::vector<Point> points(N);
    for (int i = 0; i < N; ++i) {
        std::cout << "Введіть x та y для точки " << i + 1 << ": ";
        std::cin >> points[i].x >> points[i].y;
    }

    DelaunayTriangulation delaunay;
    auto triangles = delaunay.triangulate(points);

    std::cout << "Трикутники Делоне:" << std::endl;
    for (const auto& triangle : triangles) {
        if (!triangle.isColl()) {
            std::cout << triangle << std::endl;
        }
    }

    return 0;
}

