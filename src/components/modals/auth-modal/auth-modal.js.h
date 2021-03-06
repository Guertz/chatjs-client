/**
 * @brief Componente Javascript auth-modal.h
 * @file auth-modal.js.h
 */

/** Componente Javascript auth-modal.h */
const std::string _src_components_modal_auth_modal_auth_modal_js = R"(
const AuthModalFactory = function(){

    const domRef = "auth-modal";

    var node = document.createElement("div");
      node.innerHTML = 
        '<div id="'+ domRef + '" class="w3-modal">' +
            '<div class="w3-modal-content">' +
                '<div class="w3-container">' +
                    '<br/>' +
                    '<form class="w3-container user-form">' +
                
                        '<label>Identificativo Utente</label>' +
                        '<input class="w3-input can-disable userid" type="text">' +

                        '<br/>' +
                        '<button type="submit" class="w3-button w3-teal can-disable">Entra</button>'+
                    '</form>'+
                    '<br/>' +
                    '<a href="javascript:void(0);" id="registrar">Oppure registrati</a>'
                '</div>' +
            '</div>' +
        '</div>';

    var setDisabled = function(state) {
        window.forAll(node, ".can-disable", function(node){
            node.disabled = !!state;
        })
    }

    var signEvent = function(event) {
        event.preventDefault();

        window.external.invoke(JSON.stringify(
            {
                fn: 'Modals::AuthModal::SignIn', 
                params: { }
            }
        ));
    }

    var submitEvent = function(event) {
        event.preventDefault();
        setDisabled(true);

        const val = window.getFirst(node, "input.userid").value;
        window.external.invoke(JSON.stringify(
            {
                fn: 'Modals::AuthModal::Submit', 
                params: {
                    '_id': val
                }
            }
        ));
    }

    this.reset = function(){
        setDisabled(false);
    }

    this.showErrors = function(err) {
        alert(err);
    }

    this.destroy = function() {
        window.unsubscribeTo(window.getFirst(node, "form"), "submit", submitEvent);  
        window.unsubscribeTo(window.getFirst(node, "a#registrar"), "click", signEvent);
        // window.getFirst(document, "#"+domRef).parent.innerHTML = "";
    }

    this.create = function() {
        // if dom not exist
        document.body.appendChild(node);
        window.subscribeTo(window.getFirst(node, "form"), "submit", submitEvent);
        window.subscribeTo(window.getFirst(node, "a#registrar"), "click", signEvent);
    }();
    

    window.modals["AuthModal"] = this;

}();
)";