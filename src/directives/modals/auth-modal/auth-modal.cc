#include <iostream>
#include <json.hpp>

#include "auth-modal.h"
#include "directives/modals/modals.h"

#include "common/web-ui/web-ui.h"
#include "common/helpers/helpers.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace Helpers;
using namespace States;

extern char _binary_src_directives_modals_auth_modal_auth_modal_js_start[];

namespace Modal {

    namespace AuthModal {

        // Deve essere lo stesso valore presente nel file JS
        static const string modalRef = "auth-modal"; /** Nome identificativo del modale di autenticazione */
        
        namespace Events {

            void Submit(const string& args){

                log_base("Modal::AuthModal::Events", args);

                AuthState::AuthActionDefinition::AuthAction data = json::parse(args);

                AuthState::Login(data);
            }

            void Reset(){
                
                const string AUTH_RESET = "modals.AuthModal.reset()";

                WebUI::Execute(AUTH_RESET);
            }

            void Show() {
                Modal::Events::ShowModalByRef(modalRef);
            }

            void Hide() {
                Modal::Events::HideModalByRef(modalRef);
            }

        }

        void RegisterModal(){

            WebUI::Execute(
                    safeptr::parse_asset(
                        _binary_src_directives_modals_auth_modal_auth_modal_js_start)
                );
            
            WebUI::Register("Modal::AuthModal::Submit", Events::Submit);
            AuthState::Register("Modal::AuthModal", State::Auth);

           Events::Show();
            
        }

        void EraseModal () {
            
        }

        namespace State {
                
            void Auth(const AuthState::AuthBaseDefinition::AuthBase& auth_data){

                Events::Reset();


                switch(auth_data.action){
                    case AuthState::AUTHSIGNAL::LOGIN:
                        if(auth_data.online){
                            AuthMethods::OnLoginSuccess();
                        } else {
                            AuthMethods::OnLoginErrors();
                        }
                            
                        break;

                    case AuthState::AUTHSIGNAL::LOGOUT:

                        AuthMethods::OnLogout();

                        break;
                }
                
            }
        }

        namespace AuthMethods {

            void OnLoginSuccess() {
                Events::Hide();
            }

            void OnLoginErrors() {

                const string AUTH_ERRORS = "modals.AuthModal.showErrors()";

                WebUI::Execute(AUTH_ERRORS);
                // Events::Reset

            }

            void OnLogout () {
                Events::Show();
            }
        }

    }
}