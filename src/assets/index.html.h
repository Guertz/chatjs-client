/**
 * @brief Scheletro HTML di base app
 * @file index.html.h
 */

/** Scheletro HTML di base app */
const std::string _src_assets_index_html = R"(
<html>
    <head>
        <title>Chat.js</title>
        <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE11"/> 
        <script></script>
    </head>
    <body>

        <navbar class="w3-bar w3-light-grey w3-right-align" ></navbar>
        
        <div class="w3-row">
            <chat-list class="w3-col m4"></chat-list>
            <chat-details class="w3-col m8"></chat-details>
        </div>

        <div id="snackbar"></div>
    </body>

</html>
)";