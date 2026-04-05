#ifndef DEBUGGER_DRIVER_H_
#define DEBUGGER_DRIVER_H_

typedef enum
{
    DEBUG_STATE_RUNNING,
    DEBUG_STATE_HALTED,
    DEBUG_STATE_WAIT_RESUME
} DebugState_t;

extern volatile DebugState_t g_debugState;

void debug_process(void);

#endif /* DEBUGGER_DRIVER_H_ */
