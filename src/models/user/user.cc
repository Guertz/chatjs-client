#include "user.h"
#include "common/logger/logger.h"

/**
 * @brief Definizione classe User (Json) 
 * @file user.cc
 */

using json = nlohmann::json;
using namespace std;

User::User(){
    log_pedantic("User@JsonItem", "Created");

    this->name  = "";
    this->_id   = "";
    this->image = "";
}

User::User(const json& j) : User() {
    log_pedantic("User@JsonItem", "Created from json");

    if(j.is_object()) {
        this->name = j.at("name").get<string>();
        this->image = j.at("image").get<string>();
        this->_id = j.at("_id").get<string>();
    }
}

User::User(const std::string& serialized) 
    : User(json::parse(serialized)) { }

User::~User() {
    log_pedantic("User@JsonItem", "Destroying");
}

json User::to_json() const {
    return json{
        { "name", this->name}, 
        { "image", this->image}, 
        { "_id", this->_id}
    };
}

bool User::is_valid() const {
    return this->_id.size() > 0;
}
     