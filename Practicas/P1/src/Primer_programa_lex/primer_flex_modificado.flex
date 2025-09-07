%{
    #include <iostream>
%}

%option c++
%option noyywrap

digito [0-9]
letra [a-zA-Z]
digitoHex [0-9A-Fa-f]
prefijoHex 0[xX]
espacio [ \t\n]

reservadas for|if|while|return|int
numHex {prefijoHex}{digitoHex}+
identificador ({letra}|_)({letra}|{digito}|_){1,31}

%%

{espacio} {}
{reservadas} { std::cout << "Encontré una palabra reservada: " << yytext << std::endl; }
{digito}+ { std::cout << "Encontré un número: " << yytext << std::endl; }
{numHex} { std::cout << "Encontré un número hexadecimal: " << yytext << std::endl; }
{identificador} { std::cout << "Encontré un identificador: " << yytext << std::endl; } 


%%

int main() {
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
}