#include "pch.h"
#include <string>
#include <ctime>
#include <stdlib.h>

#include "launch/run.h"

#include "line_util.h"
#ifdef READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

std::string psfilename = "<stdin>";
bool REPLMode = true;

int main(int argc, char **argv) {
    auto fn = startREPL;

    if (argc == 2) {
        psfilename = argv[1];
        REPLMode = false;
        fn = runFile;
    } else if (argc > 2) {
        std::cerr << "Too many arguements!\nUsage:\n" << argv[0] << " <filename>" << std::endl;
        return EXIT_FAILURE;
    }

#ifdef READLINE
    rl_bind_key('\t', rl_tab_insert);
#endif

    srand((unsigned int) time(NULL));

    return fn() ? EXIT_SUCCESS : EXIT_FAILURE;
}

bool getLine(std::string &line, const char *prompt) {
#ifdef READLINE
    char *buf = readline(prompt);
    if (buf != NULL) {
        line = buf;
        if (buf[0] != '\0') add_history(buf);
        free(buf);
    } else {
        line.clear();
        return false;
    }
#else
    std::cout << prompt << std::flush;
    std::getline(std::cin, line);
    if (std::cin.eof()) return false;
#endif

    return true;
}
