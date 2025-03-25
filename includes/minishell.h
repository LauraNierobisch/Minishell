#ifndef MINISHELL_H
# define MINISHELL_H

/* EXTERNAL INCLUDES */
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>

extern volatile sig_atomic_t	g_sig;

# define TEST printf

# define PROMPT "\033[38;5;168m\033[1m🧚>$ \033[0m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define HEREDOC_FILE "/tmp/.minishell_heredoc_"

# define success true
# define fail false

/* INCLUDES */
# include "libft/libft.h"
# include "shell.h"
# include "token.h"
# include "error.h"
# include "debug.h"
# include "expander.h"
# include "format.h"
# include "builtin.h"
# include "signals.h"
# include "env.h"
# include "exec.h"
# include "utils.h"
// # include "history.h"
// # include "gcollector.h"

/* READLINE INCLUDES */
# include <readline/history.h>
# include <readline/readline.h>

# ifndef DEBUG
#  define DEBUG 0
# endif


#endif /* MINISHELL_H */