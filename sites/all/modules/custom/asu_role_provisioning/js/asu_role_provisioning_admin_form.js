/**
 * Created by ctestama on 7/25/16.
 */
(function ($) {
    Drupal.behaviors.asu_role_provisioning = {
        attach: function (context, settings) {

            var arp_affil = $('#arp-affil-select');
            //var criteria_element = $('#arp-role-criteria');
            var roles_element = $('#arp-roles');
            var config_element = $('#arp-role-config');
            var show_config_element = $('#arp-show-config');
            var the_configs = settings.asu_role_provisioning.configs;

            console.log(the_configs);

            //Buttons
            var crit_button = $('#arp-new-criteria');
            var clear_button = $('#arp-clear-params');
            var save_button = $('#arp-save');


            //Add criteria joined by AND or OR
            /*
            crit_button.click(function(event) {
                event.preventDefault();


                if (field != null) {

                    current_param = field;
                    /*
                    if (current_params == '') {
                        current_params = field + ":" + param;
                        $('#arp-joiner').show();
                    } else {
                        current_params += ' ' + op + ' ' + field + ":" + param;
                    }

                    criteria_element.find('input').val('');
                    show_crit.text(current_params);
                }
            });

            //clear paramaters
            clear_button.click(function(event) {
                event.preventDefault();
                current_params = '';
                show_crit.text('');
                $('#arp-joiner').hide();
            });*/

            //save the rule to the configs array
            save_button.click(function(event) {
                event.preventDefault();

                var roles = roles_element.find('select').val();
                var params = arp_affil.find('input').val();

                if (params != null && roles != null && params != '' && roles.length > 0) {
                    var conf = {
                        'params': params,
                        'roles': roles
                    };

                    the_configs.push(conf);

                    config_element.find('textarea').val(JSON.stringify(the_configs));

                    show_configs(the_configs, show_config_element);
                }
            });

            //Remove a rule
            function remove_conf(index) {
                the_configs.splice(index, 1);
                show_configs(the_configs, show_config_element);
                config_element.find('textarea').val(JSON.stringify(the_configs));
            }

            //Render the role provisioning rules
            function show_configs(configs, target) {
                target.html('');

                for (var i = 0; i < configs.length; i++) {
                    var c = configs[i];
                    var item = '<div>&emsp;Params:' + c.params + '&emsp;Roles:' + c.roles +
                        '&emsp;<a class="arp-remove-rule" value="' + i + '">' +
                        'X</a></div>';
                    target.append(item);
                }

                $('a.arp-remove-rule').click(function(event) {
                    var index = $(this).attr('value');
                    remove_conf(index);
                });
            }

            //render the saved configs if they exist
            if (the_configs != null) {
                show_configs(the_configs, show_config_element);
            }
        }
    }
})(jQuery);

