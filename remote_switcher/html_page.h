const char webpageCode[] PROGMEM =
R"=====(
<!DOCTYPE HTML>
<html>
<head>
  <title>ESP32 Web Server</title>
</head>
<!-------------------------------C S S------------------------------>
<style>
  body{
    
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    
    text-align:center;
    font-family:"Calibri";
    background-color:rgba(0, 3, 8, 0.26)
  }
  h1{    
    font-size: 6rem;    
    color: rgba(0, 127, 0, 1);
  }
  #btn{
    display: inline-block;
    width: 30rem;
    height: 30rem;
    font-weight: bold;
    font: 12rem arial, sans-serif;
    line-height: 150px;
    border-radius: 50%;
    text-align: center;
    vertical-align: middle;
    overflow: hidden;
    box-shadow: 0px 0px 0px 8px #8CD460;
    border: solid 10px rgba(127,127,127, 0.47);
    text-decoration: none;
    color: rgba(150,150,150, 0.80);
    transition: 0.5s;
  }
  .main{
    height: 80vh;
    width: 80%;
    
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;

    margin: 2rem;
    padding: 2rem;
    
    background-color: #333;
    border-radius: 2rem;
  }
</style>
<!------------------------------H T M L----------------------------->
<body>
   <div class="main">
     <h1>Antena Switcher</h1>
     <button id="btn" ONCLICK='button()'> </button>
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
            document.getElementById('btn').style.background='#00FF00';
            document.getElementById('btn').style["boxShadow"] = "0px 0px 0px 8px #00FF00";
          }
       }
     }
     //-------------------------------------------------------------
     function button()
     {
        btn = 'LEDonoff=ON';
        if(document.getElementById('btn').innerHTML == 'ON')
        {
          btn = 'LEDonoff=OFF';
        }
        websock.send(btn);
     }
  </script>
</body>
</html>
)=====";
