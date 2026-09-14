#include <csignal>
#include <signal.h>
#include <string.h>
volatile sig_atomic_t	g_signal;

static void	ms_sig_handler(int sig)
{
	g_signal = sig;
}

/*
Wenn rl bei ctrl-c nicht selbst \n macht können wir 'write(1, "\n", 1);' hinzufügen. Ist async-signal-safe!
*/

void	ms_sig_init(void)
{
	struct sigaction	s_sig;

	s_sig.sa_handler = ms_sig_handler;
	sigemptyset(&s_sig.sa_mask);
	s_sig.sa_flags = 0;
	sigaction(SIGINT, &s_sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}



void	ms_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
/*
Du musst sagen ob wir das^ wollen od ned
man:
When a process which has installed signal handlers forks, the child process inherits the signals.  All caught signals may be reset to their default action by a call to
     the execve(2) function; ignored signals remain ignored.


in ms_repl():

g_signal = 0;
line = ms_gnl();
if (line == NULL)
{
	if (g_signal == SIGINT)
			continue;
	break;
}
*/
