#include <iostream>
#include <json.hpp>

#include "chat-details.h"
#include "chat-details.hjs"

#include "common/web-ui/web-ui.h"
#include "common/logger/logger.h"

#include "states/chat-state/chat-state.h"

using json = nlohmann::json;
using namespace std;
using namespace States;

/**
 * @brief Definizione pagina ChatDetails in cui viene visualizzata la chat attiva
 * @file chat-details.cc
 */

namespace ChatDetails {

    const string CHAT_INACTIVE = "alert('Deve prima essere selezionata una chat')";

    const string ENABLE_FORM  = "components.ChatDetails.enable()";
    const string DISABLE_FORM = "components.ChatDetails.disable()";

    namespace Events {

        inline void Submit(const std::string& args){
            log_pedantic("ChatDetails::Submit", args);

            json form_args = json::parse(args);
            ChatState::ChatMethods::SendAMessage(form_args.at("text").get<string>());

        }
    }

    void Bootstrap() {
        log_details("ChatDetails", "Bootstrap");

        WebUI::Execute(_src_pages_chat_details_chat_details_js);

        WebUI::Register("ChatDetails::Submit", Events::Submit);

        ChatState::ChatMethods::Register("ChatDetails", State::Chat);

    }

    void Destroy() {
        log_details("ChatDetails", "Destroy");
    }

    namespace State {
        inline void Chat(){
            if(ChatState::ChatsMethods::isCurrentChat()){
                const string js_chat = "components.ChatDetails.populateChatDetails('" +
                                            ChatState::ChatsMethods::getCurrentChat() +
                                        "')";

                WebUI::Execute(js_chat);
                WebUI::Execute(ENABLE_FORM);
            }
        }
    }
}