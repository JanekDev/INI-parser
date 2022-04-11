/*******************************************************************************
*                               INI PARSER
*
* by Łukasz Sztukiewicz & Michał Wiliński
*
* Input formats:
* 1. ./program PATH_TO_INI expression "section.key+section2.key2"
* 2. ./program PATH_TO_INI section.key
*
*  Structure of ini save:
*  [section] -> [key]
*
* Mode 1 - expression evaluation
* Mode 2 - displaying value of section.key
******************************************************************************/

#include "input_parser.h"

int main(int argc, char *argv[]) {
  char *path = argv[1];

  // read file
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("File not found\n");
    return 1;
  }
  struct Section *first_section = parse_file(file);
  fclose(file);

  // Mode 1
  if ((strcmp(argv[2], "expression") == 0)) {

    // in this mode there must be exactly 3 arguments
    if (argc != 4) {
      printf("Bad number of arguments\n");
      free_mem(first_section);
      return 1;
    }
    char *result = parse_expression(first_section, argv[3]);
    printf("%s", result);
    free(result);
  }

  // Mode2
  else {

    // parse section and key identifiers
    char *desired_section = strtok(argv[2], ".");
    char *desired_key     = strtok(NULL, ".");

    // perform read operation
    char *result = read_value_from_section(first_section, desired_section, desired_key);

    // process the result
    if (strcmp("Error:section-not-found", result) == 0) {
      printf("Failed to find section [%s]", desired_section);
      free_mem(first_section);
      return 1;
    } else if (strcmp("Error:key-not-found", result) == 0) {
      printf("Failed to find key \"%s\" in section [%s]", desired_key, desired_section);
      free_mem(first_section);
      return 1;
    } else {
      printf("%s", result);
    }
  }
  free_mem(first_section);
  return 0;
}