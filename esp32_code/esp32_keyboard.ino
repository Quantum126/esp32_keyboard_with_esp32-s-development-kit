#include <WiFi.h>
#include <WebServer.h>

// ====== WiFi Config ======
const char* ssid = "ESP32_KEYBOARD";
const char* password = "12345678";

WebServer server(80);

// Simple URL encoder (replace space, newline, etc.)
String urlEncode(const String &str) {
  String encoded = "";
  char c;
  char bufHex[4];
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (isalnum(c)) {
      encoded += c;
    } else if (c == ' ') {
      encoded += '+';
    } else {
      sprintf(bufHex, "%%%02X", c);
      encoded += bufHex;
    }
  }
  return encoded;
}

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>ESP32 Keyboard</title>
    </head>
    <body>
      <h2>ESP32 Keyboard Bridge</h2>hello
      <form action="/send" method="GET">
        <textarea name="text" rows="10" cols="40" placeholder="Enter text here..."></textarea><br>
        <input type="submit" value="Send">
      </form>
      <br>
      <form action="/key" method="GET">
        <select name="key">
          <option value="enter">Enter</option>
          <option value="backspace">Backspace</option>
          <option value="tab">Tab</option>
          <option value="esc">ESC</option>
          <option value="up">Arrow Up</option>
          <option value="down">Arrow Down</option>
          <option value="left">Arrow Left</option>
          <option value="right">Arrow Right</option>
        </select>
        <input type="submit" value="Send Key">
      </form>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleSend() {
  if (server.hasArg("text")) {
    String text = server.arg("text");
    text.replace("\r\n", "\n");  // normalize newlines
    String encoded = urlEncode(text); // our custom encoder
    Serial.println("TEXT:" + encoded);
    Serial.println("ENDTEXT");
    server.send(200, "text/html", "<h3>Text sent successfully!</h3><a href=\"/\">Go Back</a>");
  } else {
    server.send(400, "text/plain", "No text received!");
  }
}

void handleKey() {
  if (server.hasArg("key")) {
    String key = server.arg("key");
    Serial.println("KEY:" + key);
    server.send(200, "text/html", "<h3>Key sent: " + key + "</h3><a href=\"/\">Go Back</a>");
  } else {
    server.send(400, "text/plain", "No key received!");
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  Serial.println("Access Point Started");
  Serial.println("Connect to WiFi: " + String(ssid));
  Serial.println("IP Address: " + WiFi.softAPIP().toString());

  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.on("/key", handleKey);

  server.begin();
}

void loop() {
  server.handleClient();
}
