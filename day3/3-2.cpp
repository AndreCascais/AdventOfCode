#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

struct edge {
    int begin;
    int end;
    int constant;
    int dist;
};

struct point{
    int x;
    int y;
    int dist;
};

int dist(point p) {
    return p.dist;
}

bool intersects(edge e1, edge e2) {
    int minE1 = std::min(e1.begin, e1.end);
    int maxE1 = std::max(e1.begin, e1.end);
    int minE2 = std::min(e2.begin, e2.end);
    int maxE2 = std::max(e2.begin, e2.end);
    return e1.constant >= minE2 && e1.constant <= maxE2 && e2.constant >= minE1 && e2.constant <= maxE1;
}

void readValues(std::vector<edge>& hVector, std::vector<edge>& vVector) {
    int x = 0;
    int y = 0;

    int totalDist = 0;

    char dir;
    int dist;
    char sep;

    while (std::cin >> dir >> dist >> sep) {
        std::cout << dir << dist << '\n';
        totalDist = totalDist + dist;
        switch(dir) {
            case 'R':
                hVector.emplace_back(edge{x, x + dist, y, totalDist});
                x = x + dist;
                break;
            case 'L':
                hVector.emplace_back(edge{x, x - dist, y, totalDist});
                x = x - dist;
                break;
            case 'U':
                vVector.emplace_back(edge{y, y + dist, x, totalDist});
                y = y + dist;
                break;
            case 'D':
                vVector.emplace_back(edge{y, y - dist, x, totalDist});
                y = y - dist;
                break;
            default:
                break;
        }
        if (sep == '.') {
            return;
        }
    }
}

void findIntersections(std::vector<point>& vector, std::vector<edge>& hVector, std::vector<edge>& vVector) {
    for (auto hEdge : hVector) {
        for (auto vEdge : vVector) {
            std::cout << "hEdge: " << hEdge.begin << ',' << hEdge.end << ',' << hEdge.constant <<'\n';
            std::cout << "vEdge: " << vEdge.begin << ',' << vEdge.end << ',' << vEdge.constant <<'\n';
            if (intersects(hEdge, vEdge)) {
                if (vEdge.constant != 0 && hEdge.constant != 0) {
                    vector.emplace_back(point{vEdge.constant, hEdge.constant,
                    hEdge.dist - abs(hEdge.end - vEdge.constant) + vEdge.dist - abs(vEdge.end - hEdge.constant)});
                }
            }
        }
    }
}

int findClosestIntersection(std::vector<point>& v) {
    int best = dist(v[0]);
    for (auto i : v) {
        if (dist(i) < best) {
            best = dist(i);
        }
    }
    return best;
}

int main() {
    std::vector<edge> hVector1;
    std::vector<edge> vVector1;
    std::vector<edge> hVector2;
    std::vector<edge> vVector2;
    std::vector<point> intersectVector;

    readValues(hVector1, vVector1);
    readValues(hVector2, vVector2);
    findIntersections(intersectVector, hVector1, vVector2);
    findIntersections(intersectVector, hVector2, vVector1);

    std::cout << findClosestIntersection(intersectVector) << '\n';
}