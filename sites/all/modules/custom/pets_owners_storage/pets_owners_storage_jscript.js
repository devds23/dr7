(function ($) {
    Drupal.behaviors.checkAjax = {
        attach: function (context, settings) {
            $('select.required', context).once("selectValidate", function () {
                $(this).focusout(function () {
                    var value = $(this).val();
                    if (value == '') {
                        $(this).addClass('error');
                    }
                    else {
                        $(this).removeClass('error');
                    }
                })
            });
        }
    }
}(jQuery));
