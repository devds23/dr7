/**
 * @file
 * jquery scripts which adds to theme theme1
 */
(function ($) {
    Drupal.behaviors.theme1js = {
        attach: function (context, settings) {
            $(".module4-header").css({"background-color": "yellow", "text-align": "center"});
            $(".custom-header").css({"background-color": "lightblue"});
            $(".full-custom-term-content").css({"color": "blue"});
            $(".teaser-term-content").css({"color": "red"});

            $(".module4-header").click(function () {
                $(".module4-body").slideToggle("slow");
            });

            $(".custom-program-node").click(function () {
                $(this).animate({fontSize: '3em'}, "slow");
                $(this).animate({fontSize: '1em'}, "slow");
            });
        }
    };
}(jQuery));

