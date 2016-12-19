<?php

class PageNodeRestfulBase extends OsNodeRestfulBase {

  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['path'] = array(
      'property' => 'path',
    );

    return $public_fields;
  }

}
