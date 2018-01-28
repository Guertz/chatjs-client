#ifndef STATES_USERS_STATE_DEFINITIONS_RESPONSE_H
#define STATES_USERS_STATE_DEFINITIONS_RESPONSE_H

#include <iostream>
#include <json.hpp>
#include "types.h"

namespace States {
    namespace UsersState {
        namespace Response {

            class Stream {
                private:
                    void from_json(const nlohmann::json& j);

                public:
                    STREAMSIGNAL type;
                    std::string  usersList;

                    Stream();
                    Stream(const nlohmann::json& j);
                    Stream(const std::string& serialized);

                    nlohmann::json to_json();
                    std::string serialize();
                    
            };

        }
    }
}

#endif