<?php
/**
 * @file
 * theme1's theme implementation to display a taxonomy term through full view
 *   mode.
 */
?>
<div id="full-custom-taxonomy-term-<?php print $term->tid; ?>"
     class="full-taxonomy-term <?php print $classes; ?>">

  <?php if (!$page): ?>
    <h2><a href="<?php print $term_url; ?>"><?php print $term_name; ?></a></h2>
  <?php endif; ?>

  <div class="full-custom-term-content">
    <?php print render($content); ?>
  </div>

</div>
