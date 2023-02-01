const char webpageCode[] PROGMEM =
  R"=====(
 <html>
  <head></head>
  <body>
    <button id="btn" type="button" ONCLICK="button()">LED</button>
    <script>
      initWebSocket();
      function initWebSocket(){
        websock = new WebSocket('ws://'+window.location.hostname+':81/');
        websock.onmessage = function(evt){
          jsonOBJ = JSON.parse(evt.data);
          document.getElementById('btn').innerHTML = jsonOBJ.LEDonoff;
        }
      }
    
      setInterval(function(){
        statusUpdate();
      }, 1000);

      function statusUpdate(){
        console.log("status..");
      }
      function button() {
        btn = 'LEDonoff=ON';
        if(document.getElementById('btn').innerHTML == 'ON'){
          btn = 'LEDonoff=OFF';
        }
        websock.send(btn);
     }
    </script>
  </body>
</html>
)=====";