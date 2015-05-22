var myApp = angular.module('gasDetector', []);

myApp.controller('gasLevelController', ['$scope', function($scope){
	var relayr = RELAYR.init({
    appId: "45e676b0-a93e-469f-b01d-6e985466369a"
 	});
 	  relayr.devices().getDeviceData({
    deviceId: "c36642b8-3327-4935-8f21-19a0196e7349", 
    token: "lCS.8toUuj67toE.Uh4YX-xhSY7lSDes",
    incomingData: function(data){
      console.log("sensor",data);
      $scope.gasLevel=data.readings.value;
    }
  });    
	//$scope.gasLevel='Dummy gas sensor value';
}]);