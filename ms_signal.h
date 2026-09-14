
#include <csignal>

extern volatile sig_atomic_t	g_signal;

void	ms_sig_init(void);
void	ms_signal_child(void);
