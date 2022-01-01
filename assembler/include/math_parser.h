#if !defined(MATH_PARSER_HH)
#define MATH_PARSER_HH
#include <string>
#include <vector>
#include <exception>
#include <cmath>

struct Expression {
    Expression(std::string token) : token(token) {} // Конструктор для чисел
    Expression(std::string token, Expression a) : token(token), args{a} {} // Конструктор унарных операций
    Expression(std::string token, Expression a, Expression b) : token(token), args{a, b} {} // Конструктор бинарных операций

    std::string token; // Операция или число
    std::vector<Expression> args; // Выражения - аргументы операции
};

class Parser {
public:
    explicit Parser(std::string input) : input(&input[0]) {} // Конструктор, принимает строку с выражением
    Expression parse(); // Основная функция парсинга
private:
    std::string parse_token(); // Парсит один токен
    Expression parse_simple_expression(); // Парсит простое выражение
    Expression parse_binary_expression(int min_priority); // Парсит бинарное выражение

    char* input; // Кусок строки, который еще не распарсили
};

double eval(const Expression& e);

#endif // MATH_PARSER_HH
