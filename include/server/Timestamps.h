#ifndef TIMESTAMPTS_H
#define TIMESTAMPTS_H

class Timestamps {
    time_t lastAccess;
    time_t lastModification;
    time_t lastChange;

  public:
    Timestamps(time_t lastAccess,
               time_t lastModification,
               time_t lastChange)
        : lastAccess(lastAccess),
          lastModification(lastModification),
          lastChange(lastChange) {
        // empty constructor
    }
};

#endif
