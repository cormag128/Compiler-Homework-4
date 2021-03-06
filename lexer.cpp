#include "lexer.hpp"

//constructors
lexer::lexer(const char* f, const char *fi) : first(f), final(fi){}
lexer::lexer(const std::string& str) : lexer(&str[0], &str[0] + str.size()) {}

//checks to see if we are at the end of the string
bool lexer::eof()
{
    if (first == final)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//looks at the pointer to see what is held at this location
char lexer::lookahead()
{
    if (eof())
    {
        return 0;
    }
    else
    {
        return *first;
    }
}

// ignores whitespace
void lexer::ignoresp()
{
    while(!eof() && std::isspace(lookahead()))
    {
        ++first;
    }
}

//push the string into a temp that can then be lexed
char lexer::consume()
{
    if(!eof())
    {
        char tmp = *first++;
        buf.push_back(tmp);
        return tmp;
    }
    else
    {
        return 0;
    }
}

//will build the new token type that is given to it
token* lexer::addtoken(token_type t)
{
    ++first;
    token* tok = new token(t);
    tokenvec.push_back(tok);
    return tok;
}

//the actual lexer is designed to lex and build tokens as it reads them
token* lexer::lex()
{
    buf.clear();
    ignoresp();

    while(!eof())
    {
        switch(*first)
        {
            case '+':
                return addtoken(add_tok);
            case '-':
                return addtoken(minus_tok);
            case '*':
                return addtoken(mult_tok);
            case '/':
                return addtoken(div_tok);
            case '%':
                return addtoken(mod_tok);
            case '&&':
                return addtoken(and_tok);
            case '||':
                return addtoken(or_tok);
            case '!':
                return addtoken(exclamation_tok);
            case '==':
                return addtoken(equality_tok);
            case '!=':
                return addtoken(notequal_tok);
            case '<':
                return addtoken(lessthan_tok);
            case '>':
                return addtoken(greaterthan_tok);
            case '<=':
                return addtoken(lessorequal_tok);
            case '>=':
                return addtoken(greaterorequal_tok);
            case '?':
                return addtoken(question_tok);
            case ':':
                return addtoken(colon_tok);
            case '(':
                return addtoken(lparen_tok);
            case ')':
                return addtoken(rparen_tok);
            case 't':
                return addtoken(bool_tok);
            case 'f':
                return addtoken(bool_tok);
            default:
                if(std::isdigit(lookahead()))
                {
                    consume();
                    while (first != final && std::isdigit(lookahead()))
                    {
                        consume();
                    }

                    token* tok = new int_token(std::stoi(buf));
                    tokenvec.push_back(tok);
                    return tok;
                }
        }
    }
}
