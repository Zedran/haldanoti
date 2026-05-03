#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "utils/utils.hpp"

namespace utils {

sf::Color decode_color(std::string html_code) {
    constexpr std::size_t SIZE_RGB  = 6;
    constexpr std::size_t SIZE_RGBA = 8;
    constexpr const char* ALPHA_100 = "ff";

    const std::size_t first_index = (html_code.front() == '#') ? 1 : 0;

    switch (html_code.size() - first_index) {
    case SIZE_RGB:  html_code += ALPHA_100; break;
    case SIZE_RGBA: break;
    default:        throw std::runtime_error{"invalid color code \"" + html_code + '"'};
    }

    const unsigned long long hex = std::stoull(html_code.substr(first_index), nullptr, 16);
    return sf::Color{static_cast<std::uint32_t>(hex)};
}

} // namespace utils
