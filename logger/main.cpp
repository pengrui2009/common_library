
#include <bits/stdc++.h>

#include "logger.h"

namespace DiagLogger = common::logger;
int main()
{
    // DiagLogger::Logger logger = 
    // DiagLogger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogInfo(__FILE__, __LINE__, __func__, "DiagIpClient instance creation started");
    // DiagLogger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogDebug(__FILE__, __LINE__, __func__, [](std::stringstream &msg) { msg << "DiagIpClient instance creation started"; });
    // DiagLogger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogError(__FILE__, __LINE__, __func__, [](std::stringstream &msg) { msg << "DiagIpClient instance creation started"; });
    std::string str = "Hello World!";
    LOGINFO(str);

    return 0;
}