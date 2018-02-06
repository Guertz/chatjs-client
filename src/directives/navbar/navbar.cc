#include <iostream>
#include <json.hpp>

#include "navbar.h"
#include "navbar.hjs"
#include "profile/profile.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

/**
 * @brief Definizione Navbar, menù di navigazione superiore 
 * @file navbar.cc
 */

namespace Navbar {

    void Bootstrap() {
        log_details("Navbar", "Bootstrap");

        WebUI::Execute(_src_directives_navbar_navbar_js);

        AuthState::Register("Navbar", State::Auth);

        Profile::RegisterLink();
    }

    void Destroy() {
        log_details("Navbar", "Destroy");

        Profile::EraseLink();
    }

    namespace State {

        inline void Auth(){
                
            const AuthState::AUTHSIGNAL 
                        auth_action = AuthState::getAuthAction();
            const User  auth_user   = AuthState::getAuthUser();

            switch(auth_action){
                case AuthState::AUTHSIGNAL::LOGIN:

                    if(auth_user.is_valid())
                        Profile::Events::SetText(auth_user.name);

                    break;

                case AuthState::AUTHSIGNAL::LOGOUT:
                    Profile::Events::SetText("Profilo");

                    break;

            }

        }
    }

}