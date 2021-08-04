/* 第一部分：C 语言开头程序 */
%{
#include <stdio.h>
%}

/* 第二部分（一）：正则表达式定义 */
template_base [0-9]
template {template_base}+

/* 第二部分（二）：动作 */
%%
{template} {;}
template {;}
"<" {;}
%%

/* 第三部分：辅助函数 */
int main() {}