<?php

/**
 * Class Things.
 */
class Things {
  public $position;
  public $numberOfThings;
  public $ratingScale;
  public $things;

  /**
   * Construction magic method.
   */
  public function __construct() {
    $this->numberOfThings = variable_get('ratebubblr_number_of_things', RATEBUBBLR_NUMBER_THINGS_DEFAULT);
    $this->ratingScale = variable_get('ratebubblr_rating_scale', RATEBUBBLR_RATING_SCALE_DEFAULT);
    $this->position = variable_get('ratebubblr_things_position', 0);
    $this->getThings();
    if (empty($this->things)) {
      $this->shuffleThings();
    }
  }

  /**
   * Retrieves the ratebubblr things from the database
   * and returns the array into the things variable.
   */
  private function getThings() {
    $this->things = unserialize(variable_get('ratebubblr_things'));
  }

  /**
   * Steps through the things array, compares the rating
   * value and swaps the two elements if the first value
   * checked is less than the second value checked.
   *
   * @return string
   *  'swapped' or 'not-swapped'
   * @throws Exception
   */
  public function stepThings() {
    $swapped = 'not-swapped';
    if ($this->position === NULL) {
      throw new Exception('Cannot step through the things without the position.');
    }
    else if ($this->position < 0 || $this->position > $this->numberOfThings - 1) {
      throw new Exception('Invalid position.');
    }
    else if ($this->position == $this->numberOfThings - 1) {
      // Reset position if the position is at the end of the list.
      $this->position = 0;
      variable_set('ratebubblr_things_position', $this->position);
      $this->saveThings();

      return $swapped;
    }
    else {
      $a = $this->things[$this->position];
      $b = $this->things[$this->position + 1];
      // if a is less than b, swap.
      if ($a['rating'] < $b['rating']) {
        $this->things[$this->position] = $b;
        $this->things[$this->position + 1] = $a;
        $swapped = 'swapped';
      }
    }
    if (isset($this->things[$this->position - 1])) {
      $this->things[$this->position - 1]['swapped'] = 'not-swapped';
    }
    if (isset($this->things[$this->position + 1])) {
      $this->things[$this->position]['swapped'] = $swapped;
      $this->things[$this->position + 1]['swapped'] = $swapped;
    }
    $this->position++;
    variable_set('ratebubblr_things_position', $this->position);
    $this->saveThings();

    return $swapped;
  }

  /**
   * Resets the things array and creates a new array of
   * things.
   *
   * @throws \Exception
   */
  public function shuffleThings() {
    if ($this->numberOfThings === NULL) {
      throw new Exception('Cannot shuffle the things without the number of things.');
    }
    if ($this->ratingScale === NULL) {
      throw new Exception('Cannot shuffle the things without the rating scale.');
    }
    $this->deleteThings();
    $this->createThings();
    $this->saveThings();
    $this->position = 0;
    variable_set('ratebubblr_things_position', $this->position);
  }

  /**
   * Saves the array of things into the variables table
   * of the database.
   */
  public function saveThings() {
    variable_set('ratebubblr_things', serialize($this->things));
  }

  /**
   * Deletes the array of things in the variables table
   * of the database.
   */
  public function deleteThings() {
    variable_set('ratebubblr_things', serialize(array()));
  }

  /**
   * Creates an array of things with randomized rating
   * scale values.
   */
  public function createThings() {
    $things = array();
    for ($i = 0; $i < $this->numberOfThings; $i++) {
      $things[] = array(
        'number' => $i,
        'rating' => rand(0, $this->ratingScale),
        'name' => t('Thing'),
        'swapped' => 'not-swapped',
      );
    }
    $this->things = $things;
  }

  /**
   * Checks the order of the things array.
   *
   * @return bool
   */
  public function checkOrder() {
    foreach ($this->things as $key => $thing) {
      if (isset($this->things[$key + 1]) && $thing['rating'] < $this->things[$key + 1]['rating']) {
        // Found an item that disproves that the array is
        // in order.
        return FALSE;
      }
    }
    // Found no items that disproves that the array is
    // in order.
    return TRUE;
  }
}