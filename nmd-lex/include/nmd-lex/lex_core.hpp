// Copyright (c) UnnamedOrange. Licensed under the MIT License.
// See the LICENSE file in the repository root for full license text.

#pragma once

#include <cctype>
#include <algorithm>
#include <stdexcept>
#include <array>
#include <concepts>

#include <nmd-lex/lex_aux.hpp>
#include <nmd-lex/lex_interface.hpp>
#include <nmd-lex/string_source.hpp>

_NMD_BEGIN
_LEX_BEGIN

enum class token_t : size_t
{
	_reserved_begin,

	unknown,
	any,
	spaces,
	enumerate,

	next_line,
	backslash,
	subsubsection,
	subsection,
	section,
	chapter,
	math,
	inline_math,
	left_brace,
	right_brace,
	star,
	itemize,
	definition,
	proposition,
	theorem,
	proof,
	solve,
	example,
	exercise,
	interval, // 、
	colon,

	_reserved_end,
};

inline constexpr std::array token_strings =
	std::to_array<std::u32string_view>(
		{
			U"", // Unused.
			U"", // Unused.
			U"", // Unused.
			U"", // Unused.
			U"", // Unused.
			U"\n",
			U"\\",
			U"####",
			U"###",
			U"##",
			U"#",
			U"$$",
			U"$",
			U"{",
			U"}",
			U"*",
			U"-",
			U"Def",
			U"Prop",
			U"Theorem",
			U"Proof",
			U"Solve",
			U"Example",
			U"Exercise",
			U"、",
			U":",
		});
inline constexpr token_t simple_token_begin = token_t::next_line;

template <std::derived_from<source_interface> source_t>
class lex_core : public lex_interface, public source_t
{
private:
	[[nodiscard]] static std::pair<token_t, size_t> determine_token(std::u32string_view str)
	{
		for (token_t to_check = simple_token_begin; to_check < token_t::_reserved_end;
			 to_check = static_cast<token_t>(static_cast<size_t>(to_check) + 1))
			if (str.ends_with(token_strings[static_cast<size_t>(to_check)]))
				return {to_check, token_strings[static_cast<size_t>(to_check)].size()};

		{
			if (str.ends_with(U"."))
			{
				size_t number_size = 0;
				for (auto it = str.crbegin() + 1; it != str.crend(); it++)
					if (U'0' <= *it && *it <= U'9')
						number_size++;
					else
						break;
				if (number_size)
					return {token_t::enumerate, number_size + 1};
			}
		}
		{
			size_t space_size = 0;
			for (auto it = str.crbegin(); it != str.crend(); it++)
				if (*it == U' ')
					space_size++;
				else
					break;
			if (space_size)
				return {token_t::spaces, space_size};
		}

		return {token_t::any, str.size()};
	}

public:
	[[nodiscard]] std::pair<token_t, std::u32string> next() override
	{
		if (source_t::eof_source())
			throw std::overflow_error("EOF has been reached.");

		std::u32string buf;
		auto pre_token = determine_token(buf);
		do
		{
			buf.push_back(source_t::forward());

			auto crt_token = determine_token(buf);
			if (crt_token.first != token_t::any &&
				buf.size() != crt_token.second)
			{
				for (size_t i = 0; i < crt_token.second; i++)
				{
					source_t::backward();
					buf.pop_back();
				}
				break;
			}
			else if (crt_token.first == token_t::any &&
					 pre_token.first != token_t::any)
			{
				source_t::backward();
				buf.pop_back();
				break;
			}

			pre_token = std::move(crt_token);
		} while (!source_t::eof_source());
		return {determine_token(buf).first, buf};
	}
	bool eof() const override
	{
		return source_t::eof_source();
	}
	void reset() override
	{
		source_t::reset_source();
	}

public:
	using source_t::source_t;
};

_LEX_END
_NMD_END