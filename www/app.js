var myApp = angular.module('gasDetector', []);
myApp.controller('gasLevelController', ['$scope', function($scope){
	$scope.gasLevel='Dummy gas sensor value';
}]);