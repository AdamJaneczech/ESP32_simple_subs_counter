static const char* response = "HTTP/1.1 200 OK   \
Content-type:text/html  \
Connection: close";

static const char* PROGMEM ConfigPage = 

"<!DOCTYPE html> \
<html lang=\"en\">  \
<head>  \
    <meta charset=\"UTF-8\">    \
    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">   \
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">  \
    <title>ESP32 FLUNI ticker</title>   \
</head> \
<body>  \
    <form action=\"/url\" method=\"GET\">   \
        <p>Enter the network SSID and password below:</p>    \
        <input type=\"text\" placeholder=\"SSID\">  \
        <input type=\"text\" placeholder=\"Password\" minlength=\"8\">  \
        <button type=\"submit\">Submit</button> \
    </form> \
</body> \
</html>";

static const char* input_ssid = "ssid";
static const char* input_password = "password";