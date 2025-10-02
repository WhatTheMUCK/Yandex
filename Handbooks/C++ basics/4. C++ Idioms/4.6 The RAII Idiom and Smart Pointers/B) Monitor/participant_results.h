#include <map>
#include <string>

struct ParticipantResults {
    std::string login;
    std::string team;
    std::map<std::string, int> scores;  // номер задачи -> баллы

    // ...

    ParticipantResults(const std::string& l, const std::string& te): login(l), team(te) {
    }

    ParticipantResults(const ParticipantResults&) = delete;
    ParticipantResults& operator = (const ParticipantResults&) = delete;
};
