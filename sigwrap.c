#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

extern char **environ;
pid_t pid;

void
sigterm(int signum) {
  kill(pid, signum);
  signal(signum, SIG_DFL);
  kill(getpid(), signum);
}

int
main(int argc, char *argv[]) {
  if(argc == 1) {
    puts("Usage: sigwrap command [args]\n"
	 "\n"
	 "See https://github.com/jim-minter/sigwrap for more details.");
    return 0;
  }

  signal(SIGTERM, sigterm);

  if((pid = fork())) {
    int status;
    wait(&status);

    signal(SIGTERM, SIG_DFL);

    if(WIFEXITED(status))
      return WEXITSTATUS(status);
    else if(WIFSIGNALED(status))
      kill(getpid(), WTERMSIG(status));

  } else
    execve(argv[1], argv + 1, environ);

  return 0;
}
