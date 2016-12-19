<?php

class PresentationNodeRestfulBase extends OsNodeRestfulBase {

  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['date'] = array(
      'property' => 'field_presentation_date',
      'process_callbacks' => array(
        array($this, 'dateProcess'),
      ),
    );

    $public_fields['location'] = array(
      'property' => 'field_presentation_location',
    );

    return $public_fields;
  }

}
