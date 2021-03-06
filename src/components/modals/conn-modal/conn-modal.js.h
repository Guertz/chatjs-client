/**
 * @brief Componente Javascript conn-modal.h
 * @file conn-modal.js.h
 */

/** Componente Javascript conn-modal.h */
const std::string _src_components_modal_conn_modal_conn_modal_js = R"(
const ConnectivityModalFactory = function() {
    const domRef = "conn-modal";

    // z-index
    // error format (color red)
    var node = document.createElement("div");
        node.innerHTML = 
            '<div id="'+ domRef + '" class="w3-modal">' +
                    '<div class="w3-modal-content">' +
                        '<div class="w3-container">' +
                            '<h2>Problemi di connessione</h2>' +
                        '</div>' +
                    '</div>' +
                '</div>';

    
    

    this.destroy = function () {
        // remove dom reference
    }

    this.create = function() {
        // if dom not exist
        document.body.appendChild(node);
    }();
 
    window.modals['ConnModal'] = this;
    
}();
)";