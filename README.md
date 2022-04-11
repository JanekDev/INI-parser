# INI Parser

Complete program that parses configuration files in INI format.
Written entirely in C language.

Created by Łukasz Sztukiewicz & Michał Wiliński.

- Formatter: [Clang 15.0.0](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- Compiled with: gcc -Wall -Wextra *.c -o main
- Tested against Valgrind

## Usage

### Input formats:

    ./program PATH_TO_INI expression "section.key+section.key"
    ./program PATH_TO_INI section.key

### Examples

1. Reading username stored in my_config.ini file

> [user]
> name = john

     ./my-program my_config.ini user.name

> john

2. Reading database port stored in database.ini file

> [server]
> port = 143

     ./my-program database.ini server.port

> 143

3. Displaying the total of bytes used by logs files

> [log]
> files = 10
> size = 256

     ./my-program my_config.ini expression "log.files * log.size"

> 2560

4. Displaying username with organization postfix

> [user]
> name = John
> [organization]
> suffix = -Google-Inc

     ./my-program my_config.ini expression "user.name + organization.suffix"

> John-Google-Inc
