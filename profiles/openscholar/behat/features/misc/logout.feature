Feature:
  Testing the logout link.

  @api @misc_first
  Scenario: Verify that when logging out the user gets redirected to the page
            he were in.
    Given I am logging in as "john"
     When I visit "john/classes"
      And I click "Log out"
     Then I should verify i am at "john/classes"
