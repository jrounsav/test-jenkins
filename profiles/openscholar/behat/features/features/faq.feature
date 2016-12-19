Feature:
  Testing the faq app.

  @api @features_first
  Scenario: Testing the migration of FAQ
    Given I am logging in as "john"
      And I visit "john/faq"
      And I should see "What does JFK stands for?"
     When I click "What does JFK stands for?"
     Then I should see "JFK stands for: John Fitzgerald Kennedy."

  @api @features_first
  Scenario: Testing the migration of FAQ
    Given I am logging in as "john"
      And I visit "john/faq"
      And I click "Add New"
      And I click "FAQ"
      And I fill "edit-title" with random text
      And I press "Save"
     Then I should see the random string

  @api @features_first
  Scenario: Verify that the FAQ's body in the LOP is collapsed by default.
    Given I am logging in as "john"
      And the widget "List of posts" is set in the "FAQ" page with the following <settings>:
          | Content Type               | FAQ         | select list |
          | Display style              | Teaser      | select list |
     When I visit "john/faq"
     Then I should see that the "faq" in the "LOP" are collapsed


  @api @features_first
  Scenario: Verify that body length limits are respected
    Given I am logging in as "john"
      And I set the variable "os_wysiwyg_maximum_length_body" to "50"
      And I visit "john/node/add/faq"
     When I fill in "edit-title" with "Gonna fail"
      And I fill in "edit-body-und-0-value" with "01234567890123456789012345678901234567890123456789AAAAAA"
      And I press "Save"
     Then I should see "Answer cannot be longer than 50 characters but is currently 56 characters long."
      And I delete the variable "os_wysiwyg_maximum_length_body"

