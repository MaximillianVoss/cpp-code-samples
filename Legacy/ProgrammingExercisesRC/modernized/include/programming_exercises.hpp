#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string_view>
#include <utility>
#include <vector>

namespace code_samples::programming_exercises {

template <typename T>
using matrix = std::vector<std::vector<T>>;

template <typename T>
[[nodiscard]] matrix<T> transpose(const matrix<T>& input)
{
    if (input.empty()) {
        return {};
    }

    const std::size_t column_count = input.front().size();
    for (const auto& row : input) {
        if (row.size() != column_count) {
            throw std::invalid_argument("matrix rows must have equal lengths");
        }
    }

    matrix<T> result(column_count, std::vector<T>(input.size()));
    for (std::size_t row = 0; row < input.size(); ++row) {
        for (std::size_t column = 0; column < column_count; ++column) {
            result[column][row] = input[row][column];
        }
    }
    return result;
}

enum class bracket_error {
    none,
    unexpected_closing,
    mismatched_closing,
    unclosed_opening,
};

struct bracket_check_result {
    bool balanced;
    bracket_error error;
    std::size_t offset;
    char expected;
};

[[nodiscard]] inline bracket_check_result check_brackets(std::string_view text)
{
    std::vector<std::pair<char, std::size_t>> openings;

    const auto expected_closing = [](char opening) {
        switch (opening) {
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        default:
            return '\0';
        }
    };

    for (std::size_t offset = 0; offset < text.size(); ++offset) {
        const char current = text[offset];
        if (current == '(' || current == '[' || current == '{') {
            openings.emplace_back(current, offset);
            continue;
        }
        if (current != ')' && current != ']' && current != '}') {
            continue;
        }
        if (openings.empty()) {
            return { false, bracket_error::unexpected_closing, offset, '\0' };
        }

        const char expected = expected_closing(openings.back().first);
        if (current != expected) {
            return { false, bracket_error::mismatched_closing, offset, expected };
        }
        openings.pop_back();
    }

    if (!openings.empty()) {
        const auto [opening, offset] = openings.back();
        return { false, bracket_error::unclosed_opening, offset, expected_closing(opening) };
    }
    return { true, bracket_error::none, text.size(), '\0' };
}

template <typename T>
class circular_queue {
public:
    explicit circular_queue(std::size_t capacity)
        : storage_(capacity)
    {
        if (capacity == 0) {
            throw std::invalid_argument("queue capacity must be positive");
        }
    }

    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] bool full() const noexcept { return size_ == storage_.size(); }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }
    [[nodiscard]] std::size_t capacity() const noexcept { return storage_.size(); }

    void push(const T& value) { emplace(value); }
    void push(T&& value) { emplace(std::move(value)); }

    [[nodiscard]] const T& front() const
    {
        if (empty()) {
            throw std::underflow_error("queue is empty");
        }
        return *storage_[head_];
    }

    [[nodiscard]] T pop()
    {
        if (empty()) {
            throw std::underflow_error("queue is empty");
        }

        T value = std::move(*storage_[head_]);
        storage_[head_].reset();
        head_ = (head_ + 1) % storage_.size();
        --size_;
        return value;
    }

private:
    template <typename U>
    void emplace(U&& value)
    {
        if (full()) {
            throw std::overflow_error("queue is full");
        }
        storage_[tail_].emplace(std::forward<U>(value));
        tail_ = (tail_ + 1) % storage_.size();
        ++size_;
    }

    std::vector<std::optional<T>> storage_;
    std::size_t head_ = 0;
    std::size_t tail_ = 0;
    std::size_t size_ = 0;
};

} // namespace code_samples::programming_exercises
