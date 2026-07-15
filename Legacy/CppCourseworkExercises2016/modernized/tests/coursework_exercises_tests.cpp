#include "coursework_exercises.hpp"
#include "programming_exercises.hpp"

#include <climits>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace coursework = code_samples::coursework_2016;
namespace programming = code_samples::programming_exercises;

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

void test_array_ordering()
{
    const std::vector<int> first { 3, -1, 0 };
    const std::vector<int> second { 2, -3, 1, INT_MIN };
    expect(
        coursework::concatenate_sorted_by_absolute(first, second)
            == std::vector<int>({ 0, -1, 1, 2, 3, -3, INT_MIN }),
        "concatenate and stably order by absolute magnitude");
}

void test_search()
{
    const std::vector<int> values { -2, 0, 3, 3, 3, 7 };
    expect(coursework::count_in_sorted(values, 3) == 3, "count duplicate values");
    expect(coursework::count_in_sorted(values, 5) == 0, "report missing value");
    expect_throw<std::invalid_argument>(
        [] { (void)coursework::count_in_sorted(std::vector<int> { 2, 1 }, 1); },
        "reject unsorted binary-search input");
}

void test_list()
{
    coursework::singly_linked_list<std::string> values;
    expect(values.empty(), "create empty list");
    values.push_back("first");
    values.push_back("second");
    values.push_back("third");
    values.reverse();
    expect(
        values.values() == std::vector<std::string>({ "third", "second", "first" }),
        "reverse owned list");
    expect(values.pop_back() == "first" && values.size() == 2, "pop list tail");
    values.pop_back();
    values.pop_back();
    expect_throw<std::underflow_error>([&values] { (void)values.pop_back(); }, "reject empty pop");
}

void test_tree()
{
    coursework::binary_search_tree tree;
    for (const int value : { 5, 3, 7, 2, 4, 6, 8 }) {
        expect(tree.insert(value), "insert unique tree value");
    }
    expect(!tree.insert(7), "ignore duplicate tree value");
    expect(tree.contains(4) && !tree.contains(9), "find tree values");
    expect(tree.height() == 3, "calculate tree height");
    expect(tree.average_subtree_height() == 2.0, "calculate fractional-safe subtree average");
    expect(tree.inorder() == std::vector<int>({ 2, 3, 4, 5, 6, 7, 8 }), "traverse tree in order");
}

void test_shared_transpose()
{
    expect(
        programming::transpose<int>({ { 1, 2, 3 }, { 4, 5, 6 } })
            == programming::matrix<int>({ { 1, 4 }, { 2, 5 }, { 3, 6 } }),
        "reuse shared rectangular transpose");
}

} // namespace

int main()
{
    test_array_ordering();
    test_search();
    test_list();
    test_tree();
    test_shared_transpose();

    if (failures == 0) {
        std::cout << "C++ coursework exercise tests passed\n";
        return 0;
    }
    std::cerr << failures << " test assertion(s) failed\n";
    return 1;
}
