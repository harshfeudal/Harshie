#pragma once

#include <dpp/dpp.h>
#include <spdlog/spdlog.h>

#include "database.h"

class HarshieCreateDatabase
{
public:
    void languageData();

private:
    HarshieDatabase& database = HarshieDatabase::getInstance();
};
