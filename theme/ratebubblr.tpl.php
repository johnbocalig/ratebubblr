<div class"configure><?php print $configure_link; ?></div>
<div class="message"><?php print $message; ?></div>
<div class="steps-text"><?php print $step_text; ?></div>
<div class="bubble-sort-form">
  <?php print $bubblesort_form; ?>
</div>
<table>
  <thead></thead>
  <tbody>
  <?php foreach ($things as $place => $thing): ?>
    <tr class="<?php print $thing['swapped']; ?><?php if ($current == $place): ?> current<?php endif; ?>">
      <td><div class="bar" style="width:<?php print ($thing['rating']/$rating_scale) * 100; ?>%"><span><?php print $thing['name'] . ' ' . $thing['number'] ; ?> (<?php print $thing['rating']; ?>)</span></div></td>
    </tr>
  <?php endforeach; ?>
  </tbody>
</table>