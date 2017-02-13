<?php
/**
 * @file
 * Theme page template file
 */
//dpm($theme_hook_suggestions);
?>

<div class="wrapper-page">
  <div class="custom-header">
    <?php if ($logo): ?>
      <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"
         rel="home" id="logo">
        <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>"/>
      </a>
    <?php endif; ?>

    <?php if ($site_name || $site_slogan): ?>
      <div id="site-name">

        <?php if ($site_name): ?>
          <?php print $site_name; ?>
        <?php endif; ?>

      </div> <!-- /#name-and-slogan -->
    <?php endif; ?>

    <?php print $messages; ?>
  </div>
  <div id="page-header"><p><?php print render($page['header']); ?></p></div>
  <div id="page-content"><p><?php print render($page['content']); ?></p></div>
  <div id="page-footer"><p><?php print render($page['footer']); ?></p></div>
</div>
