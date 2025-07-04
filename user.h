#ifndef USER_H
#define USER_H

class User {
private:
    float budget;

public:
    User() : budget(0.0f) {}
    float getBudget() const { return budget; }
    void setBudget(float b) { budget = b; }
};

#endif // USER_H