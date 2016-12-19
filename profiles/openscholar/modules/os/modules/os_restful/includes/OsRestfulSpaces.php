<?php

/**
 * @file
 * Contains \OsRestfulSpaces
 */
abstract class OsRestfulSpaces extends \OsRestfulDataProvider {

  /**
   * @var vsite
   * The space object.
   */
  protected $space;

  /**
   * @var string
   * Object type: context, boxes etc. etc.
   */
  protected $objectType = '';

  /**
   * @var EntityMetadataWrapper
   *
   * The group wrapper object.
   */
  protected $group;

  /**
   * Overrides \RestfulDataProviderEFQ::controllersInfo().
   */
  public static function controllersInfo() {
    return array(
      '' => array(
        \RestfulInterface::GET => 'getSpace',
        \RestfulInterface::POST => 'createSpace',
        \RestfulInterface::PUT => 'updateSpace',
        \RestFulInterface::DELETE => 'deleteSpace',
      ),
      '^.*$' => array(
        \RestfulInterface::GET => 'getSpace',
      ),
    );
  }

  abstract public function createSpace();
  abstract public function updateSpace();
  abstract public function deleteSpace();

  /**
   * {@inheritdoc}
   */
  public function access() {
    return $this->checkGroupAccess();
  }

  /**
   * {@inheritdoc}
   */
  public function publicFieldsInfo() {
    return $this->simpleFieldsInfo(array('type', 'id', 'object_id', 'object_type', 'value'));
  }

  /**
   * Simple fields mapping.
   *
   * @param array $fields
   *   The list of the properties.
   * @return array
   *   List of the schema fields.
   */
  protected function simpleFieldsInfo($fields = array()) {
    $return = array();
    foreach ($fields as $field) {
      $return[$field] = array('property' => $field);
    }

    return $return;
  }

  /**
   * Overriding the query list filter method: Exposing only boxes.
   */
  protected function queryForListFilter(\SelectQuery $query) {
    parent::queryForListFilter($query);

    if ($this->objectType) {
      $query->condition('object_type', $this->objectType);
    }

    if (!empty($this->request['vsite'])) {
      $query->condition('id', $_GET['vsite']);
    }

    if (!empty($this->request['delta'])) {
      $query->condition('object_id', $this->request['delta']);
    }
  }

  /**
   * Throwing exception easily.
   * @param $message
   *   The exception message.
   * @throws RestfulBadRequestException
   */
  public function throwException($message) {
    throw new \RestfulBadRequestException($message);
  }

  /**
   * Verify the user's request has access CRUD in the current group.
   */
  public function checkGroupAccess() {
    $this->getObject();
    if (!$this->space = spaces_load('og', $this->object->vsite)) {
      // No vsite context.
      $this->throwException('The vsite ID is missing.');
    }

    // Set up the space.
    spaces_set_space($this->space);

    $this->group = entity_metadata_wrapper('node', $this->space->og);

    if (user_access('administer group', $this->getAccount())) {
      return TRUE;
    }
  }

  /**
   * un-serialize the value object.
   */
  public function mapDbRowToPublicFields($row) {
    $row->value = unserialize($row->value);
    return parent::mapDbRowToPublicFields($row);
  }

  /**
   * Override the list method in order to return a specific delta from the
   * space override.
   */
  public function getSpace() {
    $list = parent::index();

    $request = $this->getRequest();

    if (!empty($request['type']) && !empty($list[0]['value'][$request['type']])) {
      // We need a sub value from the space.
      $sub_value = $list[0]['value'][$request['type']];

      if (!empty($request['delta']) && !empty($sub_value[$request['delta']])) {
        // We need a specif delta from the sub value.
        return $sub_value[$request['delta']];
      }

      return $sub_value;
    }

    return $list;
  }

}
