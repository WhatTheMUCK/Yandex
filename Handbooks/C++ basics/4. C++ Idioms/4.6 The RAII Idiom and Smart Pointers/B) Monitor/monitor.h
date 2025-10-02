#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Monitor {
private:
    // удобные псевдонимы типов для краткости:
    using Ptr = ParticipantResults*;
    using ConstPtr = const ParticipantResults*;

    std::map<std::string, Ptr> byParticipant;
    std::map<std::string, std::vector<ConstPtr>> byTeam;
    std::vector<ConstPtr> allResults;

public:
    Monitor() = default;
    Monitor(const Monitor&) = delete;
    Monitor& operator=(const Monitor&) = delete;

    Ptr RegisterParticipant(const std::string& login, const std::string& team) {
        if (byParticipant.contains(login)) {
            throw std::invalid_argument("Participant is already registered");
        }
        // Добавить новую запись об участнике и вернуть её
        byParticipant[login] = new ParticipantResults(login, team);
        byTeam[team].push_back(byParticipant[login]);
        allResults.push_back(byParticipant[login]);
        return byParticipant[login];
    }

    Ptr GetParticipantResults(const std::string& login) {
        return byParticipant.at(login);
    }

    ConstPtr GetParticipantResults(const std::string& login) const {
        return byParticipant.at(login);
    }

    std::vector<ConstPtr> GetTeamResults(const std::string& team) const {
        return byTeam.at(team);
    }

    std::vector<ConstPtr> GetAllResults() const {
        return allResults;
    }

    ~Monitor() {
        for (auto ptr : allResults) {
            delete ptr;
        }
    }
};