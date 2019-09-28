const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<style type="text/css">
html {
  box-sizing: border-box;
  font-family: 'Arial', sans-serif;
  font-size: 100%;

}
*, *:before, *:after {
  box-sizing: inherit;
  margin:0;
  padding:0;
}
.mid {
  display: flex;
  align-items: center;
  justify-content: center;
  padding-top:1em;
}


/* Switch starts here */
.rocker {
  display: inline-block;
  position: relative;
  /*
  SIZE OF SWITCH
  ==============
  All sizes are in em - therefore
  changing the font-size here
  will change the size of the switch.
  See .rocker-small below as example.
  */
  font-size: 2em;
  font-weight: bold;
  text-align: center;
  text-transform: uppercase;
  color: #888;
  width: 7em;
  height: 4em;
  overflow: hidden;
  border-bottom: 0.5em solid #eee;
}

.rocker-small {
  font-size: 0.75em; /* Sizes the switch */
  margin: 1em;
}

.rocker::before {
  content: "";
  position: absolute;
  top: 0.5em;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #999;
  border: 0.5em solid #eee;
  border-bottom: 0;
}

.rocker input {
  opacity: 0;
  width: 0;
  height: 0;
}

.switch-left,
.switch-right {
  cursor: pointer;
  position: absolute;
  display: flex;
  align-items: center;
  justify-content: center;
  height: 2.5em;
  width: 3em;
  transition: 0.2s;
}

.switch-left {
  height: 2.4em;
  width: 2.75em;
  left: 0.85em;
  bottom: 0.4em;
  background-color: #ddd;
  transform: rotate(15deg) skewX(15deg);
}

.switch-right {
  right: 0.5em;
  bottom: 0;
  background-color: #bd5757;
  color: #fff;
}

.switch-left::before,
.switch-right::before {
  content: "";
  position: absolute;
  width: 0.4em;
  height: 2.45em;
  bottom: -0.45em;
  background-color: #ccc;
  transform: skewY(-65deg);
}

.switch-left::before {
  left: -0.4em;
}

.switch-right::before {
  right: -0.375em;
  background-color: transparent;
  transform: skewY(65deg);
}

input:checked + .switch-left {
  background-color: #0084d0;
  color: #fff;
  bottom: 0px;
  left: 0.5em;
  height: 2.5em;
  width: 3em;
  transform: rotate(0deg) skewX(0deg);
}

input:checked + .switch-left::before {
  background-color: transparent;
  width: 3.0833em;
}

input:checked + .switch-left + .switch-right {
  background-color: #ddd;
  color: #888;
  bottom: 0.4em;
  right: 0.8em;
  height: 2.4em;
  width: 2.75em;
  transform: rotate(-15deg) skewX(-15deg);
}

input:checked + .switch-left + .switch-right::before {
  background-color: #ccc;
}

/* Keyboard Users */
input:focus + .switch-left {
  color: #333;
}

input:checked:focus + .switch-left {
  color: #fff;
}

input:focus + .switch-left + .switch-right {
  color: #fff;
}

input:checked:focus + .switch-left + .switch-right {
  color: #333;
}

button {
    color: #444444;
    background: #F3F3F3;
    border: 1px #DADADA solid;
    padding: 5px 10px;
    border-radius: 2px;
    font-weight: bold;
    font-size: 9pt;
    outline: none;
}

button:hover {
    border: 1px #C6C6C6 solid;
    box-shadow: 1px 1px 1px #EAEAEA;
    color: #333333;
    background: #F7F7F7;
}

button:active {
    box-shadow: inset 1px 1px 1px #DFDFDF;   
}



/* Red Google Button as seen on drive.google.com */
button.red {
    background: -webkit-linear-gradient(top, #DD4B39, #D14836); 
    background: -moz-linear-gradient(top, #DD4B39, #D14836); 
    background: -ms-linear-gradient(top, #DD4B39, #D14836); 
    border: 1px solid #DD4B39;
    color: white;
    text-shadow: 0 1px 0 #C04131;
}

button.red:hover {
     background: -webkit-linear-gradient(top, #DD4B39, #C53727);
     background: -moz-linear-gradient(top, #DD4B39, #C53727);
     background: -ms-linear-gradient(top, #DD4B39, #C53727);
     border: 1px solid #AF301F;
}

button.red:active {
     box-shadow: inset 0 1px 1px rgba(0,0,0,0.2);
    background: -webkit-linear-gradient(top, #D74736, #AD2719);
    background: -moz-linear-gradient(top, #D74736, #AD2719);
    background: -ms-linear-gradient(top, #D74736, #AD2719);
}

</style>
<body style="background-color: #5d6d7e; color: #ECEFF1;
  background-image: radial-gradient(#4f6875, #263238);">
 <center>
<h2>Majoreng Automation Panel<h2>
<h3> </h3>
 <br><br>
<form action="/action_page">
<center>
<br>
<div class="mid">
<br>AC Cooler<br>
  <label class="rocker rocker-small">

    <input type="checkbox" value="true" name="AC Cooler">
    <span class="switch-left">ON</span>
    <span class="switch-right">OFF</span>

  </label>
<br>Water Cooler<br>
 <label class="rocker rocker-small">
    <input type="checkbox" value="true" name="Water Cooler">
    <span class="switch-left">ON</span>
    <span class="switch-right">OFF</span>
  </label>
<br>Flower House<br>
<label class="rocker rocker-small">
    <input type="checkbox" value="true" name="Flower House" >
    <span class="switch-left">ON</span>
    <span class="switch-right">OFF</span>
  </label>
<br>Lamp<br>
<label class="rocker rocker-small">
    <input type="checkbox" value="true" name="Lamp">
    <span class="switch-left">ON</span>
    <span class="switch-right">OFF</span>
  </label>
</div>


 <br>

 <br>
 <br>
  ON Time (Miniute):<br>
  <input type="text" name="ONtime" value="1">
  <br>
  OFF Time (Minute):<br>
  <input type="text" name="OFFtime" value="1">
  <br>
  Sequence Number:<br>
  <input type="text" name="Seqn" value="1">
  <br>
  <input type="submit" value="Submit">
</form> 

<br><br>
 <div id="demo">
<h1>Alarm And Temp Control</h1>
<br><br>

 <button class="red" type="button" onclick="sendData(1)">Switch ON</button>
  <button class="red" type="button" onclick="sendData(0)">Switch OFF</button><BR>

</div>
 <br>
<div style="font-family: 'Roboto Condensed', sans-serif;">
  Temperature & Humidity : <span id="ADCValue">0</span><br>
    LED State is : <span id="LEDState">NA</span><br>
PIR Status:  <span id="PIRValue">0</span><br>
</div>
<script>
function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  xhttp.send();
}
 
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
  getData2();
}, 2000); //2000mSeconds update rate
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("ADCValue").innerHTML =
      this.responseText;

    }
  };
  xhttp.open("GET", "readADC", true);
  xhttp.send();
}
function getData2() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      
document.getElementById("PIRValue").innerHTML =
      this.responseText;
    }
  };
  
  xhttp.open("GET", "readPIR", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
