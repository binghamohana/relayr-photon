var reading = document.getElementById('reading');
var devId = "5439a96f-f58a-4ec2-ad3b-6f74526acaee";
var token =  "lCS.8toUuj67toE.Uh4YX-xhSY7lSDes";
var relayr = RELAYR.init({
    appId: "45e676b0-a93e-469f-b01d-6e985466369a"
});

relayr.devices().getDeviceData({
   deviceId: devId, 
   token: token,
   incomingData: function(data){
     console.log("sensor",data);
     reading.innerText="My moisture reading is " + data.readings[0].value;
   }
});  

var changeColor = function(color) {
  var device = {
    deviceId: devId,
    token: token,
    command: {"color":color.toLowerCase()}
  };
  relayr.devices().sendCommand(device);
};
