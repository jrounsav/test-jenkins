<?php

class BiblioNodeRestfulBase extends OsNodeRestfulBase {

  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['type'] = array(
      'property' => 'biblio_type',
    );

    return $public_fields;
  }
}
