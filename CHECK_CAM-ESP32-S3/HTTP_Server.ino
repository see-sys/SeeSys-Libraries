//================== HTTP_Server ====================
void sendResponse() {

  String htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP32-S3-CAM</title>

<style>
body{
  margin:0;
  padding:20px;
  text-align:center;
  font-family:Arial;
  background:#f2f2f2;
}

h1{
  font-size:28px;
}

.box{
  display:inline-block;
  background:white;
  padding:20px;
  border-radius:16px;
  box-shadow:0 4px 15px rgba(0,0,0,0.15);
}

img{
  width:640px;
  max-width:95vw;
  height:auto;
  border-radius:12px;
  border:2px solid #333;
}
</style>

</head>

<body>
<h1>ESP32-S3-CAM Live</h1>

<div class="box">
  <img src="/cam">
</div>

</body>
</html>
)rawliteral";

  server.send(200, "text/html", htmlPage);
}

//=================================
void setupServer() {

  server.on("/", HTTP_GET, []() {
    sendResponse();
  });

  server.on("/cam", HTTP_GET, []() {
    String streamUrl = "http://" + WiFi.softAPIP().toString() + ":81/stream";
    server.sendHeader("Location", streamUrl, true);
    server.send(302, "text/plain", "");
  });
}
//===================================================