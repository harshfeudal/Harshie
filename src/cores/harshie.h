#include <dpp/dpp.h>
#include <spdlog/spdlog.h>

#include "dotenv.h"
#include "decoder.h"

class Harshie {
public:
    Harshie();

    void HarshieStart();

private:
    std::unique_ptr<dpp::cluster> client;

    void HarshieOnReady();
    void HarshieOnSlashCmnd();

    void HarshieActivites(const dpp::ready_t& event);
    void HarshieRegisterSlashCmnd();
};
