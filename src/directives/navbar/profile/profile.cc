#include <iostream>
#include <json.hpp>

#include "profile.h"
#include "profile.hjs"

#include "common/web-ui/web-ui.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

namespace Navbar {
    namespace Profile {

        void RegisterLink(){

            WebUI::Execute(_src_directives_navbar_profile_profile_js);

            WebUI::Register("Navbar::Profile::Disconnect", Events::Disconnect);
        }

        void EraseLink() {

        }

        namespace Events {
            void Disconnect(const string& arg){

                AuthState::Logout();
            }

            void SetText(const string text) {
                const string js_nav_link = "window.navbar.ProfileLink.setText('" + 
                                                text +
                                            "')";

                WebUI::Execute(js_nav_link);
            }
        }
    }

}