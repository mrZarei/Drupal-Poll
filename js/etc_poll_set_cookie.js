/**
 * Created by mohammadReza on 8/18/2016.
 */

(function($){
    Drupal.behaviors.ETCPollsetCookie = {
        attach:function(){
            if(Drupal.settings.ep.entity_id !== undefined) {
                var entityId = (Drupal.settings.ep.entity_id != undefined)? Drupal.settings.ep.entity_id : 0;
                var field_name = (Drupal.settings.ep.field_name !=undefined)? Drupal.settings.ep.field_name : 'field_name';
                var delta  = (Drupal.settings.ep.delta != undefined)? Drupal.settings.ep.delta : 0;
                $.cookie('ep-'+field_name+'-'+entityId, delta, {expires: 31, path: '/'});
            }
        }
    }

})(jQuery);
