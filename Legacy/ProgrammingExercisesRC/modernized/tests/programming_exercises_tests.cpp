#include "programming_exercises.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace exercises = code_samples::programming_exercises;

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

void test_transpose()
{
    expect(
        exercises::transpose<int>({ { 1, 2, 3 }, { 4, 5, 6 } })
            == exercises::matrix<int>({ { 1, 4 }, { 2, 5 }, { 3, 6 } }),
        "transpose rectangular matrix");
    expect(
        exercises::transpose<int>({ { 1, 2 }, { 3, 4 } })
            == exercises::matrix<int>({ { 1, 3 }, { 2, 4 } }),
        "transpose square matrix");
    expect(exercises::transpose<int>({}).empty(), "transpose empty matrix");
    expect_throw<std::invalid_argument>(
        [] { (void)exercises::transpose<int>({ { 1, 2 }, { 3 } }); },
        "reject ragged matrix");
}

void test_brackets()
{
    expect(exercises::check_brackets("([]{})").balanced, "accept balanced brackets");
    expect(exercises::check_brackets("call(values[0])").balanced, "ignore non-bracket text");

    const auto mismatch = exercises::check_brackets("{]");
    expect(
        !mismatch.balanced && mismatch.error == exercises::bracket_error::mismatched_closing
            && mismatch.offset == 1 && mismatch.expected == '}',
        "report mismatched closing bracket");

    const auto unexpected = exercises::check_brackets("]");
    expect(
        !unexpected.balanced && unexpected.error == exercises::bracket_error::unexpected_closing
            && unexpected.offset == 0,
        "report unexpected closing bracket");

    const auto unclosed = exercises::check_brackets("([");
    expect(
        !unclosed.balanced && unclosed.error == exercises::bracket_error::unclosed_opening
            && unclosed.offset == 1 && unclosed.expected == ']',
        "report unclosed opening bracket");
}

void test_circular_queue()
{
    exercises::circular_queue<int> queue(3);
    expect(queue.empty() && queue.capacity() == 3, "create empty bounded queue");

    queue.push(1);
    queue.push(2);
    expect(queue.pop() == 1, "pop first value");
    queue.push(3);
    queue.push(4);
    expect(queue.full() && queue.front() == 2, "wrap queue storage");
    expect_throw<std::overflow_error>([&queue] { queue.push(5); }, "reject queue overflow");

    expect(queue.pop() == 2, "preserve second value");
    expect(queue.pop() == 3, "preserve wrapped third value");
    expect(queue.pop() == 4 && queue.empty(), "drain queue in FIFO order");
    expect_throw<std::underflow_error>([&queue] { (void)queue.pop(); }, "reject queue underflow");
    expect_throw<std::invalid_argument>([] { exercises::circular_queue<int> invalid(0); }, "reject zero capacity");
}

} // namespace

int main()
{
    test_transpose();
    test_brackets();
    test_circular_queue();

    if (failures == 0) {
        std::cout << "Programming exercises tests passed\n";
        return 0;
    }
    std::cerr << failures << " test assertion(s) failed\n";
    return 1;
}
