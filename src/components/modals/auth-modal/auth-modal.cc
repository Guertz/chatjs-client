#include <iostream>
#include <json.hpp>

#include "auth-modal.h"
#include "auth-modal.js.h"

#include "components/modals/modals.h"
#include "components/modals/sign-modal/sign-modal.h"

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

            inline void Submit(const std::string& args) {
                log_details(TAG::CMP, "Modals::AuthModal::Submit", args);

                json fn_params = json::parse(args);
                AuthState::Login(fn_params.at("_id").get<string>());
            }

            inline void SignIn(const std::string& args) {
                log_details(TAG::CMP, "Modals::AuthModal::SignIn", args);

                Modals::SignModal::Events::Show();
            }
            
            inline void Reset(){
                log_details(TAG::CMP, "Modals::AuthModal::Reset", "");

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
            log_base(TAG::CMP, "Modals::AuthModal::RegisterModal", "");

            WebUI::Execute(_src_components_modal_auth_modal_auth_modal_js);
            
            WebUI::Register("Modals::AuthModal::Submit", Events::Submit);
            WebUI::Register("Modals::AuthModal::SignIn", Events::SignIn);
            AuthState::Register("Modals::AuthModal", State::Auth);

            Events::Show();
        }

        void EraseModal () {
            log_base(TAG::CMP, "Modals::AuthModal::EraseModal", "");

            WebUI::Execute(AUTH_DESTROY);
        }

        namespace State {
                
            inline void Auth(){
                log_details(TAG::CMP, "Modals::AuthModal::State::Auth", "!! Detect changes ");
                
                Events::Reset();

                const AuthSocket::SIGNAL 
                                auth_action = AuthState::getAuthAction();
                const User      auth_user   = AuthState::getAuthUser();

                switch(auth_action) {
                    case AuthSocket::SIGNAL::LOGIN:
                        if(auth_user.is_valid())
                            AuthMethods::OnLoginSuccess();
                        else
                            AuthMethods::OnLoginErrors();
                        
                        break;

                    default:
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
                const string errors = AuthState::getAuthError();

                if(errors.size() > 0)
                    WebUI::Execute("modals.AuthModal.showErrors('" + errors + "')");
            }

            inline void OnLogout () {
                Events::Show();
            }
        }

    }
}