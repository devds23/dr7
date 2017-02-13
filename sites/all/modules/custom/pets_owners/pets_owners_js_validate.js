/**
 * @file
 *
 * JS validation file
 */
(function ($) {
    /**
     * check required fields on empty
     * @type {{attach: Drupal.behaviors.requireFilds.attach}}
     */
    Drupal.behaviors.requireFilds = {
        attach: function (context) {
            $("form[id^='pets-owners-form']", context).once("petsOwnersValidate", function () {
                if (!$("#messages").length) {
                    $("#header").after('<div id="messages"><div class="section clearfix"></div></div>');
                }

                $(".required", this).focusout(function () {
                    $("#messages div.status").remove();

                    if (!$("#messages .section .error").length) {
                        $("#messages div").append("<div class='messages error'><ul></ul></div>");
                    }

                    if ($("#messages .error ul").length == 0 && $("#messages .error").has('h2')) {
                        var single_error = '<li>' + $('#messages .section .error').clone().children().remove().end().text() + '</li>';
                        $("#messages .error").remove();
                        $("#messages div").append("<div class='messages error'><ul></ul></div>");
                        $("#messages ul").append(single_error);
                    }

                    var label_text = labelName(this);
                    var label_item = "<li>Field " + label_text + " is required</li>";

                    if (isEmpty(this)) {
                        $("li:contains(Field " + label_text + " is required)").remove();
                        $("#messages ul").append(label_item);
                        $(this).addClass('error');
                    }
                    else {
                        $("li:contains(Field " + label_text + " is required)").remove();
                        $(this).removeClass('error');
                        var liLength = $("#messages .error ul li").length;

                        if (liLength == 0) {
                            $("#messages .error").remove();
                        }
                    }
                });

                $("#edit-email", this).focusout(function () {
                    $("#messages div.status").remove();

                    if (!$("#messages .section div:not(.status)").length) {
                        $("#messages div").append("<div class='messages error'><ul></ul></div>");
                    }

                    if ($.trim($(this).val()) == '') {
                        $("li:contains('Field email is not valid')").remove();
                        $("li:contains('Field Your email is required')").remove();
                    }
                    else {
                        $("li:contains('Field Your email is required')").remove();
                        var liMail = $("#messages .error ul li").length;

                        if (liMail == 0) {
                            $("#messages .error").remove();
                        }
                    }

                    if (!isEmpty(this) && !isEmail(this)) {
                        if (!($("#messages .section .error").length)) {
                            $("#messages div").append("<div class='messages error'><ul></ul></div>");
                        }
                        $("li:contains('Field email is not valid')").remove();
                        $("#messages ul").append("<li>Field email is not valid</li>");
                        $(this).addClass('error');
                    }
                    if (!isEmpty(this) && isEmail(this)) {
                        $("li:contains('Field email is not valid')").remove();

                        var liMail = $("#messages .error ul li").length;

                        if (liMail == 0) {
                            $("#messages .error").remove();
                        }
                    }
                });

                $(this).submit(function (event) {
                    var flag = true;
                    $("#messages div.status").remove();
                    if (!$("#messages .error ul").has('li')) {
                        $("#messages .section").html("");
                    }

                    $('.required', this).each(function () {
                        var label_text = labelName(this);
                        var label_item = "<li>Field " + label_text + " is required</li>";

                        if (isEmpty(this)) {
                            if (!$("#messages .section div:not(.status)").length) {
                                $("#messages div").append("<div class='messages error'><ul></ul></div>");
                            }
                            $("li:contains(Field " + label_text + " is required)").remove();
                            $("#messages ul").append(label_item);
                            $(this).addClass('error');
                            flag = false;
                        }
                        else if (!isEmpty(this) && !isEmail(this) && $(this).attr('id') == 'edit-email') {
                            if (!$("#messages .section div:not(.status)").length) {
                                $("#messages div").append("<div class='messages error'><ul></ul></div>");
                            }
                            $("li:contains('Field email is not valid')").remove();
                            $("#messages ul").append("<li>Field email is not valid</li>");
                            $("#edit-email").addClass('error');
                            flag = false;
                        }
                        else if (!isEmpty(this) && isEmail(this && $(this).attr('id') == 'edit-email')) {
                            $("li:contains(Field " + label_text + " is required)").remove();
                            $("li:contains('Field email is not valid')").remove();
                            $("<div class='messages error'><ul></ul></div>").remove();
                            $(this).removeClass('error');
                        }
                        console.log(flag + $(this).attr('id'));
                    });

                    return flag;
                });
            });
        }
    };

    /**
     *
     * @param obj
     * @returns {boolean}
     */
    function isEmail(obj) {
        var email = $.trim($(obj).val());
        var regex = /^([a-zA-Z0-9_.+-])+\@(([a-zA-Z0-9-])+\.)+([a-zA-Z0-9]{2,4})+$/;

        return regex.test(email);
    }

    /**
     *
     * @param obj
     * @returns {boolean}
     */
    function isEmpty(obj) {
        var value = $.trim($(obj).val());

        if (value == '') {
            return true;
        }
        return false;
    }

    /**
     *
     * @param obj
     * @returns {string|XML|void}
     */
    function labelName(obj) {
        var for_name = $(obj).attr('id');
        var label = $('label[for="' + for_name + '"]');

        return  label.text().replace("*", "");
    }
})(jQuery);
