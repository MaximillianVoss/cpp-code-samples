#include "alexandra_assignments.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace assignments = code_samples::alexandra_2015;

namespace {

int failures = 0;

void expect(bool condition, const std::string& name)
{
    if (!condition) {
        ++failures;
        std::cerr << "FAILED: " << name << '\n';
    }
}

template <typename Exception, typename Action>
void expect_throw(Action action, const std::string& name)
{
    try {
        action();
        expect(false, name);
    } catch (const Exception&) {
        expect(true, name);
    } catch (...) {
        expect(false, name + " (wrong exception)");
    }
}

void test_quick_sort()
{
    std::vector<int> values { 5, 1, 3, 3, -2, 9, 1 };
    assignments::quick_sort<int>(values);
    expect(values == std::vector<int>({ -2, 1, 1, 3, 3, 5, 9 }), "sort duplicates ascending");

    assignments::quick_sort<int>(values, std::greater<int> {});
    expect(values == std::vector<int>({ 9, 5, 3, 3, 1, 1, -2 }), "sort descending");

    std::vector<int> empty;
    assignments::quick_sort<int>(empty);
    std::vector<int> single { 42 };
    assignments::quick_sort<int>(single);
    expect(empty.empty() && single == std::vector<int>({ 42 }), "sort empty and single values");
}

void test_dynamic_array()
{
    assignments::dynamic_array<std::string> values;
    values.push_back("first");
    values.push_back("third");
    values.insert(1, "second");
    values.insert(values.size(), "fourth");
    expect(values.values() == std::vector<std::string>({ "first", "second", "third", "fourth" }),
        "insert at middle and end");
    values.erase(0);
    expect(values.pop_back() == "fourth", "pop returns the last value");
    expect(values.values() == std::vector<std::string>({ "second", "third" }), "erase compacts values");

    expect_throw<std::out_of_range>([&values] { values.insert(4, "invalid"); }, "reject insert past end");
    expect_throw<std::out_of_range>([&values] { values.erase(2); }, "reject erase past end");
    assignments::dynamic_array<int> empty;
    expect_throw<std::underflow_error>([&empty] { (void)empty.pop_back(); }, "reject empty pop");
}

void test_line_intersection()
{
    using assignments::line_relation;
    using assignments::point;

    const auto vertical = assignments::line::through({ 2.0, -1.0 }, { 2.0, 5.0 });
    const auto horizontal = assignments::line::through({ -3.0, 3.0 }, { 7.0, 3.0 });
    const auto crossing = assignments::intersect_lines(vertical, horizontal);
    expect(crossing.relation == line_relation::unique && crossing.position.has_value()
            && assignments::nearly_equal(*crossing.position, point { 2.0, 3.0 }),
        "intersect vertical and horizontal lines");

    const auto parallel = assignments::intersect_lines(
        assignments::line::through({ 0.0, 0.0 }, { 2.0, 0.0 }),
        assignments::line::through({ 0.0, 1.0 }, { 2.0, 1.0 }));
    expect(parallel.relation == line_relation::parallel && !parallel.position.has_value(),
        "classify parallel lines");

    const auto coincident = assignments::intersect_lines(
        assignments::line::through({ 0.0, 0.0 }, { 2.0, 2.0 }),
        assignments::line::through({ 6.0, 6.0 }, { 3.0, 3.0 }));
    expect(coincident.relation == line_relation::coincident, "classify proportional coincident lines");
    expect_throw<std::invalid_argument>(
        [] { (void)assignments::line::through({ 1.0, 1.0 }, { 1.0, 1.0 }); },
        "reject degenerate line");
}

void test_segment_intersection()
{
    using assignments::point;
    using assignments::segment_intersection_kind;

    const auto crossing = assignments::intersect_segments(
        { { 0.0, 0.0 }, { 2.0, 2.0 } },
        { { 0.0, 2.0 }, { 2.0, 0.0 } });
    expect(crossing.kind == segment_intersection_kind::point && crossing.first.has_value()
            && assignments::nearly_equal(*crossing.first, point { 1.0, 1.0 }),
        "find proper segment crossing");

    const auto endpoint = assignments::intersect_segments(
        { { 0.0, 0.0 }, { 2.0, 0.0 } },
        { { 2.0, 0.0 }, { 2.0, 3.0 } });
    expect(endpoint.kind == segment_intersection_kind::point && endpoint.first.has_value()
            && assignments::nearly_equal(*endpoint.first, point { 2.0, 0.0 }),
        "include shared endpoint");

    const auto overlap = assignments::intersect_segments(
        { { 0.0, 0.0 }, { 4.0, 0.0 } },
        { { 2.0, 0.0 }, { 6.0, 0.0 } });
    expect(overlap.kind == segment_intersection_kind::overlap
            && assignments::nearly_equal(*overlap.first, point { 2.0, 0.0 })
            && assignments::nearly_equal(*overlap.second, point { 4.0, 0.0 }),
        "report collinear overlap");

    const auto disjoint = assignments::intersect_segments(
        { { 0.0, 0.0 }, { 1.0, 0.0 } },
        { { 2.0, 0.0 }, { 3.0, 0.0 } });
    expect(disjoint.kind == segment_intersection_kind::none, "reject disjoint collinear segments");

    const auto point_on_segment = assignments::intersect_segments(
        { { 1.0, 1.0 }, { 1.0, 1.0 } },
        { { 0.0, 0.0 }, { 2.0, 2.0 } });
    expect(point_on_segment.kind == segment_intersection_kind::point,
        "support a degenerate point segment");
}

} // namespace

int main()
{
    test_quick_sort();
    test_dynamic_array();
    test_line_intersection();
    test_segment_intersection();

    if (failures == 0) {
        std::cout << "Alexandra C++ assignment tests passed\n";
        return 0;
    }
    std::cerr << failures << " test assertion(s) failed\n";
    return 1;
}
