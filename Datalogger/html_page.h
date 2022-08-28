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
  p {
    margin: 1rem;
  }
  .main-data {
    display: flex;
    flex-direction: column;
  }
  .row-data {
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-items: center;
  }
  .main-btn{
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
  }
</style>
<!------------------------------H T M L----------------------------->
<body>
    <div class="main">
      <div class="main-data">
        <div class="row-data">
          <p>Time: </p>
          <p id="time"></p>
        </div>
        <div class="row-data">
          <p>Channel 1: </p>
          <p id="analog1"></p>
        </div>
        <div class="row-data">
          <p>Channel 2: </p>
          <p id="analog2"></p>
        </div>
      </div>
      <div class="main-btn">
        <button id="run-btn" type="button" ONCLICK="runBtn()">Run/Stop</button>
        <div class="csv-form">
          <input id="file-name" placeholder="data"></input>
          <button id="send-btn" type="button" ONCLICK="sendBtn()">Export</button>
        </div>
        <span id="btn" onclick="btn()"></span>
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
          var packLength = JSONobj.pack_length;
          
          var output = jsonToCSV(JSONobj.time);
          document.getElementById('time').innerHTML = output[packLength];
          var output = jsonToCSV(JSONobj.channel1);
          document.getElementById('analog1').innerHTML = output[packLength];
          var output = jsonToCSV(JSONobj.channel2);          
          document.getElementById('analog2').innerHTML = output[packLength];
          
          //document.getElementById('btn').innerHTML = JSONobj.run_btn;
          if(JSONobj.run_btn == 'ON')
          {
            document.getElementById('run-btn').style.background='#FF0000';
            document.getElementById('run-btn').innerHTML = "Stop";
          }
          else
          {
            document.getElementById('run-btn').style.background='#777777';
            document.getElementById('run-btn').innerHTML = "Run";
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
       send_btn = 'send_btn=ON';
        if(JSONobj.send_btn == 'ON') {
          send_btn = 'send_btn=OFF';
        }
        websock.send(send_btn);
        download();
     }
     function jsonToCSV(objArray) {
       var array = objArray.split(",");

       return array;
     }
     function download() {
       var packLength = JSONobj.pack_length;
       var csv = 'Time,Channel1,Channel2\n';
       var time_String = jsonToCSV(JSONobj.time);
       var channel1_String = jsonToCSV(JSONobj.channel1);
       var channel2_String = jsonToCSV(JSONobj.channel2);

       for(var i=0; i<= packLength;i++) {
         csv += time_String[i]+','+ channel1_String[i]+','+channel2_String[i]
         csv += "\n"
       }

       console.log(csv);

       var hiddenElement = document.createElement('a');  
       hiddenElement.href = 'data:text/csv;charset=utf-8,' + encodeURI(csv);  
       hiddenElement.target = '_blank';  
       
       hiddenElement.download = 'data.csv';  
//       hiddenElement.click();  
     }
  </script>
</body>
</html>
)=====";
