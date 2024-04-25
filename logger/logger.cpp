/* Diagnostic Logger library
 * Copyright (C) 2023  Avijit Dey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "logger.h"

namespace common {
namespace logger {

Logger::Logger(std::string context_id) : contxt_{}, app_id_{}, context_id_{context_id} {
#ifdef ENABLE_DLT_LOGGER
  DLT_REGISTER_CONTEXT(contxt_, context_id_.c_str(), "Application Context");
#else 
  Initialize(context_id);
#endif
}

Logger::Logger(std::string app_id, std::string context_id)
    : contxt_{},
      app_id_{app_id},
      context_id_{context_id} {
#ifdef ENABLE_DLT_LOGGER
  DLT_REGISTER_APP(app_id_.c_str(), "Application Id");
  DLT_REGISTER_CONTEXT(contxt_, context_id_.c_str(), "Application Context");
  registration_with_app_id_ = true;
#else 
  Initialize(context_id);
#endif
}

Logger::~Logger() {
#ifdef ENABLE_DLT_LOGGER
  DLT_UNREGISTER_CONTEXT(contxt_);
  if (registration_with_app_id_) { DLT_UNREGISTER_APP(); }
#endif
}

void Logger::Initialize(const std::string &filename) {
  boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");
  
  std::string log_filename = std::string("logs/") + std::string(filename) + std::string("__%Y_%m_%d_%H_%M_%S.log");
// #ifdef Debug
//     logging::core::get()->set_filter(
//         trivial::severity >= trivial::debug
//     );
// #else
    // logging::core::get()->set_filter(
    //     trivial::severity >= trivial::info
    // );
// #endif

  boost::log::add_file_log(
      boost::log::keywords::file_name = log_filename, // 日志名为sample_0.log,sample_1.log
      boost::log::keywords::open_mode = std::ios_base::app, // 日志使用追加方式
      boost::log::keywords::rotation_size = 100 * 1024 * 1024, // 当日志大小到1M的时候，使用新的日志文件存储
      boost::log::keywords::format = "[%TimeStamp%]: <%Severity%> %Message%"); // 每条日志的输出格式：时间，日志等级，日志信息

  // helpers function adds attributes such as "Timestamp" and "ThreadID"
  boost::log::add_common_attributes();  
}

Logger DiagClientLogger::logger_("DiagClient");

}  // namespace logger
}  // namespace common
