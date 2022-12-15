
struct Green {
  int ON = 1;
  int OFF = 0;
};

struct Blue {
  int ON = 1;
  int OFF = 0;
};

struct Red {
  int ON = 1;
  int OFF = 0;
};

struct State {
  unsigned long State;
  unsigned long Time;
  unsigned long Color[3];
  unsigned long nextState;
};

typedef const struct State LedState;

struct SemaforState {
  unsigned long State;
  LedState* type;
  unsigned long nextState;
};

typedef const struct SemaforState Semafore;
