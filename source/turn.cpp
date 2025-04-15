#include <sstream>

#include <bitboard/turn.hpp>

namespace bitboard
{

const static char kCodes[7] = {'\0', 'p', 'k', 'b', 'r', 'q', '\0'};

std::string Turn::toString() const
{
  if (!valid()) {
    return "0000";
  }
  if (static_cast<Figure>(m_figure) == Figure::kEmpty) {
    std::stringstream ss;
    ss << Position(m_from).toString() << Position(m_to).toString();
    return ss.str();
  }
  std::stringstream ss;
  ss << Position(m_from).toString() << Position(m_to).toString()
     << kCodes[static_cast<size_t>(m_figure)];
  return ss.str();
}

}  // namespace bitboard
