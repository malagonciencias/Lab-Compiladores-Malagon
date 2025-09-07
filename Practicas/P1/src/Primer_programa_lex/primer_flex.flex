%{
    #include <iostream>
%}

%option c++
%option noyywrap


digito [0-9]
letra [a-zA-Z]
palabra {letra}+
espacio [ \t\n]

%%

{espacio} {}
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl; }
{palabra} { std::cout << "Encontré una palabra: " << yytext << std::endl; }

%%

int main() {
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
}