/**
 * @brief Componente Javascript profile.h
 * @file profile.js.h
 */

/** Componente Javascript profile.h */
const std::string _src_components_navbar_profile_profile_js = R"(
const ProfileNavLink = function(){

    const dropdownRef = "profile-dropdown-helper";
    const dropdownNameRef = "profile-dropdown-text";
    const navbarRef = "navbar";
    const logoutRef = "nav-user-logout";

    var node = document.createElement("div");
        node.innerHTML = 
            '<div class="w3-dropdown-hover">' +
                '<button class="w3-button" id="profile-dropdown-text">Profilo</button>' +
                '<div class="w3-dropdown-content w3-bar-block w3-card-4" id="' + dropdownRef + '">' +
                    '<a href="javascript:void(0) " class="w3-bar-item w3-button" id="nav-user-logout">Disconnetti</a>' +
                '</div>' +
            '</div>';
    
    var eventLogout = function() {
        window.external.invoke(JSON.stringify(
            {
                fn: 'Navbar::Profile::Disconnect', 
                params: { }
            }
        ));
    }
            
    this.setText = function(username){
        window.getFirst(node, "#"+dropdownNameRef).innerText = username
    }

    this.create = function() {
        // if dom not exist
        window.getFirst(document, navbarRef).appendChild(node);
        window.subscribeTo(window.getFirst(node, "#"+logoutRef), "click", eventLogout);
    }(); // calling itself

    this.destroy = function() {
        // remove dom?
        window.unsubscribeTo(window.getFirst(node, "#"+logoutRef), "click", eventLogout);
    }
    
    window.navbar["ProfileLink"] = this;
    
}(); // calling itself
)";