
#include <bits/stdc++.h>

#include "logger.h"

namespace DiagLogger = common::logger;

bool getBufferData(int *data_ptr, int size)
{
  data_ptr[size-1] = 20;
  
  return true;
}

int main() {
  // DiagLogger::Logger logger =
  // DiagLogger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogInfo(__FILE__, __LINE__, __func__,
  // "DiagIpClient instance creation started");
  // DiagLogger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogDebug(__FILE__, __LINE__, __func__,
  // [](std::stringstream &msg) { msg << "DiagIpClient instance creation started"; });
  // DiagLogger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogError(__FILE__, __LINE__, __func__,
  // [](std::stringstream &msg) { msg << "DiagIpClient instance creation started"; });
  std::string str = "Hello World!";
  LOGINFO(str);
  int data[10];

  data[20] = 0;
  
  if (getBufferData(data, 20) != 0)
  {

  }
  return 0;
}