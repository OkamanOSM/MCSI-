#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

static const int a = 0;
const long long b = 0;
const long long c = 0;
const int mod = 101;
long long d = 2;
long long e = 3;

Point P = { 3, 6 };

struct PointWithUQ_VQ {
    Point point;
    long long uQ;
    long long vQ;
};

vector<Point> points;
vector<Point> r_plus_and_2_torsion_subgroup;
vector<PointWithUQ_VQ> uQ_vQPoints;
bool is_there_2_torsion_point = true;

void add_point_to_vector(int type, Point p1) {
    if (type == 1) { points.push_back(p1); }
    else if (type == 2) { r_plus_and_2_torsion_subgroup.push_back(p1); }
    else { exit; }
}

long long modAdd(int a, int b) {
    return (a + b) % mod;
}

long long modSubtract(int a, int b) {
    return (a - b + mod) % mod;
}

long long modMultiply(int a, int b) {
    return (1LL * a * b) % mod;
}

long long modPow(int base, int exponent) {
    int result = 1;
    base %= mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = modMultiply(result, base);
        }
        base = modMultiply(base, base);
        exponent >>= 1;
    }
    return result;
}

Point pointAdd(Point p1, Point p2) {
    Point result;
    if (p1.x != p2.x) {
        long long slope = modMultiply(modSubtract(p2.y, p1.y), modPow(modSubtract(p2.x, p1.x), mod - 2));
        result.x = modSubtract(modSubtract(modMultiply(slope, slope), p1.x), p2.x);
        result.y = modSubtract(modMultiply(slope, modSubtract(p1.x, result.x)), p1.y);
    }
    else {
        long long slope = modMultiply(modAdd(modMultiply(3, p1.x * p1.x), d), modPow(modMultiply(2, p1.y), mod - 2));
        result.x = modSubtract(modSubtract(modMultiply(slope, slope), p1.x), p2.x);
        result.y = modSubtract(modMultiply(slope, modSubtract(p1.x, result.x)), p1.y);
    }

    result.x = result.x % mod;
    result.y = result.y % mod;

    if ((result.y * result.y) % mod == (result.x * result.x * result.x + d * result.x + e) % mod) {
    }
    else {
        //cerr << "Hata: Bu noktalar eðri üzerinde deðil.\n";
    }

    return result;
}

long long find_the_infinite_point(Point start_point) {
    int infinite_number_queue = 2;
    bool indicator = true;
    Point second_point = start_point;
    add_point_to_vector(1, start_point);

    while (indicator) {
        second_point = pointAdd(start_point, second_point);
        add_point_to_vector(1, second_point);

        if (second_point.x == start_point.x && second_point.y == (mod - start_point.y)) {
            indicator = false;
            return infinite_number_queue;
        }

        infinite_number_queue++;
    }
}

long long find_r_plus_groups(int finite_number) {
    if (finite_number % 2 == 0) {
        is_there_2_torsion_point = false;
    }
    else {
        is_there_2_torsion_point = true;
    }

    int start_index = (finite_number % 2 == 0) ? (finite_number / 2) : (finite_number + 1) / 2;

    for (int i = 0; i < start_index; i++) {
        Point current_point = points[i];
        add_point_to_vector(2, current_point);
    }
    return (start_index);
}

void calculate_vQ_uQ(int start_index) {
    int i = 1;
    for (const Point& Q : r_plus_and_2_torsion_subgroup) {
        int fQ = modAdd(modAdd(modMultiply(3, modMultiply(Q.x, Q.x)), modMultiply(2 * c, Q.x)), modSubtract(d, modMultiply(a, Q.y)));
        int gQ = modSubtract(modSubtract(0, modMultiply(2, Q.y)), modAdd(modMultiply(a, Q.x), b));

        int vQ;
        if (is_there_2_torsion_point == true && i == start_index) {
            vQ = fQ;
        }
        else {
            vQ = modSubtract(modMultiply(2, fQ), modMultiply(a, gQ));
        }

        int uQ = modMultiply(gQ, gQ);
        uQ_vQPoints.push_back({ Q, uQ, vQ });

        i++;
    }
}

void calculate_isogeny() {
    int v = 0;
    int w = 0;

    for (PointWithUQ_VQ& uQ_vQPoint : uQ_vQPoints) {
        v = modAdd(v, uQ_vQPoint.vQ);
        int term = modAdd(uQ_vQPoint.uQ, modMultiply(uQ_vQPoint.point.x, uQ_vQPoint.vQ));
        w = modAdd(w, term);
    }

    d = modSubtract(d, modMultiply(5, v));
    e = modSubtract(e, modAdd(modMultiply(modAdd(modMultiply(a, a), modMultiply(4, c)), v), modMultiply(7, w)));
    cout << " a:" << d << " e:" << e << endl;
}

Point calculate_image_point() {
    long long a1 = a;
    long long a3 = b;
    long long alpha = P.x;
    long long beta = P.y;

    for (const auto& Q : uQ_vQPoints) {
        long long xQ = Q.point.x;
        long long yQ = Q.point.y;
        long long uQ = Q.uQ;
        long long vQ = Q.vQ;

        long long xDiff = modSubtract(P.x, xQ);
        long long xDiffSq = modPow(xDiff, 2);
        long long xDiffCube = modPow(xDiff, 3);

        long long termAlpha1 = modMultiply(vQ, modPow(xDiff, mod - 2));
        long long termAlpha2 = modMultiply(uQ, modPow(xDiffSq, mod - 2));
        alpha = modAdd(alpha, modSubtract(termAlpha1, termAlpha2));

        long long term1 = modMultiply(uQ, modMultiply(modAdd(modAdd(modMultiply(2, P.y), modMultiply(a1, P.x)), a3), modPow(xDiffCube, mod - 2)));
        long long term2 = modMultiply(vQ, modAdd(modMultiply(a1, xDiff), modSubtract(P.y, yQ)));
        term2 = modMultiply(term2, modPow(xDiffSq, mod - 2));
        long long gQx = modAdd(modAdd(modMultiply(3, modMultiply(xQ, xQ)), modMultiply(2 * c, xQ)), modSubtract(d, modMultiply(a, yQ)));
        long long gQy = modSubtract(modSubtract(0, modMultiply(2, yQ)), modAdd(modMultiply(a, xQ), b));
        long long term3 = modMultiply(modSubtract(modMultiply(a1, uQ), modMultiply(gQx, gQy)), modPow(xDiffSq, mod - 2));

        beta = modSubtract(beta, modAdd(modAdd(term1, term2), term3));
    }

    return { alpha, beta };
}

int main() {
    int a;
    cout << "Lutfen dongu sayisini seciniz" << endl;
    cin >> a;
    const clock_t begin_time = clock();

    for (int i = 0; i < a; i++) {
        int finite_number = find_the_infinite_point(P);
        //cout << finite_number << endl;
        int queue_of_s_group = find_r_plus_groups(finite_number);

        calculate_vQ_uQ(queue_of_s_group);

        calculate_isogeny();
        Point z = calculate_image_point();
        P.x = z.x;
        P.y = z.y;
        cout << "image point's x = " << P.x << " Image point's y = " << P.y << endl;
    }

    cout << float(clock() - begin_time) / CLOCKS_PER_SEC << endl;
}
