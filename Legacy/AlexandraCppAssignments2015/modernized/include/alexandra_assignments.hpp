#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <functional>
#include <iterator>
#include <optional>
#include <span>
#include <stdexcept>
#include <utility>
#include <vector>

namespace code_samples::alexandra_2015 {

template <typename T>
class dynamic_array {
public:
    [[nodiscard]] bool empty() const noexcept { return values_.empty(); }
    [[nodiscard]] std::size_t size() const noexcept { return values_.size(); }
    [[nodiscard]] const std::vector<T>& values() const noexcept { return values_; }

    void push_back(T value)
    {
        values_.push_back(std::move(value));
    }

    void insert(std::size_t index, T value)
    {
        if (index > values_.size()) {
            throw std::out_of_range("insert index exceeds array size");
        }
        values_.insert(values_.begin() + static_cast<std::ptrdiff_t>(index), std::move(value));
    }

    T pop_back()
    {
        if (values_.empty()) {
            throw std::underflow_error("cannot pop from an empty array");
        }
        T result = std::move(values_.back());
        values_.pop_back();
        return result;
    }

    void erase(std::size_t index)
    {
        if (index >= values_.size()) {
            throw std::out_of_range("erase index exceeds array size");
        }
        values_.erase(values_.begin() + static_cast<std::ptrdiff_t>(index));
    }

private:
    std::vector<T> values_;
};

template <typename T, typename Compare = std::less<T>>
void quick_sort(std::span<T> values, Compare compare = {})
{
    if (values.size() < 2) {
        return;
    }

    const T pivot = values[values.size() / 2];
    const auto less_end = std::partition(values.begin(), values.end(), [&](const T& value) {
        return compare(value, pivot);
    });
    const auto equal_end = std::partition(less_end, values.end(), [&](const T& value) {
        return !compare(pivot, value);
    });

    const auto less_size = static_cast<std::size_t>(std::distance(values.begin(), less_end));
    const auto greater_offset = static_cast<std::size_t>(std::distance(values.begin(), equal_end));
    quick_sort<T, Compare>(values.first(less_size), compare);
    quick_sort<T, Compare>(values.subspan(greater_offset), compare);
}

inline constexpr double default_epsilon = 1e-9;

struct point {
    double x;
    double y;

    friend bool operator==(const point&, const point&) = default;
};

[[nodiscard]] inline bool nearly_equal(double left, double right, double epsilon = default_epsilon) noexcept
{
    const double scale = std::max({ 1.0, std::abs(left), std::abs(right) });
    return std::abs(left - right) <= epsilon * scale;
}

[[nodiscard]] inline bool nearly_equal(point left, point right, double epsilon = default_epsilon) noexcept
{
    return nearly_equal(left.x, right.x, epsilon) && nearly_equal(left.y, right.y, epsilon);
}

struct line {
    double a;
    double b;
    double c;

    [[nodiscard]] static line through(point first, point second, double epsilon = default_epsilon)
    {
        if (nearly_equal(first, second, epsilon)) {
            throw std::invalid_argument("two distinct points are required to define a line");
        }
        return {
            first.y - second.y,
            second.x - first.x,
            first.x * second.y - second.x * first.y,
        };
    }
};

enum class line_relation {
    unique,
    parallel,
    coincident,
};

struct line_intersection {
    line_relation relation;
    std::optional<point> position;
};

[[nodiscard]] inline line_intersection intersect_lines(
    line first,
    line second,
    double epsilon = default_epsilon) noexcept
{
    const double determinant = first.a * second.b - second.a * first.b;
    if (!nearly_equal(determinant, 0.0, epsilon)) {
        return {
            line_relation::unique,
            point {
                (first.b * second.c - second.b * first.c) / determinant,
                (first.c * second.a - second.c * first.a) / determinant,
            },
        };
    }

    const bool same_ac = nearly_equal(first.a * second.c, second.a * first.c, epsilon);
    const bool same_bc = nearly_equal(first.b * second.c, second.b * first.c, epsilon);
    return { same_ac && same_bc ? line_relation::coincident : line_relation::parallel, std::nullopt };
}

struct segment {
    point first;
    point second;
};

enum class segment_intersection_kind {
    none,
    point,
    overlap,
};

struct segment_intersection {
    segment_intersection_kind kind;
    std::optional<point> first;
    std::optional<point> second;
};

[[nodiscard]] inline double cross(point origin, point first, point second) noexcept
{
    return (first.x - origin.x) * (second.y - origin.y)
        - (first.y - origin.y) * (second.x - origin.x);
}

[[nodiscard]] inline bool contains(segment value, point candidate, double epsilon = default_epsilon) noexcept
{
    if (!nearly_equal(cross(value.first, value.second, candidate), 0.0, epsilon)) {
        return false;
    }
    return candidate.x >= std::min(value.first.x, value.second.x) - epsilon
        && candidate.x <= std::max(value.first.x, value.second.x) + epsilon
        && candidate.y >= std::min(value.first.y, value.second.y) - epsilon
        && candidate.y <= std::max(value.first.y, value.second.y) + epsilon;
}

[[nodiscard]] inline int orientation_sign(double value, double epsilon) noexcept
{
    if (nearly_equal(value, 0.0, epsilon)) {
        return 0;
    }
    return value < 0.0 ? -1 : 1;
}

[[nodiscard]] inline segment_intersection intersect_segments(
    segment first,
    segment second,
    double epsilon = default_epsilon)
{
    const bool first_is_point = nearly_equal(first.first, first.second, epsilon);
    const bool second_is_point = nearly_equal(second.first, second.second, epsilon);
    if (first_is_point || second_is_point) {
        if (first_is_point && second_is_point) {
            return nearly_equal(first.first, second.first, epsilon)
                ? segment_intersection { segment_intersection_kind::point, first.first, std::nullopt }
                : segment_intersection { segment_intersection_kind::none, std::nullopt, std::nullopt };
        }
        const point candidate = first_is_point ? first.first : second.first;
        const segment other = first_is_point ? second : first;
        return contains(other, candidate, epsilon)
            ? segment_intersection { segment_intersection_kind::point, candidate, std::nullopt }
            : segment_intersection { segment_intersection_kind::none, std::nullopt, std::nullopt };
    }

    const double first_to_second_start = cross(first.first, first.second, second.first);
    const double first_to_second_end = cross(first.first, first.second, second.second);
    const double second_to_first_start = cross(second.first, second.second, first.first);
    const double second_to_first_end = cross(second.first, second.second, first.second);

    const int s1 = orientation_sign(first_to_second_start, epsilon);
    const int s2 = orientation_sign(first_to_second_end, epsilon);
    const int s3 = orientation_sign(second_to_first_start, epsilon);
    const int s4 = orientation_sign(second_to_first_end, epsilon);

    if (s1 == 0 && s2 == 0 && s3 == 0 && s4 == 0) {
        std::vector<point> shared;
        for (const point candidate : { first.first, first.second, second.first, second.second }) {
            if (contains(first, candidate, epsilon) && contains(second, candidate, epsilon)
                && std::none_of(shared.begin(), shared.end(), [&](point existing) {
                    return nearly_equal(existing, candidate, epsilon);
                })) {
                shared.push_back(candidate);
            }
        }
        if (shared.empty()) {
            return { segment_intersection_kind::none, std::nullopt, std::nullopt };
        }
        std::sort(shared.begin(), shared.end(), [](point left, point right) {
            return left.x < right.x || (left.x == right.x && left.y < right.y);
        });
        if (shared.size() == 1) {
            return { segment_intersection_kind::point, shared.front(), std::nullopt };
        }
        return { segment_intersection_kind::overlap, shared.front(), shared.back() };
    }

    if (s1 * s2 > 0 || s3 * s4 > 0) {
        return { segment_intersection_kind::none, std::nullopt, std::nullopt };
    }

    const auto intersection = intersect_lines(
        line::through(first.first, first.second, epsilon),
        line::through(second.first, second.second, epsilon),
        epsilon);
    if (intersection.relation != line_relation::unique || !intersection.position.has_value()) {
        return { segment_intersection_kind::none, std::nullopt, std::nullopt };
    }
    return { segment_intersection_kind::point, intersection.position, std::nullopt };
}

} // namespace code_samples::alexandra_2015
