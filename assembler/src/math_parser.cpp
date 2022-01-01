#include "math_parser.h"
#include <cstring>

std::string Parser::parse_token() {
    // Пропускаем пробелы перед токеном.        
    while (std::isspace(input[0])) ++input;

    // Если input начинается с цифры, то парсим число.
    if (std::isdigit(input[0])) {
        std::string number;
        int i = 0;
        while (std::isdigit(input[i]) || input[i] == '.') number.push_back(input[i]),i++;
        return number;
    }

    // Список всех известных токенов - операции и скобки.
    static const std::string tokens[] =
        { "+", "-", "**", "*", "/", "mod", "abs", "sin", "cos", "(", ")" };
    for (auto& t : tokens) {
        if (std::strncmp(input, t.c_str(), t.size()) == 0) {
            input += t.size();
            return t;
        }
    }

    return ""; // Какой-то неизвестный токен, или символ '\0' - конец строки.
}

Expression Parser::parse_simple_expression() {
    // Парсим первый токен.
    auto token = parse_token();
    if (token.empty()) // Неожиданный конец строки, или неизвестный токен
        throw "Invalid input";

    if (std::isdigit(token[0])) // Если это цифра, возвращаем выражение без аргументов
        return Expression(token);

    if (token == "(") {
        auto result = parse();
        if (parse_token() != ")") throw "Expected \')\'";
        return result; // Если это скобки, парсим и возвращаем выражение в скобках
    }

    // Иначе, это унарная операция ("-", "sin", и т.п.)
    auto arg = parse_simple_expression(); // Парсим ее аргумент.
    return Expression(token, arg);
}

int get_priority(const std::string& token) {
    if (token == "+") return 1;
    if (token == "-") return 1;
    if (token == "*") return 2;
    if (token == "/") return 2;
    if (token == "mod") return 2; // остаток от деления
    if (token == "**") return 3; // степень
    return 0; // Возвращаем 0 если токен - это не бинарная операция (например ")")
}

Expression Parser::parse_binary_expression(int min_priority) {
    auto left_expr = parse_simple_expression(); // Парсим простое выражение.

    for (;;) {
        auto op = parse_token(); // Пробуем парсить бинарную операцию.
        auto priority = get_priority(op);
        // Выходим из цикла если ее приоритет слишком низок (или это не бинарная операция).
        if (priority <= min_priority) {
            input -= op.size(); // Отдаем токен обратно,
            return left_expr; // возвращаем выражение слева.
        }

        // Парсим выражение справа. Текущая операция задает минимальный приоритет.
        auto right_expr = parse_binary_expression(priority);
        left_expr = Expression(op, left_expr, right_expr); // Обновляем выражение слева.
    } // Повторяем цикл: парсинг операции, и проверка ее приоритета.
}

Expression Parser::parse() {
    return parse_binary_expression(0);
}

double eval(const Expression& e) {
    switch (e.args.size()) {
        case 2: { // Два аргумента - бинарные операции.
            auto a = eval(e.args[0]);
            auto b = eval(e.args[1]);
            if (e.token == "+") return a + b;
            if (e.token == "-") return a - b;
            if (e.token == "*") return a * b;
            if (e.token == "/") return a / b;
            if (e.token == "**") return pow(a, b);
            if (e.token == "mod") return static_cast<int>(a) % static_cast<int>(b);
            throw "Unknown binary operator";
        }

        case 1: { // Один аргумент.
            auto a = eval(e.args[0]);
            if (e.token == "+") return +a;
            if (e.token == "-") return -a;
            if (e.token == "abs") return abs(a);
            if (e.token == "sin") return sin(a);
            if (e.token == "cos") return cos(a);
            throw "Unknown unary operator";
        }

        case 0: { // Числа (ноль аргументов).
            return strtod(e.token.c_str(), nullptr);
        }
    }

    throw "Unknown expression type";
}