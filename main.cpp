/*
#include <iostream>
#include <vector>
#include <algorithm>

class Point {
public:
    double x, y;

    // Конструктор для ініціалізації точок 0,0 за замовчуванням
    Point(double x = 0, double y = 0) : x(x), y(y) {}

    //функція для обчислення орієнтації трьох точок
    static double orientation(const Point& p1, const Point& p2, const Point& p3) {
        return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    }
};

class ConvexHullBuilder {
public:
    // функція для побудови опуклої оболонки
    static std::vector<Point> buildHull(std::vector<Point>& points) {
        size_t N = points.size();
        std::vector<Point> hull;

        // Знаходимо точку з найменшою y-координатою
        size_t minYPointIndex = 0;
        for (size_t i = 1; i < N; ++i) {
            if (points[i].y < points[minYPointIndex].y ||
                (points[i].y == points[minYPointIndex].y && points[i].x < points[minYPointIndex].x)) {
                minYPointIndex = i;
            }
        }
        // Переставляємо її на початок
        std::swap(points[0], points[minYPointIndex]);

        // Сортуємо точки за полярним кутом відносно першої точки
        std::sort(points.begin() + 1, points.end(), [&refPoint = points[0]](const Point& a, const Point& b) {
            double ori = Point::orientation(refPoint, a, b);
            return ori > 0 || (ori == 0 && (a.x - refPoint.x) < (b.x - refPoint.x));
        });

        // Додаємо перші три точки до опуклої оболонки
        for (size_t i = 0; i < 3 && i < N; ++i) {
            hull.push_back(points[i]);
        }

        // Побудова опуклої оболонки
        for (size_t i = 3; i <= N; ++i) {
            while (hull.size() >= 2 && Point::orientation(hull[hull.size() - 2], hull.back(), points[i % N]) <= 0) {
                hull.pop_back();
            }
            if (i < N) hull.push_back(points[i]);
        }

        return hull;
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

    // Побудова опуклої оболонки з заданих точок
    std::vector<Point> hull = ConvexHullBuilder::buildHull(points);

    // Виведення точок опуклої оболонки
    std::cout << "Точки опуклої оболонки:" << std::endl;
    for (const auto& point : hull) {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    return 0;
}
*/
