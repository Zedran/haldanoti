#pragma once

#include <cstddef>
#include <span>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/GameRow.hpp"
#include "app/SecretRow.hpp"
#include "theme/Board.hpp"
#include "ui/Box.hpp"

namespace app {

// Top-level container for the game display.
class Board final : public ui::Box {
public:
    // Size relative to outer container.
    static constexpr sf::Vector2f REL_SIZE{0.90f, 0.88f};

    Board(const sf::Font& font, sf::Vector2f size, theme::Board theme);

    ~Board();

    // Displays the secret code and the result.
    void end_game(std::span<const int, game::Row::ROW_LEN> good_code, bool won);

    // Returns a mutable reference to the currently active GameRow.
    GameRow& get_active_row() const noexcept;

    // Returns true if currently active GameRow is the last available row.
    bool is_last_row() const noexcept;

    // Unlocks the next GameRow. Calling this function to progress past
    // the last row of the Board will cause assertion error.
    void next_row();

    // Resets the Board instance.
    void reset();

private:
    // Index of the currently active GameRow.
    std::size_t active_row_;

    // Stores non-owning pointers to GameRow instances.
    std::vector<GameRow*> game_rows_;

    // Holds a non-owning pointer to the SecretRow instance.
    SecretRow* secret_row_;
};

} // namespace app
