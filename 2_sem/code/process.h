#ifndef PROCESS_H
#define PROCESS_H

extern int process_is_exited;

int process_daemonize();
int process_setup_signals();

#endif
