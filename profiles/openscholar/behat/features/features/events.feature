Feature:
  Testing the events (calendar) tab.

  @api @features_first
  Scenario: Test the Management of registrations for an event with no registrants
    Given I am logging in as "john"
     When I create a new registration event with title "Registration event"
      And I manage registrations for the event "Registration event"
      And I should not see "Download Registrant List"

  @api @features_first
  Scenario: Test the Management of registrations for an event with a registrant
    Given I am logging in as "john"
      And I sign up "Foo bar" with email "foo@example.com" to the event "Registration event"
      And I manage registrations for the event "Registration event"
      And text exists "Foo bar"
     Then I click "Download Registrant List"
     Then I should see "Simple view"
      And I should see "CSV"

  @api @features_first
  Scenario: Test the simple view for the event registrants
    Given I am logging in as "john"
      And I manage registrations for the event "Registration event"
     When I click "Simple view"
     Then I should see "[ ] Foo bar - foo@example.com"

  @api @features_first
  Scenario: Test the simple view for the event registrants
    Given I am logging in as "john"
      And I manage registrations for the event "Registration event"
     When I export the registrants list for the event "Registration event" in the site "john"
     Then I verify the file contains the user "Foo bar" with email of "foo@example.com"
