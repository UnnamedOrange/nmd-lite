/* 第一部分：C++ 开头程序 */
%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <format>

enum class token_t : int
{
	eof = 0,
	unused,
	command,
};

inline std::string my_command_name;
%}

/* 第二部分（零）：状态定义 */
%s MAKEATLETTER

/* 第二部分（一）：正则表达式定义 */
command_no_at [A-Za-z]+
command_with_at [@A-Za-z]+

/* 第二部分（二）：动作 */
%%
\\makeatletter {
	BEGIN MAKEATLETTER;
	my_command_name = yytext;
	return static_cast<int>(token_t::command);
}
\\makeatother {
	BEGIN INITIAL;
	my_command_name = yytext;
	return static_cast<int>(token_t::command);
}
<INITIAL>\\{command_no_at} |
<MAKEATLETTER>\\{command_with_at} {
	my_command_name = yytext;
	return static_cast<int>(token_t::command);
}

. { return static_cast<int>(token_t::unused); } /* 抑制输出 */
%%

/* 第三部分：辅助函数 */

/* 若 yywrap 返回 0，则继续扫描；返回 1，则词法分析器返回报告文件已结束的 0。*/
int yywrap()
{
	return 1;
}

int main(int argn, char** argv)
{
	if (argn > 1)
	{
		if ((yyin = std::fopen(argv[1], "r")) == NULL)
		{
			std::cout << std::format("Can't open file {0}", argv[1]) << std::endl;
			return 1;
		}
	}
	else
		yyin = stdin;

	token_t ret;
	do
	{
		ret = static_cast<token_t>(yylex());
		if (ret > token_t::unused)
		{
			std::cout << std::endl <<
				std::format("yylex returns with: {}", static_cast<int>(ret)) << std::endl;
			std::cout << std::format("yytext is: {}", yytext) << std::endl;

			switch (ret)
			{
			case token_t::command:
			{
				std::cout << std::format("command name is: {}", my_command_name) << std::endl;
				break;
			}
			default:
				break;
			}
		}
	} while (ret != token_t::eof);

	if (yyin)
		std::fclose(yyin);
}
