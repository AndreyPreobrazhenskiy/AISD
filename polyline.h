#pragma once
#include <iostream>
#include <complex>
#include <cmath>
#include <stdexcept>
#include <cstdlib>

#ifndef PI
#define PI 3.14159265358979323846
#endif

template<typename T>
struct Point {
    T x, y;

    Point(T x = T{}, T y = T{}) : x(x), y(y) {}

    double distanceTo(const Point& other) const {
        if constexpr (std::is_same_v<T, std::complex<float>> || std::is_same_v<T, std::complex<double>>) {
            double dx = std::abs(other.x - x);
            double dy = std::abs(other.y - y);
            return std::sqrt(dx * dx + dy * dy);  
        }
        else {
            double dx = static_cast<double>(other.x - x);
            double dy = static_cast<double>(other.y - y);
            return std::sqrt(dx * dx + dy * dy);
        }
    }

};

template<typename T>
class Polyline {
private:
    Point<T>* points;
    size_t count;
    size_t capacity;

    void expand() {
        capacity *= 2;
        Point<T>* newPoints = new Point<T>[capacity];
        for (size_t i = 0; i < count; ++i) {
            newPoints[i] = points[i];
        }
        delete[] points;
        points = newPoints;
    }

public:

    static constexpr double epsilon = 1e-5;

    explicit Polyline(size_t count = 0) : count(count), capacity(count > 0 ? count : 1) {
        points = new Point<T>[capacity];
    }

    explicit Polyline(const Point<T>& point) : count(1), capacity(1) {
        points = new Point<T>[capacity];
        points[0] = point;
    }

    Polyline(size_t count, T m1, T m2) : count(count), capacity(count) {
        points = new Point<T>[capacity];
        for (size_t i = 0; i < count; ++i) {
            T x = m1 + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (m2 - m1)));
            T y = m1 + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (m2 - m1)));
            points[i] = Point<T>(x, y);
        }
    }

    ~Polyline() {
        delete[] points;
    }

    Polyline(const Polyline& other) : count(other.count), capacity(other.capacity) {
        points = new Point<T>[capacity];
        for (size_t i = 0; i < count; ++i) {
            points[i] = other.points[i];
        }
    }

    Polyline& operator=(const Polyline& other) {
        if (this == &other) {
            return *this;
        }

        delete[] points;

        count = other.count;
        capacity = other.capacity;
        points = new Point<T>[capacity];
        for (size_t i = 0; i < count; ++i) {
            points[i] = other.points[i];
        }

        return *this;
    }

    Point<T>& operator[](size_t index) {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return points[index];
    }

    const Point<T>& operator[](size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of range");
        }
        return points[index];
    }

    Polyline operator+(const Polyline& other) const {

        Polyline result(count + other.count);
        for (size_t i = 0; i < count; ++i) {
            result.points[i] = points[i];
        }
        for (size_t i = 0; i < other.count; ++i) {
            result.points[count + i] = other.points[i];
        }
        result.count = count + other.count;
        return result;
    }

    Polyline& operator+=(const Point<T>& point) {
        if (count >= capacity) {
            expand();
        }
        points[count++] = point;
        return *this;
    }

    friend Polyline operator+(const Point<T>& point, const Polyline& polyline) {
        Polyline result(polyline.count + 1);
        result.points[0] = point;
        for (size_t i = 0; i < polyline.count; ++i) {
            result.points[i + 1] = polyline.points[i];
        }
        result.count = polyline.count + 1;
        return result;
    }

    bool operator==(const Polyline& other) const {
        if (count != other.count) {
            return false;
        }
        for (size_t i = 0; i < count; ++i) {
            if constexpr (std::is_floating_point_v<T>) {
                if (std::abs(points[i].x - other.points[i].x) > epsilon ||
                    std::abs(points[i].y - other.points[i].y) > epsilon) {
                    return false;
                }
            }
            else {
                if (points[i].x != other.points[i].x || points[i].y != other.points[i].y) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Polyline& other) const {
        return !(*this == other);
    }

    double length() const {
        double totalLength = 0.0;
        for (size_t i = 1; i < count; ++i) {
            totalLength += points[i - 1].distanceTo(points[i]);
        }
        return totalLength;
    }

    size_t size() const {
        return count;
    }

    void print() const {
        for (size_t i = 0; i < count; ++i) {
            std::cout << "Point " << i << ": (" << points[i].x << ", " << points[i].y << ")\n";
        }
    }
};