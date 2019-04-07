#include <Arduino.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include "StreamString.h"
#include "ESP8266FirmwareUploader.h"

/*
static const char serverIndex[] PROGMEM =
  R"(<html><body><form method='POST' action='' enctype='multipart/form-data'>
                  <input type='file' name='update'>
                  <input type='submit' value='Update'>
               </form>
         </body></html>)";
*/

static const char serverIndex[] PROGMEM =
  R"(<!DOCTYPE html>
<html>
<head>
<meta charset=utf-8>
<meta name="description" content="Login">
<meta name="keywords" content="Updater">
<meta name="author" content="Cahyo Hertanto">
<meta name="viewport" content="width=320, initial-scale=1, user-scalable=no"/>
<title>Firmware Uploader</title>
</head>
<style>
body,textarea,input,select{background: 0;border-radius: 0;font: 16px sans-serif;margin: 0}
textarea,input,select{outline: 0;font-size: 14px;border: 1px solid #ccc;padding: 8px;width: 95%}
.btn{backgroud:teal;}.btn a{text-decoration: none; background:teal;}
.red{background:red;}.orange{background:orange;}.green{background:green;}.teal{background:teal;}
.container{margin: auto;padding-top:20px;width: 85%}a{text-decoration: none}
.btn{background:teal;}.btn,h2{font-size: 2em}h1{font-size: 3em}.red{background:red;}a{text-decoration: none;color:red;}
.btn{font-size:1.5em;border-radius: 4px;border: 0;color: #fff;cursor: pointer;display: inline-block;margin: 2px 0;padding: 10px 14px 11px;width: 100%}
.btn:hover{background: orange}.btn:active,.btn:focus{background: #008080}label>*{display: inline}form>*{display: block;margin-bottom: 10px}textarea:focus,input:focus,select:focus{border-color: #5ab}
.msg{margin-top:220px;background: #e6ffff;border-left: 5px solid #ff6600;border-right: 5px solid #ff6600;padding: 1.5em}
.q{float: right;width: 64px;text-align: right;color: green;}
.l{background: url('data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAACAAAAAgCAMAAABEpIrGAAAALVBMVEX///8EBwfBwsLw8PAzNjaCg4NTVVUjJiZDRUUUFxdiZGSho6OSk5Pg4eFydHTCjaf3AAAAZElEQVQ4je2NSw7AIAhEBamKn97/uMXEGBvozkWb9C2Zx4xzWykBhFAeYp9gkLyZE0zIMno9n4g19hmdY39scwqVkOXaxph0ZCXQcqxSpgQpONa59wkRDOL93eAXvimwlbPbwwVAegLS1HGfZAAAAABJRU5ErkJggg==') no-repeat left center;background-size: 1em}input[type='checkbox']{float: left;width: 20px}
 /* TABLE */
table {font-family: arial, sans-serif;border-collapse: collapse;width: 100%;}
td, th {border: 1px solid #dddddd;text-align: left;padding: 8px;}tr:nth-child(even) {background-color: #dddddd;}
/* The container */
.c {display: block;position: relative; padding-left: 35px;margin-bottom:25px;cursor: pointer;font-size: 18px;-webkit-user-select: none;-moz-user-select: none;-ms-user-select: none;user-select: none;}
.c input {position: absolute;opacity: 0;cursor: pointer;}.checkmark {position: absolute;top: 0;left: 0;height: 25px;width: 25px;background-color: #eee;}
.c:hover input ~ .checkmark {background-color: #ccc;}.c input:checked ~ .checkmark {background-color: teal;}
.checkmark:after {content:"";position: absolute;display: none;}
.c input:checked ~ .checkmark:after {display: block;}
.c .checkmark:after {left: 9px;top: 5px;width: 5px;height: 10px;border: solid white;border-width: 0 3px 3px 0;-webkit-transform: rotate(45deg);-ms-transform: rotate(45deg);transform: rotate(45deg);}
a{text-decoration: none}.btn{background:teal;}.btn,h2{font-size: 2em}h1{font-size: 3em}.red{background:red;}.orange{background:orange;}.green{background:green;}.teal{background:teal;}.yellow{background:yellow;}
a{text-decoration: none;color:red;}.btn{font-size:1.5em;border-radius: 4px;border: 0;color: #fff;cursor: pointer;display: inline-block;margin: 2px 0;padding: 10px 14px 11px;width: 100%}
.btn:hover{background: #5c5c8a}.btn:active,.btn:focus{background: #008080}label>*{display: inline}form>*{display: block;margin-bottom: 10px}textarea:focus,input:focus,select:focus{border-color: #5ab}
@media(min-width:1200px){.container{margin: auto;width: 30%}
@media(min-width:0px) and (max-width:320px){.container{margin: auto;width: 50%}}
.card {box-shadow: 0 4px 20px 0 rgba(0,0,0,0.2);transition: 0.3s;width: 100%;}
.card:hover {box-shadow: 0 8px 25px 0 rgba(0,0,0,0.2);}
.card_container {padding: 2px 16px;}

#myProgress {
  width: 100%;
  background-color: #ddd;
}

#myBar {
  width: 0%;
  height: 30px;
  background-color: #008080;
  text-align: center;
  line-height: 30px;
  color: white;
}
</style>

<script type="text/javascript">
      function fileSelected() {
        var file = document.getElementById('fileToUpload').files[0];
        if (file) {
          var fileSize = 0;
          if (file.size > 1024 * 1024)
            fileSize = (Math.round(file.size * 100 / (1024 * 1024)) / 100).toString() + 'MB';
          else
            fileSize = (Math.round(file.size * 100 / 1024) / 100).toString() + 'KB';

          document.getElementById('fileName').innerHTML = 'Name: ' + file.name;
          document.getElementById('fileSize').innerHTML = 'Size: ' + fileSize;
          document.getElementById('fileType').innerHTML = 'Type: ' + file.type;
        }
      }

      function uploadFile() {
        var fd = new FormData();
        fd.append("fileToUpload", document.getElementById('fileToUpload').files[0]);
        var xhr = new XMLHttpRequest();
        xhr.upload.addEventListener("progress", uploadProgress, false);
        xhr.addEventListener("load", uploadComplete, false);
        xhr.addEventListener("error", uploadFailed, false);
        xhr.addEventListener("abort", uploadCanceled, false);
        xhr.open("POST", "/update");
        xhr.send(fd);
        oTimer = setInterval(doInnerUpdates, 300);
      }

      function uploadProgress(evt) {
        if (evt.lengthComputable) {
          var percentComplete = Math.round(evt.loaded * 100 / evt.total);
          var elem = document.getElementById("myBar"); 
          var width = 0;
          var id = setInterval(frame, 1);
          document.getElementById('progressNumber').innerHTML = percentComplete.toString() + '%';
          document.getElementById("total").innerHTML = "Upload "+evt.loaded+" bytes from "+evt.total;
          function frame() {
            if (width >= 100) {
            clearInterval(id);
            } else {
            width++;
            elem.style.width = percentComplete.toString() + '%'; 
            elem.innerHTML = percentComplete.toString()* 1 + '%';
            }
          } 
        }
        else {
          document.getElementById('progressNumber').innerHTML = 'unable to compute';
        }
      }

      function uploadComplete(evt) {
        /* This event is raised when the server send back a response */
        alert(evt.target.responseText);
      }

      function uploadFailed(evt) {
        alert("There was an error attempting to upload the file.");
      }

      function uploadCanceled(evt) {
        alert("The upload has been canceled by the user or the browser dropped the connection.");
      }
    </script>
</head>
<body>
<div class="container">
<div class="card">
<div class="card_container" align="center">
<h4> Firmware Uploader </h4>
</div>
</div>
<br/>

<form id="form" enctype="multipart/form-data" method="post" action="">
<label>Select FIle to Upload</label>
<br/>
<input type="file" name="fileToUpload" id="fileToUpload" onchange="fileSelected();"/>
<div id="fileName"></div>
<div id="fileSize"></div>
<div id="fileType"></div>
<input type="button" style="width:380px" class="btn" onclick="uploadFile();" value="Update" />
<br/>
<br/>
<label>Progress:</label>
<div>
<div id="myBar"/>
<div id="total"/>
</div>

</div>
</form>
</body>
</html>)";
static const char successResponse[] PROGMEM = 
  "<META http-equiv=\"refresh\" content=\"15;URL=/\">Update Success, Rebooting Device ...\n";

ESP8266FirmwareUploader::ESP8266FirmwareUploader(bool serial_debug)
{
  _serial_output = serial_debug;
  _server = NULL;
  _username = emptyString;
  _password = emptyString;
  _authenticated = false;
}

void ESP8266FirmwareUploader::setup(ESP8266WebServer *server, const String& path, const String& username, const String& password)
{
    _server = server;
    _username = username;
    _password = password;

    // handler for the /update form page
    _server->on(path.c_str(), HTTP_GET, [&](){
      if(_username != emptyString && _password != emptyString && !_server->authenticate(_username.c_str(), _password.c_str()))
        return _server->requestAuthentication();
      _server->send_P(200, PSTR("text/html"), serverIndex);
    });

    // handler for the /update form POST (once file upload finishes)
    _server->on(path.c_str(), HTTP_POST, [&](){
      if(!_authenticated)
        return _server->requestAuthentication();
      if (Update.hasError()) {
        _server->send(200, F("text/html"), String(F("Update error: ")) + _updaterError);
      } else {
        _server->client().setNoDelay(true);
        _server->send_P(200, PSTR("text/html"), "Update Success, Rebooting Device ...");
        delay(100);
        _server->client().stop();
        ESP.restart();
      }
    },[&](){
      // handler for the file upload, get's the sketch bytes, and writes
      // them through the Update object
      HTTPUpload& upload = _server->upload();

      if(upload.status == UPLOAD_FILE_START){
        _updaterError = String();
        if (_serial_output)
          Serial.setDebugOutput(true);

        _authenticated = (_username == emptyString || _password == emptyString || _server->authenticate(_username.c_str(), _password.c_str()));
        if(!_authenticated){
          if (_serial_output)
            Serial.printf("Unauthenticated Update\n");
          return;
        }

        WiFiUDP::stopAll();
        if (_serial_output)
          Serial.printf("Update: %s\n", upload.filename.c_str());
        uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
        if(!Update.begin(maxSketchSpace)){//start with max available size
          _setUpdaterError();
        }
      } else if(_authenticated && upload.status == UPLOAD_FILE_WRITE && !_updaterError.length()){
        if (_serial_output) Serial.printf(".");
        if(Update.write(upload.buf, upload.currentSize) != upload.currentSize){
          _setUpdaterError();
        }
      } else if(_authenticated && upload.status == UPLOAD_FILE_END && !_updaterError.length()){
        if(Update.end(true)){ //true to set the size to the current progress
          if (_serial_output) Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
        } else {
          _setUpdaterError();
        }
        if (_serial_output) Serial.setDebugOutput(false);
      } else if(_authenticated && upload.status == UPLOAD_FILE_ABORTED){
        Update.end();
        if (_serial_output) Serial.println("Update was aborted");
      }
      delay(0);
    });
}

void ESP8266FirmwareUploader::_setUpdaterError()
{
  if (_serial_output) Update.printError(Serial);
  StreamString str;
  Update.printError(str);
  _updaterError = str.c_str();
}
