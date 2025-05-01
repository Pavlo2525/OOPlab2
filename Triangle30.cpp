#include "Triangle30.h"

#define CP_UTF8 65001



double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle& t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double crossProduct(const Point& A, const Point& B, const Point& P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

bool isPointInTriangle_VectorMethod(const Triangle& t, const Point& P) {
    if (isDegenerate(t)) {
        return isPointOnEdge(t, P);
    }
    double c1 = crossProduct(t.A, t.B, P);
    double c2 = crossProduct(t.B, t.C, P);
    double c3 = crossProduct(t.C, t.A, P);

    bool has_neg = (c1 < 0) || (c2 < 0) || (c3 < 0);
    bool has_pos = (c1 > 0) || (c2 > 0) || (c3 > 0);

    return !(has_neg && has_pos);
}

bool isPointInTriangle_Heron(const Triangle& t, const Point& P) {
    Triangle t1 = { t.A, t.B, P };
    Triangle t2 = { t.B, t.C, P };
    Triangle t3 = { t.C, t.A, P };

    double S = heronArea(t);
    double S1 = heronArea(t1);
    double S2 = heronArea(t2);
    double S3 = heronArea(t3);

    return fabs((S1 + S2 + S3) - S) < 1e-9;
}

bool isDegenerate(const Triangle& t) {
    return fabs(crossProduct(t.A, t.B, t.C)) < 1e-9;
}

bool isPointOnSegment(const Point& A, const Point& B, const Point& P) {
    if (fabs(crossProduct(A, B, P)) > 1e-9)
        return false;

    return min(A.x, B.x) - 1e-9 <= P.x && P.x <= max(A.x, B.x) + 1e-9 &&
        min(A.y, B.y) - 1e-9 <= P.y && P.y <= max(A.y, B.y) + 1e-9;
}

bool isPointOnEdge(const Triangle& t, const Point& P) {
    return isPointOnSegment(t.A, t.B, P) ||
        isPointOnSegment(t.B, t.C, P) ||
        isPointOnSegment(t.C, t.A, P);
}


void coordinate() {
    Triangle t;

    cout << "Введіть координати трикутника (A, B, C):\n";
    cin >> t.A.x >> t.A.y >> t.B.x >> t.B.y >> t.C.x >> t.C.y;

    if (isDegenerate(t)) {
        cout << "Трикутник вироджений.\n";
    }
    else {
        cout << "Трикутник не є виродженим.\n";
    }

    int choice;
    do {
        cout << "\nМеню вибору методу:\n";
        cout << "1. Метод Герона\n";
        cout << "2. Метод векторного добутку\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Завершення програми...\n";
            break;
        }

        if (choice != 1 && choice != 2) {
            cout << "Невірний вибір. Спробуйте ще раз.\n";
            continue;
        }

        int n;
        cout << "Скільки точок ви хочете перевірити? ";
        cin >> n;

        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cout << "Введіть координати точки " << i + 1 << ": ";
            cin >> points[i].x >> points[i].y;

            bool inside = (choice == 1)
                ? isPointInTriangle_Heron(t, points[i])
                : isPointInTriangle_VectorMethod(t, points[i]);

            bool onEdge = isPointOnEdge(t, points[i]);

            if (onEdge) {
                cout << "Точка " << i + 1 << " лежить на межі трикутника.\n";
            }
            else if (inside) {
                cout << "Точка " << i + 1 << " належить трикутнику.\n";
            }
            else {
                cout << "Точка " << i + 1 << " не належить трикутнику.\n";
            }
        }

    } while (true);
}
