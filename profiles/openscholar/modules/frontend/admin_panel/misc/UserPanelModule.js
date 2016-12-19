(function () {
	var rootPath;
  var restPath;
  var vsite;
  var notify_settings;
  var user_data;
  var paths;

  angular.module('UserPanel', ['AdminPanel'])
  .config(function () {
    rootPath = Drupal.settings.paths.adminPanelModuleRoot;
    restPath = Drupal.settings.paths.api;

    if(typeof(Drupal.settings.spaces) == 'undefined') {
      vsite = false;
    } else {
      vsite = Drupal.settings.spaces.id;
    }

    user_data = Drupal.settings.user_panel.user;
    paths = Drupal.settings.paths;
    notify_settings = Drupal.settings.os_notifications;
  }).controller("UserMenuController",['$scope', '$http', '$timeout', function ($scope, $http, $timeout) {
    
      $scope.user = user_data;
      $scope.vsite = { id: vsite };
      $scope.paths = paths;
      $scope.close_others = function(id){
    	//Protect the current link
    	if(!jQuery("#rightMenuSlide .click-processing").length) {
          jQuery("#rightMenuSlide [data-id='"+id+"']").addClass('click-processing');
    	}
        // After closing the modal, setting the search text field as blank and resetting search results.
        $scope.searchString = '';
        $timeout(function() {
          jQuery('#rightMenuSlide .menu_modal_open').not("[data-id='"+id+"']").not('.click-processing').click();
          $timeout(function() {
            jQuery("#rightMenuSlide .click-processing").removeClass('click-processing');
          });
      	});
      };

  }]).controller("UserSitesController",['$scope', '$http', function ($scope, $http) {
    $scope.baseUrl = Drupal.settings.basePath;
    $scope.purlBaseDomain = Drupal.settings.admin_panel.purl_base_domain + "/";

    var url = paths.api + '/users/' + user_data.uid;
    $http({method: 'get', url: url}).then(function(response) {
      if(typeof(response.data.data[0].og_user_node) == 'undefined') {
        $scope.site_data = [];
      } else {
        $scope.site_data = response.data.data[0].og_user_node;
      }
      $scope.create_access = response.data.data[0].create_access;
    });
    $scope.pageSize = 7;
    if (Drupal.settings.spaces) {
      $scope.delete_destination = encodeURIComponent('?destination=node/' + Drupal.settings.spaces.id + encodeURIComponent('?destination=' + window.location.pathname.replace(/^\/|\/$/g, '')));
    } else {
      $scope.delete_destination = '';
    }
    $scope.numberOfPages=function(data){
      return Math.ceil(data.length/$scope.pageSize);
    }
  }]).directive('rightMenu', function() {
      return {
       templateUrl: rootPath+'/templates/user_menu.html?vers='+Drupal.settings.version.userPanel,
       controller: 'UserMenuController',
     };
  }).directive('addDestination', function() {
      //Add the destination to a URL
	  return {
	    link: function(scope, element, attrs) {
		  var url = (typeof(attrs.href) == 'undefined') ? attrs.ngHref : attrs.href;
	      element.attr('href', url + ((url.indexOf('?') == -1) ? '?' : '&') + 'destination=' + encodeURIComponent(location.href));
  	    },
	  }
  }).directive('loadMySites', function() {
    	 
    return {
        templateUrl: rootPath+'/templates/user_sites.html?vers='+Drupal.settings.version.userPanel,
        controller: 'UserSitesController',
      };
       
  }).service('notificationService', [function () {
    //check for google and hopscotch
    if (typeof google == 'undefined' || typeof hopscotch == 'undefined') {
      return;
    }

    function handleNotificationStepEvent(num_remaining) {
      count--;
      for (var i=0; i<handlers.step.length; i++) {
        handlers.step[i](num_remaining);
      }
    }

    function handleNotificationEndEvent() {
      for (var i=0; i<handlers.end.length; i++) {
        handlers.step[i]();
      }
    }

    var count = 0;
    var handlers = {
      step: [],
      end: [],
      load: []
    };
    var tour;
    var loaded = false;

    // @TODO: Add support for multiple feeds.
    var feed = new google.feeds.Feed(notify_settings.url);
    feed.setNumEntries(notify_settings.max);
    feed.load(function (result) {
      loaded = true;
      if (result.error) {
        return;
      }

      var items = [],
        oldItems = [];

      for (var i = 0; i < result.feed.entries.length; i++) {
        var num_remaining = (result.feed.entries.length - i);
        var entry = result.feed.entries[i];
        var item = osTour.notifications_item(entry, num_remaining, false, handleNotificationStepEvent, target);
        if (osTour.notifications_is_new(entry)) {
          items.push(item);
        }
        else {
          oldItems.push(item);
        }
      }

      /* Add a permanent "stop" node to the end of the list. */
      var lastEntryContent = "There are no new announcements. Click here to view the <a href=\"http://hwp.harvard.edu/os-alerts/announcement\" target=\"_blank\">archive</a>.";
      var lastEntry = {
        author: "scholar",
        categories: [],
        content: lastEntryContent,
        contentSnippet: lastEntryContent,
        publishedDate: "Fri, 1 Jan 1971 00:00:00 -0800",
        title: "No new announcements."
      };
      var lastItem = osTour.notifications_item(lastEntry, 0, true, handleNotificationStepEvent, target);
      var trueCount = items.length;
      items.push(lastItem);

      // If there are new items
      if (trueCount) {
        // Sets up the DOM elements.
        count = trueCount;
        //$('#os-tour-notifications-menu-link').slideDown('slow');

        // Sets up the tour object with the loaded feed item steps.
        tour = {
          showPrevButton: true,
          scrollTopMargin: 100,
          id: "os-tour-notifications",
          steps: items,
          onEnd: function () {
            handleNotificationEndEvent();
            osTour.notifications_read_update();
          }
        };
      }
      else {
        oldItems.reverse();

        tour = {
          showPrevButton: true,
          scrollTopMargin: 100,
          id: "os-tour-notifications",
          steps: oldItems
        };
      }

      for (var i = 0; i < handlers.load.length; i++) {
        handlers.load[i]();
      }
    });

    this.Count = function () {
      return count;
    }

    var targetSet = false;
      target = null;
    this.MakeTarget = function (element) {
      if (element) {
        targetSet = true;
        target = element;

        if (tour && tour.steps) {
          for (var i=0; i<tour.steps.length; i++) {
            tour.steps[i].target = element;
          }
        }
      }
    }

    /**
     * Event can be 'step' or 'end'
     */
    this.AddHandler = function (event, handler) {
      if (typeof handler != 'function') {
        throw new Exception('Notification handler must be a function');
      }
      switch (event) {
        case 'load':
          if (loaded) {
            handler();
            break;
          }
        case 'step':
        case 'end':
          handlers[event].push(handler);
          break;
        default:
          throw new Exception('Notification handler event must be "step" or "end".');
      }
    }

    this.ToggleTour = function () {
      if (hopscotch.getCurrTour()) {
        hopschotch.endTour();
      }
      else {
        hopscotch.startTour(tour);
      }
    }

  }]).directive('notificationCheck', ['notificationService', function(notificationService) {
      
    //Go to feed and check for notifications.
    return {
      link: function(scope, element, attrs) {
        var count_element = angular.element('<span class="slate alert" ng-alert=></span>');
        var link = element.find('a')[0];
        if (link) {
          notificationService.MakeTarget(link);
        }
        element.append(count_element);

        notificationService.AddHandler('load', function () {
          var n = notificationService.Count();
          count_element.html(n);
          if (n <= 0) {
            count_element.hide();
          }
        });

        notificationService.AddHandler('step', function (n) {
          count_element.html(n);
          if (n <= 0 || n == undefined) {
            count_element.hide();
          }
        });

        notificationService.AddHandler('end', function () {
          count_element.hide();
        })

        element.find('a').bind('click', function(e) {
          e.preventDefault();

          if (jQuery(e.target).hasClass('click-processing')) {
            notificationService.ToggleTour();
            jQuery('.hopscotch-bubble').addClass('os-tour-notifications');

            // Hide notifications counter when there are none left
            var value = parseInt(jQuery('.slate.alert').text());
            if (value < 1) {
              jQuery('.slate.alert').hide();
            }
          }
        });
      }
    }
  }]).directive('rightMenuToggle', function() {
        return {
            link: function(scope, element, attrs) {
        	  element.bind('click', function(e) {
        		  e.preventDefault();
        		  jQuery('div#rightMenuSlide').each( function () {
        	        if(this.style.display == 'none') {
        	          jQuery(this).fadeIn('fast');
        	          jQuery(this).addClass('open');
        	        } else {
        	          jQuery(this).fadeOut('fast');
        	          jQuery(this).removeClass('open');
        	        }
        	      });
              })  
            },
          }
        });
})();
