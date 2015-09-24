<?php

/**
 * Theme preprocess function for theme_preprocess_ratebubblr().
 */
function template_preprocess_ratebubblr(&$variables) {
  // Include the custom stylesheet for the display.
  drupal_add_css(drupal_get_path('module', 'ratebubblr') . '/theme/css/ratebubblr.css');

  // Bring the ratebubblr name and things type variables
  // in to display a personalized message to the user.
  $name = variable_get('ratebubblr_name', RATEBUBBLR_NAME_DEFAULT);
  $things_type = variable_get('ratebubblr_things_type', RATEBUBBLR_THINGS_TYPE_DEFAULT);
  $text_substitutions = array('!name' => $name, '!things_type' => $things_type);
  $variables['message'] = t('!name wants to create an ordered list of !things with the highest rated on top and down to the lowest rated on the bottom. Help !name place the !things in order by pressing the "Step" button until !name is happy.', $text_substitutions);

  // Add the bubble sort form (Shuffle and step buttons
  // to the variables array.
  $bubble_sort_form = drupal_get_form('ratebubblr_bubblesort_form');
  $variables['bubblesort_form'] = drupal_render($bubble_sort_form);

  // Add the "things to sort" array into the mix.
  $things = new Things();
  $variables['things'] = $things->things;

  // The step text will change depending on if the
  // array is in correct order.
  $variables['step_text'] = $things->checkOrder() ? t('Yay! !name is happy with the order of !things_type! Press the Shuffle button to start again.', $text_substitutions) : t('!name is not happy with the order of !things_type yet. Try clicking the Step button to sort the !things_type.', $text_substitutions);

  // Capturing the current position to add styling on
  // the bar for visual indication of where the user is.
  $variables['current'] = $things->position;

  // Capturing the rating scale to be output in the
  // template.
  $variables['rating_scale'] = variable_get('ratebubblr_rating_scale', RATEBUBBLR_RATING_SCALE_DEFAULT);

  // Add a configure link for easy admin access if the
  // user has the permission to access the administration
  // page.
  $variables['configure_link'] = user_access('administer ratebubblr') ? l(t('Configure the demo values'), RATEBUBBLR_ADMIN_PATH, array('attributes' => array('destination' => $_GET['q']))) : '';
}