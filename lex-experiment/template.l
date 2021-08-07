/* 第一部分：C++ 开头程序 */
%{
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <format>
%}

/* 第二部分（一）：正则表达式定义 */
template_base [0-9]
template {template_base}+

/* 第二部分（二）：动作 */
%%
{template} { return 1; }
template {;}
"<" {;}
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

	while (int ret = yylex())
	{
		std::cout << std::format("yylex returns with: {}", ret) << std::endl;
	}

	if (yyin)
		std::fclose(yyin);
}
