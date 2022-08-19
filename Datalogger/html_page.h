const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Datalogger</title>
</head>
<!-------------------------------C S S------------------------------>
<style>
  body {text-align:center; font-family:"Calibri"; background-color:rgba(0, 3, 8, 0.26)}
  h1   {color: rgba(0, 0, 255, 0.87); font-size: 50px;}
</style>
<!------------------------------H T M L----------------------------->
<body>
    <div class="main">
      <div class="main-data">
        <p>Time: </p>
        <p id="time"></p>
        <p>Channel 1: </p>
        <p id="analog1"></p>
        <p>Channel 2: </p>
        <p id="analog2"></p>
      </div>
      <div class="main-btn">
        <button id="run-btn" type="button" ONCLICK="runBtn()">Run/Stop</button>
        <button id="send-btn" type="button" ONCLICK="sendBtn()">Export</button>
      </div>
    </div>
<!-----------------------------JavaScript--------------------------->
  <script>
     InitWebSocket()
     function InitWebSocket()
     {
       websock = new WebSocket('ws://'+window.location.hostname+':81/'); 
       websock.onmessage = function(evt)
       {
          JSONobj = JSON.parse(evt.data);
          document.getElementById('btn').innerHTML = JSONobj.LEDonoff;
          if(JSONobj.LEDonoff == 'ON')
          {
            document.getElementById('btn').style.background='#FF0000';
            document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #FF0000";
          }
          else
          {
            document.getElementById('btn').style.background='#111111';
            document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #111111";
          }
       }
     }
     //-------------------------------------------------------------
     function button() {
        btn = 'LEDonoff=ON';
        if(document.getElementById('btn').innerHTML == 'ON') {
          btn = 'LEDonoff=OFF';
        }
        websock.send(btn);
     }
     function runBtn() {
       run_btn = 'run_btn=ON';
        if(JSONobj.run_btn == 'ON') {
          run_btn = 'run_btn=OFF';
        }
        websock.send(run_btn);
     }
     function sendBtn() {
       var output = jsonToCSV(JSONobj.time);
      document.getElementById('time').innerHTML = output[0];
       var output = jsonToCSV(JSONobj.channel1);
      document.getElementById('analog1').innerHTML = output[0];
       var output = jsonToCSV(JSONobj.channel2);
      document.getElementById('analog2').innerHTML = output[0];
       send_btn = 'send_btn=ON';
        if(JSONobj.send_btn == 'ON') {
          send_btn = 'send_btn=OFF';
        }
        websock.send(send_btn);
     }
     function jsonToCSV(objArray) {
       var array = objArray.split(",");

       return array;
     }
  </script>
</body>
</html>
)=====";
