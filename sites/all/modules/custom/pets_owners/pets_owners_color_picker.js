(function ($) {
    Drupal.ajax.prototype.commands.color_picker = function(ajax, response, status) {
        $('a').css('color', response.color);
        console.log(response.style);
    }
})(jQuery);
