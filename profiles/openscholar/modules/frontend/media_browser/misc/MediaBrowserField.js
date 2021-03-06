(function () {

  angular.module('MediaBrowserField', ['mediaBrowser', 'FileEditorModal', 'EntityService', 'ui.sortable'])
    .directive('mediaBrowserField', ['mbModal', 'EntityService', function (mbModal, EntityService) {

      function link(scope, elem, attr) {
        // everything to define
        var field_root = elem.parent();
        while (!field_root.attr('id')) {
          field_root = field_root.parent();
        }
        var service = new EntityService('files', 'id');
        scope.field_name = field_root.attr('id').match(/edit-([\w-]*)/)[1].replace(/-/g, '_');
        scope.field_id = field_root.attr('id');
        scope.showHelp = false;
        scope.panes = ['upload', 'web', 'library'];
        scope.required = attr['required'] == "";

        var types = {};
        scope.allowedTypes = scope.types.split(',');
        scope.extensionsFull = [];
        for (var i = 0; i < scope.allowedTypes.length; i++) {
          var type = scope.allowedTypes[i];
          types[type] = type;
          if (Drupal.settings.extensionMap[type] && Drupal.settings.extensionMap[type].length) {
            scope.extensionsFull = scope.extensionsFull.concat(Drupal.settings.extensionMap[type]);
          }
        }
        scope.extensionsFull.sort();

        scope.sortableOptions = {
          axis: 'y',
          handle: '.tabledrag-handle'
        };

        if (!store.isNew()) {
          scope.selectedFiles = store.fetchData(scope.field_name);
        }
        else if (!Array.isArray(scope.selectedFiles)) {
          scope.selectedFiles = [];
        }

        if (scope.selectedFiles.length == 0) {
          var fids = Drupal.settings.mediaBrowserField[scope.field_id].selectedFiles,
            generateFunc = function (i) {
              return function(file) {
                scope.selectedFiles[i] = angular.copy(file);
                return file;
              }
            };

          for (var i = 0; i < fids.length; i++) {
            var fid = fids[i];
            service.fetchOne(fid).then(generateFunc(i));
          }
          store.setData(scope.field_name, scope.selectedFiles);
        }

        // prefetch the files now so user can open Media Browser later
        service.fetch();

        scope.$on('EntityService.files.update', function (e, file) {
          for (var i = 0; i<scope.selectedFiles.length; i++) {
            if (file.id == scope.selectedFiles[i].id) {
              scope.selectedFiles[i] = angular.copy(file);
            }
          }
          store.setData(scope.field_name, scope.selectedFiles);
        });

        scope.sendToBrowser = function($files) {
          var params = {
            files: $files,
            onSelect: scope.addFile,
            types: types
          };
          mbModal.open(params);
          for (var i = 0; i < scope.selectedFiles; i++) {
            highlightDupe(scope.selectedFiles[i], false);
          }
        }

        scope.addFile = function ($files) {
          for (var i = 0; i < $files.length; i++) {
            var found = false;
            for (var j = 0; j < scope.selectedFiles.length; j++) {
              highlightDupe(scope.selectedFiles[j], false);
              if ($files[i].id == scope.selectedFiles[j].id) {
                scope.selectedFiles[j] = angular.copy($files[i]);
                highlightDupe(scope.selectedFiles[j], true);
                found = true;
                break;
              }
            }
            if (!found) {
              scope.selectedFiles.push($files[i]);
            }
          }
          store.setData(scope.field_name, scope.selectedFiles);
        }

        scope.removeFile = function ($index) {
          scope.selectedFiles.splice($index, 1);
          store.setData(scope.field_name, scope.selectedFiles);
        }

        scope.replaceFile = function ($inserted, $index) {
          scope.selectedFiles.splice($index, 1, $inserted[0]);
          store.setData(scope.field_name, scope.selectedFiles);
        }

        function highlightDupe(file, toHighlight) {
          file.highlight = toHighlight;
        }

        scope.fieldIsFull = function () {
          if (scope.cardinality == -1) {
            return false;
          }

          return scope.selectedFiles.length >= scope.cardinality;
        }

        var label = elem.parent().find(' label');
        elem.parent().find(' > *').not(elem).remove();
        elem.before(label);
      }

      if (mbModal.requirementsMet()) {
        return {
          link: link,
          templateUrl: function () {
            return Drupal.settings.paths.moduleRoot + '/templates/field.html?vers=' + Drupal.settings.version.mediaBrowser
          },
          scope: {
            selectedFiles: '=files',
            maxFilesize: '@maxFilesize',
            types: '@',
            extensions: '@',
            upload_text: '@uploadText',
            droppable_text: '@droppableText',
            cardinality: '@'
          }
        }
      }
      else {
        // remove this element. It won't work right anyway
        return {
          link: function (elem, attr) {
            elem.remove();
          }
        }
      }
    }])
    .run(function () {
      angular.element(window).on('dragover drop', function(e) {
        e = e || event;
        e.preventDefault();
      });
    });

  var store;
  (function () {
    var form_id,
      new_form,
      data = {},
      inited = false;
    store = {
      init: function () {
        if (inited) {
          return;
        }

        inited = true;
        var old_id = sessionStorage['last_form'];
        form_id = document.querySelector('form input[name="form_build_id"]').value;

        if (form_id != old_id) {
          delete sessionStorage[old_id];
          new_form = true;
          sessionStorage['last_form'] = form_id;
        }
        else {
          data = JSON.parse(sessionStorage[form_id]);
          new_form = false;
        }
      },
      fetchData: function (field_name) {
        this.init();
        return data[field_name];
      },
      setData: function (field_name, newData) {
        this.init();
        data[field_name] = newData;
        sessionStorage[form_id] = JSON.stringify(data);
      },
      isNew: function () {
        this.init();
        return new_form;
      }
    };
  })();
})();