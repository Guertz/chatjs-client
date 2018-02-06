#include <iostream>
#include <json.hpp>

#include "auth-modal.h"
#include "auth-modal.hjs"

#include "directives/modals/modals.h"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/auth-state/auth-state.h"

using json = nlohmann::json;
using namespace std;
using namespace WebUI;
using namespace States;

/**
 * @brief Definizione AuthModal, form autenticazione utente.
 * @file auth-modal.cc
 */

namespace Modals {

    namespace AuthModal {

        /** Nome identificativo del modale di autenticazione */
        static const string modalRef = "auth-modal";  // Deve essere lo stesso valore presente nel file JS

        static const string AUTH_RESET = "modals.AuthModal.reset()";
        static const string AUTH_DESTROY = "modals.AuthModal.destroy()";

        namespace Events {

            inline void Submit(const std::string& args){
                log_pedantic("Modals::AuthModal::Submit", args);

                json fn_params = json::parse(args);
                AuthState::Login(fn_params.at("_id").get<string>());
            }

            inline void Reset(){
                log_pedantic("Modals::AuthModal::Reset", "");

                WebUI::Execute(AUTH_RESET);
            }

            void Show() {
                Modals::Events::ShowModalByRef(modalRef);
            }

            void Hide() {
                Modals::Events::HideModalByRef(modalRef);
            }

        }

        void RegisterModal(){
            log_details("Modals::AuthModal", "Create");

            WebUI::Execute(_src_directives_modal_auth_modal_auth_modal_js);
            
            WebUI::Register("Modals::AuthModal::Submit", Events::Submit);
            AuthState::Register("Modals::AuthModal", State::Auth);

            Events::Show();
        }

        void EraseModal () {
            log_details("Modals::AuthModal", "Erase");

            WebUI::Execute(AUTH_DESTROY);
        }

        namespace State {
                
            inline void Auth(){
                log_pedantic("Modals::AuthModal::State::Auth", "Refreshing...");
                
                Events::Reset();

                const AuthState::AUTHSIGNAL 
                            auth_action = AuthState::getAuthAction();
                const User  auth_user   = AuthState::getAuthUser();

                switch(auth_action) {
                    case AuthState::AUTHSIGNAL::LOGIN:
                        if(auth_user.is_valid())
                            AuthMethods::OnLoginSuccess();
                        else
                            AuthMethods::OnLoginErrors();
                        
                        break;

                    case AuthState::AUTHSIGNAL::LOGOUT:
                        AuthMethods::OnLogout();

                        break;
                }
            }
        }

        namespace AuthMethods {

            inline void OnLoginSuccess() {
                Events::Hide();
            }

            inline void OnLoginErrors() {
                WebUI::Execute("modals.AuthModal.showErrors('" + AuthState::getAuthError() + "')");
            }

            inline void OnLogout () {
                Events::Show();
            }
        }

    }
}