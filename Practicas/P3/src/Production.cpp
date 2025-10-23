#include "headers/Production.h"

Production::Production()
{    
}

Production::Production(Symbol head, vector<Symbol> body)
{
    this->head = head;
    this->body = body;
}

Production::~Production(){

}

Symbol Production::getHead()
{
    return head;
}

vector<Symbol> Production::getBody(){
    return body;
}
