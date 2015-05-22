var myApp = angular.module('gasDetector', []);

myApp.controller('gasLevelController', ['$scope', function($scope){
	var relayr = RELAYR.init({
    appId: "45e676b0-a93e-469f-b01d-6e985466369a"
    //appId: "7cfe17c8-41e0-4edc-93d4-ce56dbbde4a8" (in the neighbouthood)
 	});
 	  relayr.devices().getDeviceData({
    deviceId: "c36642b8-3327-4935-8f21-19a0196e7349", 
    //deviceId: "a2242103-c522-4b6f-a533-7740db2cb891", (in the neighbouthood)
    //token: "yRl.dC9fPiMmmO-.cjkYf_OSCAo-KR3l", (in the neighbouthood)
    token: "lCS.8toUuj67toE.Uh4YX-xhSY7lSDes",
    incomingData: function(data){
      console.log("sensor",data);
      $scope.gasLevel=data.readings.value;
    }
  });    
	//$scope.gasLevel='Dummy gas sensor value';
}]);