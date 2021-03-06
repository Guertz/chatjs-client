/**
 * @brief Metodi Javascript elementari
 * @file appinit.js.h
 */

/** Metodi Javascript elementari */
const std::string _src_assets_appinit_js = R"(
window.stylify = function(multiline, css) {

    var style = document.createElement('style');
    var head = document.head || document.getElementsByTagName('head')[0];
    style.setAttribute('type', 'text/css');
    if (style.styleSheet) {
        style.styleSheet.cssText = multiline? atob(css) : css;
    } else {
        style.appendChild(document.createTextNode( multiline? atob(css) : css));
    }
    head.appendChild(style);
}

window.appready = function() {
    window.external.invoke(JSON.stringify(
        {
            fn: 'App::Ready', 
            params: { 
                framework: true
            }
        }
    ));
}

/* var WebUIEventResize = function(){
    window.external.invoke(JSON.stringify(
        {
            fn: 'WebUI::Resize', 
            params: {
                width: window.innerWidth,
                height: window.innerHeight
            }
        }
    ));
} */
)";