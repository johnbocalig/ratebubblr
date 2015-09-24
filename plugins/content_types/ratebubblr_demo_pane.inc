<?php

$plugin = array(
  'single' => TRUE,
  'title' => t('Rate Bubblr Demo Pane'),
  'description' => t('The pane that displays the Bubble Sort Demo.'),
  'category' => t('Rate Bubblr'),
  'render callback' => 'ratebubblr_demo_pane_render',
  'defaults' => array(
    'text' => '',
  ),
  'all contexts' => TRUE,
);

/**
 * Render callback for the Rate Bubblr demo pane.
 */
function ratebubblr_demo_pane_render($subtype, $conf, $args, $contexts) {
  $name = variable_get('ratebubblr_name', RATEBUBBLR_NAME_DEFAULT);
  $things_type = variable_get('ratebubblr_things_type', RATEBUBBLR_THINGS_TYPE_DEFAULT);

  $block = new stdClass();

  // initial content is blank
  $block->title = t('Help !name with !things_type', array('!name' => $name, '!things_type' => $things_type));
  $block->content = theme('ratebubblr');

  return $block;
}