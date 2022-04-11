#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include "file_parser.h"

bool is_integer_valid(char *value);

char *parse_expression(struct Section *parsed_sections, char *expression);

#endif