#include "input_parser.h"

// utility functions
bool is_integer_value(char *value) {
  int length = strlen(value);
  for (int i = 0; i < length; i++) {
    if (!isdigit(value[i])) {
      return false;
    }
  }
  return true;
}

char *parse_expression(struct Section *parsed_sections, char *expression) {
  // parse expression in quotes to variables
  char *first_argument_section  = strtok(expression, " .");
  char *first_argument_key      = strtok(NULL, " .");
  char *first_value             = read_value_from_section(parsed_sections, first_argument_section, first_argument_key);
  char *operand                 = strtok(NULL, " .");
  char *second_argument_section = strtok(NULL, " .");
  char *second_argument_key     = strtok(NULL, " .");
  char *second_value            = read_value_from_section(parsed_sections, second_argument_section, second_argument_key);
  bool is_int_first_value       = is_integer_value(first_value);
  bool is_int_second_value      = is_integer_value(second_value);
  char *message                 = malloc(sizeof(char) * (strlen(first_value) + strlen(second_value)) + 1);

  if (is_int_first_value && is_int_second_value) {

    // perform operations on integer values
    // long type is required since multiplication operation can be also performed
    long first_int_value  = atol(first_value);
    long second_int_value = atol(second_value);
    switch (*operand) {
    case '+':
      printf("%ld", first_int_value + second_int_value);
      break;
    case '-':
      printf("%ld", first_int_value - second_int_value);
      break;
    case '*':
      printf("%ld", first_int_value * second_int_value);
      break;
    case '/':
      printf("%ld", first_int_value / second_int_value);
      break;
    }
    strcpy(message, "");
  }

  // check if the values have same type
  else if ((is_int_first_value && !is_int_second_value) || (!is_int_first_value && is_int_second_value)) {
    strcpy(message, "Error:invalid-operation type mismatch");
  }

  // both values must be strings, so perform operation on strings
  else {
    // only concatenation is allowed
    if (*operand != '+') {
      strcpy(message, "Error:invalid-operation on string");
    } else {
      strcpy(message, first_value);
      strcat(message, second_value);
    }
  }
  return message;
}