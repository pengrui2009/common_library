/* Diagnostic Logger library
 * Copyright (C) 2023  Avijit Dey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef DIAGNOSTIC_CLIENT_LIB_COMMON_LOGGER_H
#define DIAGNOSTIC_CLIENT_LIB_COMMON_LOGGER_H

#ifdef ENABLE_DLT_LOGGER
#include <dlt/dlt.h>
#endif

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

// #define SENSORNAME  "sensor_flash"

namespace common {
namespace logger {

class Logger {
 public:
  template <typename Func>
  auto LogFatal(const std::string file_name, int line_no, const std::string func_name, Func &&func) noexcept -> void {
#ifdef ENABLE_DLT_LOGGER
    LogDltMessage(DLT_LOG_FATAL, file_name, func_name, line_no, std::forward<Func>(func));
#else
    BOOST_LOG_TRIVIAL(fatal) << CreateLoggingMessage(file_name, func_name, line_no, func).str();
#endif
  }

  template <typename Func>
  auto LogError(const std::string file_name, int line_no, const std::string func_name, Func &&func) noexcept -> void {
#ifdef ENABLE_DLT_LOGGER
    LogDltMessage(DLT_LOG_ERROR, file_name, func_name, line_no, std::forward<Func>(func));
#else
    BOOST_LOG_TRIVIAL(error) << CreateLoggingMessage(file_name, func_name, line_no, func).str();
#endif
  }

  template <typename Func>
  auto LogWarn(const std::string file_name, int line_no, const std::string func_name, Func &&func) noexcept -> void {
#ifdef ENABLE_DLT_LOGGER
    LogDltMessage(DLT_LOG_WARN, file_name, func_name, line_no, std::forward<Func>(func));
#else
    BOOST_LOG_TRIVIAL(warning) << CreateLoggingMessage(file_name, func_name, line_no, func).str();
#endif
  }

  template <typename Func>
  auto LogInfo(const std::string file_name, int line_no, const std::string func_name, Func &&func) noexcept -> void {
#ifdef ENABLE_DLT_LOGGER
    LogDltMessage(DLT_LOG_INFO, file_name, func_name, line_no, std::forward<Func>(func));
#else
    BOOST_LOG_TRIVIAL(info) << CreateLoggingMessage(file_name, func_name, line_no, func).str();
#endif
  }

  template <typename Func>
  auto LogDebug(const std::string file_name, int line_no, const std::string func_name, Func &&func) noexcept -> void {
#ifdef ENABLE_DLT_LOGGER
    LogDltMessage(DLT_LOG_DEBUG, file_name, func_name, line_no, std::forward<Func>(func));
#else
    BOOST_LOG_TRIVIAL(debug) << CreateLoggingMessage(file_name, func_name, line_no, func).str();
#endif
  }

  template <typename Func>
  auto LogVerbose(const std::string file_name, int line_no, const std::string func_name, Func &&func) noexcept -> void {
#ifdef ENABLE_DLT_LOGGER
    LogDltMessage(DLT_LOG_VERBOSE, file_name, func_name, line_no, std::forward<Func>(func));
#else
    BOOST_LOG_TRIVIAL(trace) << CreateLoggingMessage(file_name, func_name, line_no, func).str();
#endif
  }

 public:
  // ctor
  explicit Logger(std::string context_id);

  // ctor
  Logger(std::string app_id, std::string context_id);

  // dtor
  ~Logger();

 private:
  void Initialize(const std::string &filename);

  template <typename Func>
  auto CreateLoggingMessage(
      const std::string file_name, const std::string /* func_name */, int line_no, Func &&func) noexcept
      -> std::stringstream {
    std::stringstream msg;
    func(msg);
    msg << " [" << file_name << ":" << line_no << "]";
    return msg;
  }

#ifdef ENABLE_DLT_LOGGER
  template <typename Func>
  void LogDltMessage(
      DltLogLevelType log_level, const std::string file_name, const std::string func_name, int line_no, Func &&func) {
    DLT_LOG(
        contxt_, log_level,
        DLT_CSTRING(CreateLoggingMessage(file_name, func_name, line_no, std::forward<Func>(func)).str().c_str()));
  }
#endif

#ifdef ENABLE_DLT_LOGGER
  // Declare the context
  DLT_DECLARE_CONTEXT(contxt_);
#else
  std::string contxt_;
#endif
  // Stores application id
  std::string app_id_;

  // Stores context id
  std::string context_id_;

  // store the information about registration with app id
  bool registration_with_app_id_{false};
};

class DiagClientLogger {
 public:
  auto static GetDiagClientLogger() noexcept -> DiagClientLogger & {
    static DiagClientLogger diag_logger;
    return diag_logger;
  }

  auto GetLogger() noexcept -> Logger * { return &logger_; }

 private:
  DiagClientLogger() {}

  // actual logger context
  static Logger logger_;
};

}  // namespace logger
}  // namespace common

#define LOGFATAL(str)                                                            \
  common::logger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogFatal( \
      __FILE__, __LINE__, __func__, [str](std::stringstream &msg) { msg << str; })
#define LOGERROR(str)                                                            \
  common::logger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogError( \
      __FILE__, __LINE__, __func__, [str](std::stringstream &msg) { msg << str; })
#define LOGWARN(str)                                                            \
  common::logger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogWarn( \
      __FILE__, __LINE__, __func__, [str](std::stringstream &msg) { msg << str; })
#define LOGINFO(str)                                                            \
  common::logger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogInfo( \
      __FILE__, __LINE__, __func__, [str](std::stringstream &msg) { msg << str; })
#define LOGDEBUG(str)                                                            \
  common::logger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogDebug( \
      __FILE__, __LINE__, __func__, [str](std::stringstream &msg) { msg << str; })
#define LOGVERBOSE(str)                                                            \
  common::logger::DiagClientLogger::GetDiagClientLogger().GetLogger()->LogVerbose( \
      __FILE__, __LINE__, __func__, [str](std::stringstream &msg) { msg << str; })

#endif  // DIAGNOSTIC_CLIENT_LIB_COMMON_LOGGER_H
