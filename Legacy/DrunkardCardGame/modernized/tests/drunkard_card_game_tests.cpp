#include "drunkard_card_game.hpp"

#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

namespace drunkard = code_samples::drunkard;

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

constexpr drunkard::card make_card(drunkard::rank value, drunkard::suit kind)
{
    return { value, kind };
}

void test_standard_deck()
{
    const auto deck = drunkard::make_standard_deck();
    std::set<std::pair<int, int>> identities;
    for (const auto current : deck) {
        identities.emplace(static_cast<int>(current.value), static_cast<int>(current.kind));
    }
    expect(deck.size() == 36, "standard deck has 36 cards");
    expect(identities.size() == deck.size(), "standard deck cards are unique");
}

void test_comparison_rules()
{
    using enum drunkard::rank;
    using enum drunkard::round_winner;
    using enum drunkard::suit;

    expect(drunkard::compare_cards(make_card(six, clubs), make_card(ace, hearts)) == first_player,
        "six beats ace");
    expect(drunkard::compare_cards(make_card(ace, clubs), make_card(six, hearts)) == second_player,
        "ace loses to six");
    expect(drunkard::compare_cards(make_card(king, clubs), make_card(queen, hearts)) == first_player,
        "ordinary higher rank wins");
    expect(drunkard::compare_cards(make_card(ten, clubs), make_card(ten, hearts)) == tie,
        "equal ranks tie regardless of suit");
}

void test_deterministic_deal()
{
    const auto first = drunkard::deal(2016);
    const auto repeated = drunkard::deal(2016);
    expect(first == repeated, "same seed produces the same deal");
    expect(first.first.size() == 18 && first.second.size() == 18, "deal is balanced");

    drunkard::game dealt(first);
    expect(dealt.total_cards() == 36, "dealt game retains the complete deck");
}

void test_tied_battle_and_conservation()
{
    using enum drunkard::rank;
    using enum drunkard::round_winner;
    using enum drunkard::suit;

    drunkard::game game(
        { make_card(ten, clubs), make_card(six, diamonds) },
        { make_card(ten, hearts), make_card(ace, spades) });

    const auto result = game.play_round();
    expect(result.winner == first_player, "six-over-ace resolves a tied battle");
    expect(result.cards_played == 4, "all battle cards are collected");
    expect(game.first_hand().size() == 4 && game.second_hand().empty(), "winner receives the table");
    expect(game.total_cards() == 4, "battle conserves every card");
}

void test_simultaneous_exhaustion()
{
    using enum drunkard::game_outcome;
    using enum drunkard::rank;
    using enum drunkard::suit;

    drunkard::game game(
        { make_card(ten, clubs) },
        { make_card(ten, hearts) });

    expect(game.play(10) == drunkard::game_result { draw, 1 }, "last-card tie is a draw");
    expect(game.unclaimed_cards().size() == 2, "draw retains tied table cards");
    expect(game.total_cards() == 2, "draw conserves every card");
}

void test_one_sided_exhaustion_after_tie()
{
    using enum drunkard::rank;
    using enum drunkard::round_winner;
    using enum drunkard::suit;

    drunkard::game game(
        { make_card(ten, clubs) },
        { make_card(ten, hearts), make_card(nine, spades) });

    const auto result = game.play_round();
    expect(result.winner == second_player && result.terminal,
        "player able to continue receives a tied table");
    expect(game.first_hand().empty() && game.second_hand().size() == 3,
        "remaining player retains hand and table");
    expect(game.total_cards() == 3, "one-sided exhaustion conserves every card");
}

void test_limits_and_invalid_states()
{
    using enum drunkard::game_outcome;
    using enum drunkard::rank;
    using enum drunkard::suit;

    auto first = drunkard::game::from_seed(42);
    auto repeated = drunkard::game::from_seed(42);
    expect(first.play(25) == repeated.play(25), "bounded seeded games are reproducible");

    auto limited = drunkard::game::from_seed(7);
    expect(limited.play(0) == drunkard::game_result { round_limit, 0 }, "zero limit stops before play");
    expect(limited.total_cards() == 36, "round limit does not discard cards");

    const auto duplicate = make_card(ace, spades);
    expect_throw<std::invalid_argument>(
        [duplicate] { drunkard::game invalid({ duplicate }, { duplicate }); },
        "duplicate cards are rejected");

    drunkard::game finished({ make_card(ace, clubs) }, {});
    expect_throw<std::logic_error>([&finished] { (void)finished.play_round(); },
        "round cannot start after game end");
}

} // namespace

int main()
{
    test_standard_deck();
    test_comparison_rules();
    test_deterministic_deal();
    test_tied_battle_and_conservation();
    test_simultaneous_exhaustion();
    test_one_sided_exhaustion_after_tie();
    test_limits_and_invalid_states();

    if (failures == 0) {
        std::cout << "Drunkard card game tests passed\n";
        return 0;
    }
    std::cerr << failures << " test assertion(s) failed\n";
    return 1;
}
