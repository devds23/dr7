<?php
/**
 * @file
 * theme1's theme implementation to display a taxonomy term
 *   mode.
 */
?>
<div id="custom-taxonomy-term-teaser-<?php print $term->tid; ?>"
     class="taxonomy-term-teaser <?php print $classes; ?>">

  <?php if (!$page): ?>
    <h2><a href="<?php print $term_url; ?>"><?php print $term_name; ?></a></h2>
  <?php endif; ?>

  <div class="custom-term-content">
    <?php print render($content); ?>
  </div>

</div>
