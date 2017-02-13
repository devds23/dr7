(function ($) {
    Drupal.behaviors.petPreview = {
        attach: function (context) {
           $("form[id^='pets-owners-form']").once("petsOwnersPreview", function () {
               $("#content").append("<div id='preview-content'></div>");
                // $(this).click(function (e) {
                //     var data = {};
                //     $("form[id^='pets-owners-form'] .form-item *[name]").each(function () {
                //         if ($(this).attr('type') == 'radio' && $(this).attr('checked') == false ) {
                //             return;
                //         }
                //         data[$(this).attr('name')] = $(this).val();
                //     });
                //     // alert("hello");
                //     $.ajax({
                //         url: "http://drupal-site.naz/pets_owners/ajax",
                //         data: data,
                //         type: "POST",
                //         dataType: 'json',
                //         success: function (result) {
                //             $("form[id^='pets-owners-form']").after("<div>"+result+"</div>");
                //         }
                //     });

                // });
           });
        }
    }
})(jQuery);
