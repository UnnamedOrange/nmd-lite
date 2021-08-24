// Copyright (c) UnnamedOrange. Licensed under the MIT License.
// See the LICENSE file in the repository root for full license text.

#pragma once

#include <string>
#include <string_view>

#include <nmd-lex/lex_aux.hpp>
#include <nmd-lex/lex_interface.hpp>

_NMD_BEGIN
_LEX_BEGIN

class string_source : public source_interface
{
private:
	std::u32string _content;
	std::u32string::const_iterator _it{_content.cbegin()};

public:
	string_source() noexcept = default;
	string_source(std::u32string_view content) : _content(content) {}
	string_source(const string_source &) = delete;
	string_source& operator=(const string_source &) = delete;
	string_source(string_source &&another) noexcept
	{
		*this = std::move(another);
	}
	string_source& operator=(string_source &&another) noexcept
	{
		_content = std::move(another._content);
		_it = std::move(another._it);
		// another._it = another._content.cbegin();
		return *this;
	}

protected:
	[[nodiscard]] char32_t forward() override
	{
		return *(_it++);
	}
	void backward() override
	{
		--_it;
	}
	virtual bool eof_source() const override
	{
		return _it == _content.cend();
	}
	virtual void reset_source() override
	{
		_it = _content.cbegin();
	}
};

_LEX_END
_NMD_END