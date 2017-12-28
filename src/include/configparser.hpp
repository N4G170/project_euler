#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <map>
#include <string>

#include "json.h"

/**
 * \brief Tries to load(from file) application configuration into config_json var
 */
int ProgramConfigReader(int argc, char *argv[], Json::Value& config_json);
int ResourcesJsonReader(Json::Value& resources_json);

#endif // CONFIGPARSER_HPP
