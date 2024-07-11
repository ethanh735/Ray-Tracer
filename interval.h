#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
public:
    double min, max;

    interval() : min(+infinity), max(-infinity) {} // Default interval is empty

    interval(double min, double max) : min(min), max(max) {}

    double size() const {
        return max - min;
    }

    // returns true if x is within interval (inclusive)
    bool contains(double x) const {
        return min <= x && x <= max;
    }

    // returns true if x is within interval (exclusive)
    bool surrounds(double x) const {
        return min < x && x < max;
    }

    // doesn't return x if outside interval
    double clamp(double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const interval empty, universe;
};

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);

#endif