#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <random>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

namespace code_samples::drunkard {

enum class rank : std::uint8_t {
    six = 6,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace,
};

enum class suit : std::uint8_t {
    clubs,
    diamonds,
    hearts,
    spades,
};

struct card {
    rank value;
    suit kind;

    friend bool operator==(const card&, const card&) = default;
};

enum class round_winner {
    tie,
    first_player,
    second_player,
};

enum class game_outcome {
    first_player,
    second_player,
    draw,
    round_limit,
};

struct round_result {
    round_winner winner;
    std::size_t cards_played;
    bool terminal;
};

struct game_result {
    game_outcome outcome;
    std::size_t rounds;

    friend bool operator==(const game_result&, const game_result&) = default;
};

struct dealt_hands {
    std::deque<card> first;
    std::deque<card> second;

    friend bool operator==(const dealt_hands&, const dealt_hands&) = default;
};

[[nodiscard]] inline round_winner compare_cards(card first, card second) noexcept
{
    if (first.value == second.value) {
        return round_winner::tie;
    }

    // This nonstandard rule is explicit in the earliest recovered implementation.
    if (first.value == rank::six && second.value == rank::ace) {
        return round_winner::first_player;
    }
    if (first.value == rank::ace && second.value == rank::six) {
        return round_winner::second_player;
    }
    return first.value > second.value
        ? round_winner::first_player
        : round_winner::second_player;
}

[[nodiscard]] inline std::vector<card> make_standard_deck()
{
    constexpr std::array ranks {
        rank::six,
        rank::seven,
        rank::eight,
        rank::nine,
        rank::ten,
        rank::jack,
        rank::queen,
        rank::king,
        rank::ace,
    };
    constexpr std::array suits {
        suit::clubs,
        suit::diamonds,
        suit::hearts,
        suit::spades,
    };

    std::vector<card> deck;
    deck.reserve(ranks.size() * suits.size());
    for (const rank value : ranks) {
        for (const suit kind : suits) {
            deck.push_back({ value, kind });
        }
    }
    return deck;
}

[[nodiscard]] inline dealt_hands deal(std::uint32_t seed)
{
    auto deck = make_standard_deck();
    std::mt19937 generator(seed);
    std::shuffle(deck.begin(), deck.end(), generator);

    dealt_hands result;
    for (std::size_t index = 0; index < deck.size(); ++index) {
        (index % 2 == 0 ? result.first : result.second).push_back(deck[index]);
    }
    return result;
}

class game {
public:
    explicit game(dealt_hands hands)
        : first_(std::move(hands.first))
        , second_(std::move(hands.second))
    {
        validate_cards();
    }

    game(std::deque<card> first, std::deque<card> second)
        : game(dealt_hands { std::move(first), std::move(second) })
    {
    }

    [[nodiscard]] static game from_seed(std::uint32_t seed)
    {
        return game(deal(seed));
    }

    [[nodiscard]] const std::deque<card>& first_hand() const noexcept { return first_; }
    [[nodiscard]] const std::deque<card>& second_hand() const noexcept { return second_; }
    [[nodiscard]] const std::vector<card>& unclaimed_cards() const noexcept { return unclaimed_; }

    [[nodiscard]] std::size_t total_cards() const noexcept
    {
        return first_.size() + second_.size() + unclaimed_.size();
    }

    [[nodiscard]] bool terminal() const noexcept
    {
        return first_.empty() || second_.empty();
    }

    round_result play_round()
    {
        if (terminal()) {
            throw std::logic_error("cannot play a round after the game has ended");
        }

        std::vector<card> table;
        while (true) {
            if (first_.empty() || second_.empty()) {
                if (first_.empty() && second_.empty()) {
                    unclaimed_.insert(unclaimed_.end(), table.begin(), table.end());
                    return { round_winner::tie, table.size(), true };
                }

                const auto winner = first_.empty()
                    ? round_winner::second_player
                    : round_winner::first_player;
                append_table(winner, table);
                return { winner, table.size(), true };
            }

            const card first_card = take_front(first_);
            const card second_card = take_front(second_);
            table.push_back(first_card);
            table.push_back(second_card);

            const auto winner = compare_cards(first_card, second_card);
            if (winner == round_winner::tie) {
                continue;
            }

            append_table(winner, table);
            return { winner, table.size(), terminal() };
        }
    }

    [[nodiscard]] game_result play(std::size_t maximum_rounds)
    {
        std::size_t rounds = 0;
        while (!terminal() && rounds < maximum_rounds) {
            (void)play_round();
            ++rounds;
        }

        if (first_.empty() && second_.empty()) {
            return { game_outcome::draw, rounds };
        }
        if (first_.empty()) {
            return { game_outcome::second_player, rounds };
        }
        if (second_.empty()) {
            return { game_outcome::first_player, rounds };
        }
        return { game_outcome::round_limit, rounds };
    }

private:
    static card take_front(std::deque<card>& hand)
    {
        const card result = hand.front();
        hand.pop_front();
        return result;
    }

    void append_table(round_winner winner, const std::vector<card>& table)
    {
        auto& destination = winner == round_winner::first_player ? first_ : second_;
        destination.insert(destination.end(), table.begin(), table.end());
    }

    void validate_cards() const
    {
        std::set<std::pair<int, int>> identities;
        const auto add = [&identities](const std::deque<card>& hand) {
            for (const card current : hand) {
                const auto identity = std::pair {
                    static_cast<int>(current.value),
                    static_cast<int>(current.kind),
                };
                if (!identities.insert(identity).second) {
                    throw std::invalid_argument("a card occurs more than once");
                }
            }
        };
        add(first_);
        add(second_);
    }

    std::deque<card> first_;
    std::deque<card> second_;
    std::vector<card> unclaimed_;
};

} // namespace code_samples::drunkard
