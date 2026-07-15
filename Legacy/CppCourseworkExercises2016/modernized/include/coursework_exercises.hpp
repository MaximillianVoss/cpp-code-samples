#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>
#include <stdexcept>
#include <utility>
#include <vector>

namespace code_samples::coursework_2016 {

[[nodiscard]] inline std::vector<int> concatenate_sorted_by_absolute(
    std::span<const int> first,
    std::span<const int> second)
{
    std::vector<int> result;
    result.reserve(first.size() + second.size());
    result.insert(result.end(), first.begin(), first.end());
    result.insert(result.end(), second.begin(), second.end());

    const auto magnitude = [](int value) {
        const auto wide = static_cast<std::int64_t>(value);
        return static_cast<std::uint64_t>(wide < 0 ? -wide : wide);
    };
    std::stable_sort(result.begin(), result.end(), [&](int left, int right) {
        return magnitude(left) < magnitude(right);
    });
    return result;
}

[[nodiscard]] inline std::size_t count_in_sorted(
    std::span<const int> values,
    int needle)
{
    if (!std::is_sorted(values.begin(), values.end())) {
        throw std::invalid_argument("count_in_sorted requires sorted input");
    }
    const auto range = std::equal_range(values.begin(), values.end(), needle);
    return static_cast<std::size_t>(std::distance(range.first, range.second));
}

template <typename T>
class singly_linked_list {
private:
    struct node {
        explicit node(T item)
            : value(std::move(item))
        {
        }

        T value;
        std::unique_ptr<node> next;
    };

public:
    [[nodiscard]] bool empty() const noexcept { return head_ == nullptr; }
    [[nodiscard]] std::size_t size() const noexcept { return size_; }

    void push_back(T value)
    {
        auto added = std::make_unique<node>(std::move(value));
        node* added_raw = added.get();
        if (tail_ == nullptr) {
            head_ = std::move(added);
        } else {
            tail_->next = std::move(added);
        }
        tail_ = added_raw;
        ++size_;
    }

    T pop_back()
    {
        if (head_ == nullptr) {
            throw std::underflow_error("cannot pop from an empty list");
        }
        if (head_.get() == tail_) {
            T value = std::move(head_->value);
            head_.reset();
            tail_ = nullptr;
            size_ = 0;
            return value;
        }

        node* previous = head_.get();
        while (previous->next.get() != tail_) {
            previous = previous->next.get();
        }
        T value = std::move(tail_->value);
        previous->next.reset();
        tail_ = previous;
        --size_;
        return value;
    }

    void reverse() noexcept
    {
        node* old_head = head_.get();
        std::unique_ptr<node> previous;
        auto current = std::move(head_);
        while (current != nullptr) {
            auto next = std::move(current->next);
            current->next = std::move(previous);
            previous = std::move(current);
            current = std::move(next);
        }
        head_ = std::move(previous);
        tail_ = old_head;
    }

    [[nodiscard]] std::vector<T> values() const
    {
        std::vector<T> result;
        result.reserve(size_);
        for (const node* current = head_.get(); current != nullptr; current = current->next.get()) {
            result.push_back(current->value);
        }
        return result;
    }

private:
    std::unique_ptr<node> head_;
    node* tail_ = nullptr;
    std::size_t size_ = 0;
};

class binary_search_tree {
private:
    struct node {
        explicit node(int item)
            : value(item)
        {
        }

        int value;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;
    };

public:
    bool insert(int value)
    {
        auto* destination = &root_;
        while (*destination != nullptr) {
            if (value == (*destination)->value) {
                return false;
            }
            destination = value < (*destination)->value
                ? &(*destination)->left
                : &(*destination)->right;
        }
        *destination = std::make_unique<node>(value);
        return true;
    }

    [[nodiscard]] bool contains(int value) const noexcept
    {
        const node* current = root_.get();
        while (current != nullptr) {
            if (value == current->value) {
                return true;
            }
            current = value < current->value ? current->left.get() : current->right.get();
        }
        return false;
    }

    [[nodiscard]] std::size_t height() const noexcept { return height_of(root_.get()); }

    [[nodiscard]] double average_subtree_height() const noexcept
    {
        if (root_ == nullptr) {
            return 0.0;
        }
        return (static_cast<double>(height_of(root_->left.get()))
                   + static_cast<double>(height_of(root_->right.get())))
            / 2.0;
    }

    [[nodiscard]] std::vector<int> inorder() const
    {
        std::vector<int> result;
        append_inorder(root_.get(), result);
        return result;
    }

private:
    static std::size_t height_of(const node* current) noexcept
    {
        if (current == nullptr) {
            return 0;
        }
        return 1 + std::max(height_of(current->left.get()), height_of(current->right.get()));
    }

    static void append_inorder(const node* current, std::vector<int>& result)
    {
        if (current == nullptr) {
            return;
        }
        append_inorder(current->left.get(), result);
        result.push_back(current->value);
        append_inorder(current->right.get(), result);
    }

    std::unique_ptr<node> root_;
};

} // namespace code_samples::coursework_2016
