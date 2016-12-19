Feature:
  Testing the tiny MCE is enabled.

  @javascript
  Scenario: Verify the tiny MCE is enabled.
    Given I am logging in as "admin"
     When I visit "john/node/add/blog"
     Then I should see tineMCE in "Body"
