// Copyright (c) UnnamedOrange. Licensed under the MIT License.
// See the LICENSE file in the repository root for full license text.

#pragma once

#include <string>
#include <string_view>
#include <utility>

#include <nmd-lex/lex_aux.hpp>

_NMD_BEGIN
_LEX_BEGIN

class source_interface
{
protected:
	[[nodiscard]] virtual char32_t forward() = 0;
	virtual void backward() = 0;
	virtual bool eof_source() const = 0;
	virtual void reset_source() = 0;
};

enum class token_t
{
	_reserved,
	any,
};

class lex_interface
{
public:
	[[nodiscard]] virtual std::pair<token_t, std::u32string> next() = 0;
	virtual bool eof() const = 0;
	virtual void reset() = 0;
};

_LEX_END
_NMD_END