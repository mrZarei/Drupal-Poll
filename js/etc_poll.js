/**
 * Created by mohammadReza on 8/18/2016.
 */
(function($){
    Drupal.behaviors.epoll ={
        attach : function(){

            console.log("epoll");
            var entityId = (Drupal.settings.ep.entity_id != undefined)? Drupal.settings.ep.entity_id : 0;
            var field_name = (Drupal.settings.ep.field_name !=undefined)? Drupal.settings.ep.field_name : 'field_name';
            var cookie = $.cookie('ep-' +field_name+'-'+entityId);
            if(cookie){
                $("#ep-form-wrapper").css("display","none");
                $("#ep-form-wrapper").remove();
            }
            else{
                $("#ep-result-wrapper").css("display","none");
                $("#ep-result-wrapper").remove();
            }
        }
    }
})(jQuery);
