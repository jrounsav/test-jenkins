/**
 * Handles the XSRF token for all write operations to the REST API
 */

(function () {
  var token = '';

  angular.module('os-auth', [])
    .factory('authenticate', ['$q', function ($q) {
      return {
        request: function (config) {
          if (token) {
            switch (config.method) {
              case 'PUT':
              case 'POST':
              case 'PATCH':
              case 'DELETE':
                config.headers['X-CSRF-Token'] = token;
                break;
              default:
                break;
            }

          }
          return config;
        }
      }
    }])
    .config(['$httpProvider', function ($httpProvider) {
        $httpProvider.interceptors.push('authenticate');
    }])
    .run(['$http', function ($http) {
      $http.get(Drupal.settings.paths.api+'/session/token').success(setToken);
    }]);

  function setToken(resp) {
    token = resp['X-CSRF-Token'];
  }
})();
