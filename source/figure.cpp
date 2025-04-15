#include <bitboard/turn.hpp>

namespace bitboard
{

// const static char kCodes[7] = {'\0', 'p', 'k', 'b', 'r', 'q', '\0'};

// Turn::Turn(std::string_view chess_format)
// {
//   if (chess_format.size() != 5 && chess_format.size() != 4) {
//     *this = {};
//     return;
//   }

//   auto pos_from = Position(chess_format.substr(0, 2));
//   auto pos_to = Position(chess_format.substr(2, 2));

//   if (!pos_from.valid() || !pos_to.valid()) {
//     *this = {};
//     return;
//   }

//   m_from = pos_from.index();
//   m_to = pos_to.index();

//   if (chess_format.size() == 5) {
//     auto index = std::find(kCodes, kCodes + 7, chess_format[4]);
//     if (index == kCodes + 7) {
//       *this = {};
//       return;
//     }
//     m_figure = index - kCodes;
//   }
// }

}  // namespace bitboard
