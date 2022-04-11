#include "file_parser.h"

bool is_identifier_valid(char *identifier) {
  int length = strlen(identifier);
  for (int i = 0; i < length; i++) {
    if (!isalnum(identifier[i]) && identifier[i] != '-') {
      return false;
    }
  }
  return true;
}

void free_mem(struct Section *first_section) {
  // traverse all sections
  while (first_section != NULL) {
    free(first_section->name);
    // traverse all keys in section
    while (first_section->keys != NULL) {
      free(first_section->keys->key);
      free(first_section->keys->value);
      struct Key *key_to_free = first_section->keys;
      first_section->keys     = first_section->keys->nextkey;
      free(key_to_free);
    }
    struct Section *section_to_free = first_section;
    first_section                   = first_section->nextsection;
    free(section_to_free);
  }
  free(first_section);
}

// define parse function returning pointer to first struct section
struct Section *parse_file(FILE *file) {
  struct Section *first_section = NULL;
  char *buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE);
  while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
    int current_buffer_size = BUFFER_SIZE;
    // handle comments
    if (buffer[0] == ';') {
      continue;
    }
    // handle lines exceeding buffer size (resize buffer)
    while (buffer[strlen(buffer) - 1] != '\n') {
      buffer = (char *)realloc(buffer, sizeof(char) * (current_buffer_size*2));
      char *tmp = (char *)malloc(sizeof(char) * (current_buffer_size));
      fgets(tmp, current_buffer_size, file);
      strcat(buffer, tmp);
      current_buffer_size *= 2;
      free(tmp);
    }     
    if (buffer[0] == '[') {
      // create a new section
      char *section_name = strtok(buffer, "]") + 1;
      if (!is_identifier_valid(section_name)) {
        printf("Invalid section identifier \"%s\" in INI file\n", section_name);
      }
      struct Section *new_section = malloc(sizeof(struct Section));
      new_section->name           = malloc(sizeof(char) * strlen(section_name) + 1);
      strcpy(new_section->name, section_name);
      new_section->keys        = NULL;
      new_section->nextsection = NULL;
      if (first_section == NULL) {
        first_section = new_section;
      } else {
        // traverse sections to return pointer to last section
        struct Section *i_section = first_section;
        while (i_section->nextsection != NULL) {
          i_section = i_section->nextsection;
        }
        i_section->nextsection = new_section;
      }
    } else if (buffer[0] == '\n') {
      continue;
    } else {

      // create a new key
      char *key = strtok(buffer, " ");
      strtok(NULL, " ");
      char *value = strtok(NULL, "\n");
      if (!is_identifier_valid(key)) {
        printf("Invalid key identifier \"%s\" in INI file\n", key);
      }
      struct Key *new_key = malloc(sizeof(struct Key));
      new_key->key        = malloc(sizeof(char) * strlen(key) + 1);
      strcpy(new_key->key, key);
      new_key->value = malloc(sizeof(char) * strlen(value) + 1);
      strcpy(new_key->value, value);
      new_key->nextkey = NULL;

      // traverse sections to return pointer to last section
      struct Section *i_section = first_section;
      while (i_section->nextsection != NULL) {
        i_section = i_section->nextsection;
      }
      // if section doesnt have keys yet, add key to section
      if (i_section->keys == NULL) {
        i_section->keys = new_key;
      }
      // traverse keys to return pointer to last key
      else {
        struct Key *i_key = i_section->keys;
        while (i_key->nextkey != NULL) {
          i_key = i_key->nextkey;
        }
        i_key->nextkey = new_key;
      }
    }
  }
  free(buffer);
  return first_section;
}

char *read_value_from_section(struct Section *first_section, char *section, char *key) {

  // traverse sections
  struct Section *i_section = first_section;
  while (strcmp(i_section->name, section) != 0) {
    if (i_section->nextsection == NULL)
      return "Error:section-not-found";
    i_section = i_section->nextsection;
  }

  // traverse keys
  struct Key *i_key = i_section->keys;
  while (strcmp(i_key->key, key) != 0) {
    if (i_key->nextkey == NULL)
      return "Error:key-not-found";
    i_key = i_key->nextkey;
  }

  return i_key->value;
}