/*
 * Perhaps it treads into the realm of premature optimization
 * but a trie version could be implemented later for better
 * performance.
 */

#pragma once
#ifndef WALMART_LUA_SCANNER
#define WALMART_LUA_SCANNER

#include <array>

/*
 * Supported tokens.
 */
#define TOKENS(x) \
  x(MOVE) \
  x(LOADK) \
  x(ADD) \
  x(SUB) \
  x(MUL) \
  x(DIV) 

/*
 * Generated tokens.
 */
#define MAKE_ENUM(token) token,
enum class Token { TOKENS(MAKE_ENUM) Unknown };
#undef MAKE_TOKEN

/*
 * Search table of token lexemes.
 */
#define MAKE_STRING(token) #token,
constexpr std::array<std::string_view, static_cast<size_t>(Token::Unknown)> token_strings = { TOKENS(MAKE_STRING) };
#undef MAKE_STRING

/*
 * Returns the corresponding token which matches the lexeme.
 */
[[ no_discard ]] auto get_token(const std::string& lexeme) -> Token
{
  auto found = std::find(token_strings.begin(), token_strings.end(), lexeme);
  size_t index = found - token_strings.begin();
  return static_cast<Token>(index);
};

#endif /* WALMART_LUA_SCANNER */
